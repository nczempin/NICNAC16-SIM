#include "decoder.hpp"
#include "instruction.hpp"
#include <stdexcept> // For std::runtime_error
#include <string>    // For std::to_string

namespace Decoder {

std::unique_ptr<Instruction> decode(uint16_t full_opcode_word) {
    // Opcode definition from spec: hi=15, lo=12
    uint8_t opcode = (full_opcode_word >> 12) & 0xF;
    switch (opcode) {
    case 0: // Decoded value for NOP
        return std::make_unique<NopInstruction>();
    case 1: // Decoded value for JMP
        return std::make_unique<JmpInstruction>();
    case 2: // Decoded value for BL
        return std::make_unique<BlInstruction>();
    case 3: // Decoded value for RET
        return std::make_unique<RetInstruction>();
    case 4: // Decoded value for LDA
        return std::make_unique<LdaInstruction>();
    case 5: // Decoded value for STA
        return std::make_unique<StaInstruction>();
    case 6: // Decoded value for ADD
        return std::make_unique<AddInstruction>();
    case 8: // Decoded value for BAN
        return std::make_unique<BanInstruction>();
    default:
        throw std::runtime_error("Unknown opcode: " + std::to_string(static_cast<int>(opcode)));
    }
}

} // namespace Decoder
