#pragma once

#include <cstdint>
#include <memory>
#include "instruction.hpp"

namespace Decoder {
    std::unique_ptr<Instruction> decode(uint16_t full_opcode_word);
} // namespace Decoder