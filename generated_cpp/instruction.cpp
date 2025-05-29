#include "instruction.hpp"
#include "processor.hpp"
#include <stdexcept> // For std::runtime_error
#include <iostream> // For potential debug messages (though not used in final logic)

void NopInstruction::execute(uint16_t word, Processor& p) {
    (void)word; // NOP doesn't use the word content beyond opcode
    p.incrementPC();
}

void JmpInstruction::execute(uint16_t word, Processor& p) {
    uint16_t address = word & 0xFFF;
    p.PC_ = address;
}

void BlInstruction::execute(uint16_t word, Processor& p) {
    uint16_t address = word & 0xFFF;
    p.AC_ = p.PC_ + 1; // Return address is the next instruction after BL
    p.PC_ = address;
}

void RetInstruction::execute(uint16_t word, Processor& p) {
    (void)word; // RET usually doesn't use the word content
    p.PC_ = p.AC_;
}

void LdaInstruction::execute(uint16_t word, Processor& p) {
    uint16_t address = word & 0xFFF;
    p.AC_ = p.readMemory(address);
    p.incrementPC();
}

void StaInstruction::execute(uint16_t word, Processor& p) {
    uint16_t address = word & 0xFFF;
    p.writeMemory(address, p.AC_);
    p.incrementPC();
}

void AddInstruction::execute(uint16_t word, Processor& p) {
    uint16_t address = word & 0xFFF;
    p.AC_ += p.readMemory(address); // uint16_t handles overflow by wrapping
    p.incrementPC();
}

void BanInstruction::execute(uint16_t word, Processor& p) {
    uint16_t address = word & 0xFFF;
    p.AC_ &= p.readMemory(address);
    p.incrementPC();
}
