#!/usr/bin/env python3
"""Generate Java sources from the ISA specification."""

import json
from pathlib import Path

def main():
    repo_root = Path(__file__).resolve().parent.parent
    spec_path = repo_root / "NICNAC16-ISA" / "isa.json"
    with spec_path.open() as f:
        spec = json.load(f)
    instructions = spec.get("instructions", [])

    generate_instruction_enum(repo_root, instructions)
    generate_decoder(repo_root, instructions)


def generate_instruction_enum(repo_root: Path, instructions):
    package = "de.czempin.nicnac16"
    dest = repo_root / "src" / "de" / "czempin" / "nicnac16" / "Instruction.java"
    lines = [
        f"package {package};",
        "",
        "import de.czempin.nicnac16.Processor;",
        "",
        "public enum Instruction {",
    ]
    for inst in instructions:
        lines.append(f"    {inst['name']},")
    lines[-1] = lines[-1][:-1] + ";"
    lines.extend([
        "",
        "    public void execute(int word, Processor p) {",
        "        p.PC++;",
        "    }",
        "}",
    ])
    dest.write_text("\n".join(lines))


def generate_decoder(repo_root: Path, instructions):
    package = "de.czempin.nicnac16.simulator"
    dest = repo_root / "src" / "de" / "czempin" / "nicnac16" / "simulator" / "Decoder.java"
    lines = [f"package {package};", "", "import de.czempin.nicnac16.Instruction;", "", "public class Decoder {", "", "    public static Instruction decode(int opcode) {", "        switch (opcode) {"]
    for inst in instructions:
        lines.append(f"        case 0b{int(inst['opcode']):04b}:")
        lines.append(f"            return Instruction.{inst['name']};")
    lines.extend([
        "        default:",
        "            throw new RuntimeException();",
        "        }",
        "    }",
        "}",
    ])
    dest.write_text("\n".join(lines))


if __name__ == "__main__":
    main()

