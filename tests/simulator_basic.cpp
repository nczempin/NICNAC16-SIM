#include "catch.hpp"
#include "processor.hpp"
#include "decoder.hpp"
#include "instruction.hpp"

TEST_CASE(basic_program) {
    Processor p;
    uint16_t next = 0;
    p.writeMemory(next++, static_cast<uint16_t>((0b0100 << 12) | 0x0010));
    p.writeMemory(next++, static_cast<uint16_t>((0b0110 << 12) | 0x0011));
    p.writeMemory(next++, static_cast<uint16_t>((0b0101 << 12) | 0x0012));
    p.writeMemory(next++, 0x7FFF);
    p.writeMemory(0x0010, 1);
    p.writeMemory(0x0011, 2);
    bool done = false;
    uint16_t word;
    while (!done) {
        word = p.readMemory(p.PC_);
        if (word == 0x7FFF) {
            done = true;
        } else {
            auto inst = Decoder::decode(word);
            inst->execute(word, p);
        }
    }
    REQUIRE(p.readMemory(0x0012) == 3);
}

int main(){
    return run_tests();
}
