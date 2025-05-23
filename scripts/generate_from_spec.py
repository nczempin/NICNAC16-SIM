#!/usr/bin/env python3
"""Generate C++ sources from the ISA specification."""

import json
from pathlib import Path
import os

def to_pascal_case(name: str) -> str:
    """Converts a name like NOP or JMP to Nop or Jmp, and BL to Bl."""
    if not name:
        return ""
    return name[0].upper() + name[1:].lower()

def main():
    repo_root = Path(__file__).resolve().parent.parent
    spec_path = repo_root / "NICNAC16-ISA" / "isa.json"
    output_dir = repo_root / "generated_cpp"

    # Create output directory if it doesn't exist
    output_dir.mkdir(parents=True, exist_ok=True)

    with spec_path.open() as f:
        spec = json.load(f)
    instructions = spec.get("instructions", [])
    
    # Get address mask from spec, default to 0x0FFF if not specified
    # The spec defines "address": {"hi": 11, "lo": 0}
    # Mask should cover from lo to hi bits.
    address_field_spec = spec.get("fields", {}).get("address", {"hi": 11, "lo": 0})
    address_hi = address_field_spec.get("hi", 11)
    address_lo = address_field_spec.get("lo", 0)
    # Calculate mask: (1 << (number of bits)) - 1, then shift if lo > 0
    # Number of bits for address is hi - lo + 1
    num_address_bits = address_hi - address_lo + 1
    address_mask = (1 << num_address_bits) - 1
    # If address_lo is not 0, the mask needs to be shifted, but for address extraction
    # from word, we usually mask then shift if needed, or shift then mask.
    # Here, `word & 0x0FFF` implies lo is 0.
    # The spec is "address": {"hi": 11, "lo": 0}, so mask is (1 << 12) - 1 = 0xFFF.
    # The python script currently passes address_mask = 0x0FFF directly
    # This is correct for the current NICNAC16 spec.

    generate_instruction_hpp(output_dir, instructions)
    # Pass the determined address_mask to the function
    generate_instruction_cpp(output_dir, instructions, address_mask) 
    generate_decoder_hpp(output_dir, instructions)
    generate_decoder_cpp(output_dir, instructions, spec.get("fields", {}).get("opcode", {}))
    print(f"C++ files generated in {output_dir}")

def generate_instruction_hpp(output_dir: Path, instructions):
    dest = output_dir / "instruction.hpp"
    lines = [
        "#pragma once",
        "",
        "#include <cstdint>",
        "#include <memory>",
        "",
        "// Forward declaration",
        "class Processor;",
        "",
        "class Instruction {",
        "public:",
        "    virtual ~Instruction() = default;",
        "    virtual void execute(uint16_t word, Processor& p) = 0;",
        "};",
        "",
    ]
    for inst in instructions:
        class_name = f"{to_pascal_case(inst['name'])}Instruction"
        lines.append(f"class {class_name} : public Instruction {{")
        lines.append("public:")
        lines.append(f"    void execute(uint16_t word, Processor& p) override;")
        lines.append("};")
        lines.append("")
    
    dest.write_text("\n".join(lines))

