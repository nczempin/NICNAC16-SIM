#include <iostream>
#include <vector>
#include <memory>
#include <cstdint> // For uint16_t

// Adjust include paths based on how CMake is configured or project structure
// Assuming CMake will handle include directories for "cpp_include" and "generated_cpp"
#include "processor.hpp"
#include "decoder.hpp"
#include "instruction.hpp"

int main(int argc, char* argv[]) {
    // Suppress unused parameter warnings
    (void)argc;
    (void)argv;

    Processor p;
    uint16_t next = 0;

    // Program Loading (translated from Main.java)
    // Opcode is in bits 15-12. Address/data in bits 11-0.
    // Program: LDA 0x0F01, ADD 0x0F02, STA 0x0F03, HALT
    p.writeMemory(next++, static_cast<uint16_t>((0b0100 << 12) | 0x0F01)); // 0: LDA 0x0F01
    p.writeMemory(next++, static_cast<uint16_t>((0b0110 << 12) | 0x0F02)); // 1: ADD 0x0F02
    p.writeMemory(next++, static_cast<uint16_t>((0b0101 << 12) | 0x0F03)); // 2: STA 0x0F03
    p.writeMemory(next++, 0x7FFF);                                     // 3: HALT

    // Data for the program
    p.writeMemory(0x0F01, 10); // Data for LDA
    p.writeMemory(0x0F02, 23); // Data for ADD
    // 0xF03 will be written by STA (Value: 10 + 23 = 33 (0x21))

    p.printState();

    bool done = false;
    uint16_t word = 0;
    std::unique_ptr<Instruction> instruction_ptr;

    while (!done) {
        if (p.PC_ >= Processor::MEMORY_SIZE) {
            std::cerr << "Error: Program Counter out of bounds!" << std::endl;
            break;
        }

        word = p.readMemory(p.PC_);

        if (word == 0x7FFF) { // Special HALT value
            std::cout << "===== END OF LINE =====" << std::endl;
            done = true;
            continue; // or break;
        }

        // Decode: Opcode is in the highest 4 bits (15-12)
        // The Decoder::decode function expects the full word, and it extracts the opcode.
        // So, we pass the full 'word'.
        try {
            instruction_ptr = Decoder::decode(word);
        } catch (const std::runtime_error& e) {
            std::cerr << "Runtime Error during decode: " << e.what() << std::endl;
            std::cerr << "At PC: 0x" << std::hex << p.PC_ << ", word: 0x" << word << std::dec << std::endl;
            done = true; // Halt on unknown instruction
            continue;
        }


        // Execute
        if (instruction_ptr) {
            // The base execute in Instruction.java did p.PC++.
            // In C++, this logic needs to be in the specific instruction's execute method or handled carefully.
            // The current generated NopInstruction::execute is (void)word; (void)p;
            // The PC increment should be part of the instruction's execution.
            // For now, we will assume instructions handle their own PC modifications (e.g., JMP)
            // or Processor::incrementPC() is called by non-branching instructions.

            // Let's assume non-branching instructions should increment PC *before* execution,
            // or rather, the instruction itself handles PC update.
            // The original Java code had p.PC++ in the Instruction base class execute.
            // This means PC was incremented *before* the specific instruction logic ran.
            // Let's replicate this behavior for now by incrementing PC *before* calling execute,
            // unless the instruction itself is a control flow one (JMP, BL, RET).
            // However, the generated execute methods are currently placeholders.
            // The NOP instruction *should* do p.incrementPC().
            // JMP, BL, RET should set PC directly.
            // Other instructions (LDA, STA, ADD, BAN) should also increment PC.

            // The simplest way for now, until individual instructions are correctly implemented:
            // All instructions are responsible for their PC update.
            // NOP, LDA, STA, ADD, BAN should call p.incrementPC().
            // JMP, BL, RET should set p.PC_ directly.
            // The base `Instruction::execute` is pure virtual.
            // Let's ensure the NOP instruction in generated code gets `p.incrementPC()`.
            // For this main loop, we call execute, and trust it does the right thing.

            instruction_ptr->execute(word, p);
        } else {
            // This case should ideally not be reached if Decoder::decode throws on unknown opcodes.
            std::cerr << "Error: Decoded to a null instruction_ptr, but no exception was thrown." << std::endl;
            std::cerr << "At PC: 0x" << std::hex << p.PC_ << ", word: 0x" << word << std::dec << std::endl;
            done = true; // Halt on this unexpected error
            continue;
        }

        p.printState();

        // Safety break for now to prevent infinite loops if PC isn't managed correctly by all instructions yet
        if (p.PC_ >= next && word != 0x7FFF) { // If PC hasn't moved past loaded program and not halted
            // This is a temporary check. Ideally, the JMP 0 or HALT should control flow.
            // If the last instruction was not a JMP, and PC points to 0x7FFF, it will halt next.
            // If PC points beyond 'next', it's in uninitialized memory.
        }
    }

    return 0;
}
