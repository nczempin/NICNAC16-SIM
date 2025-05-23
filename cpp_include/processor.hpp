#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <iomanip> // For std::setfill, std::setw

class Processor {
public:
    static constexpr size_t MEMORY_SIZE = 65536; // 2^16

    uint16_t PC_; // Program Counter
    uint16_t AC_; // Accumulator

    Processor();

    uint16_t readMemory(uint16_t address);
    void writeMemory(uint16_t address, uint16_t value);
    void printState() const;
    void incrementPC();

private:
    std::vector<uint16_t> mem_;

    // Helper method to print memory around a specific address
    // Made private as it's primarily a helper for readMemory and writeMemory logging
    void printMemory(uint16_t address) const; 
};