def generate_instruction_cpp(output_dir: Path, instructions, address_mask_val: int):
    dest = output_dir / "instruction.cpp"
    address_mask_hex_str = f"0x{address_mask_val:03X}" # e.g. 0x0FFF for a 12-bit mask
    
    lines = [
        '#include "instruction.hpp"',
        '#include "processor.hpp"', # processor.hpp is in cpp_include, which is an include dir
        '#include <stdexcept> // For std::runtime_error',
        '#include <iostream> // For potential debug messages (though not used in final logic)',
        "",
    ]

    for inst in instructions:
        class_name = f"{to_pascal_case(inst['name'])}Instruction"
        lines.append(f"void {class_name}::execute(uint16_t word, Processor& p) {{")
        inst_name = inst['name']

        if inst_name == "NOP":
            lines.append("    (void)word; // NOP doesn't use the word content beyond opcode")
            lines.append("    p.incrementPC();")
        elif inst_name == "JMP":
            lines.append(f"    uint16_t address = word & {address_mask_hex_str};")
            lines.append("    p.PC_ = address;")
        elif inst_name == "BL":
            lines.append(f"    uint16_t address = word & {address_mask_hex_str};")
            lines.append("    p.AC_ = p.PC_ + 1; // Return address is the next instruction after BL")
            lines.append("    p.PC_ = address;")
        elif inst_name == "RET":
            lines.append("    (void)word; // RET usually doesn't use the word content")
            lines.append("    p.PC_ = p.AC_;")
        elif inst_name == "LDA":
            lines.append(f"    uint16_t address = word & {address_mask_hex_str};")
            lines.append("    p.AC_ = p.readMemory(address);")
            lines.append("    p.incrementPC();")
        elif inst_name == "STA":
            lines.append(f"    uint16_t address = word & {address_mask_hex_str};")
            lines.append("    p.writeMemory(address, p.AC_);")
            lines.append("    p.incrementPC();")
        elif inst_name == "ADD":
            lines.append(f"    uint16_t address = word & {address_mask_hex_str};")
            lines.append("    p.AC_ += p.readMemory(address); // uint16_t handles overflow by wrapping")
            lines.append("    p.incrementPC();")
        elif inst_name == "BAN":
            lines.append(f"    uint16_t address = word & {address_mask_hex_str};")
            lines.append("    p.AC_ &= p.readMemory(address);")
            lines.append("    p.incrementPC();")
        else:
            # Fallback for any instruction not explicitly handled above
            # This case should ideally not be reached if isa.json is complete and handled
            lines.append("    (void)word;")
            lines.append(f"    // Instruction '{inst_name}' is defined in isa.json but not explicitly handled in generate_instruction_cpp.")
            lines.append(f"    throw std::runtime_error(\"Execution logic for {inst_name} not implemented in script.\");")

        lines.append("}")
        lines.append("")
        
    dest.write_text("\n".join(lines))

def generate_decoder_hpp(output_dir: Path, instructions):
    dest = output_dir / "decoder.hpp"
    lines = [
        "#pragma once",
        "",
        "#include <cstdint>",
        "#include <memory>",
        '#include "instruction.hpp"',
        "",
        "namespace Decoder {",
        "    std::unique_ptr<Instruction> decode(uint16_t full_opcode_word);",
        "} // namespace Decoder",
    ]
    dest.write_text("\n".join(lines))

def generate_decoder_cpp(output_dir: Path, instructions, opcode_field_spec):
    dest = output_dir / "decoder.cpp"
    
    op_hi = opcode_field_spec.get("hi", 15) # Default to 15 if not in spec
    op_lo = opcode_field_spec.get("lo", 12) # Default to 12 if not in spec
    op_shift = op_lo
    op_mask_len = op_hi - op_lo + 1
    op_mask = (1 << op_mask_len) - 1

    lines = [
        '#include "decoder.hpp"',
        '#include "instruction.hpp"',
        '#include <stdexcept> // For std::runtime_error',
        '#include <string>    // For std::to_string',
        "",
        "namespace Decoder {",
        "",
        "std::unique_ptr<Instruction> decode(uint16_t full_opcode_word) {",
        f"    // Opcode definition from spec: hi={op_hi}, lo={op_lo}",
        f"    uint8_t opcode = (full_opcode_word >> {op_shift}) & 0x{op_mask:X};",
        "    switch (opcode) {",
    ]
    for inst in instructions:
        class_name = f"{to_pascal_case(inst['name'])}Instruction"
        lines.append(f"    case {inst['opcode']}: // Decoded value for {inst['name']}")
        lines.append(f"        return std::make_unique<{class_name}>();")
    lines.extend([
        "    default:",
        "        throw std::runtime_error(\"Unknown opcode: \" + std::to_string(static_cast<int>(opcode)));",
        "    }",
        "}",
        "",
        "} // namespace Decoder",
    ])
    dest.write_text("\n".join(lines))

if __name__ == "__main__":
    main()
