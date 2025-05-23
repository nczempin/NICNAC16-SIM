#include "processor.hpp"
#include <iostream>
#include <iomanip> // For std::setfill, std::setw, std::hex
#include <stdexcept> // For std::out_of_range (optional, for bounds checking)

Processor::Processor() : PC_(0), AC_(0) {
    mem_.resize(MEMORY_SIZE, 0);
}

uint16_t Processor::readMemory(uint16_t address) {
    // Basic bounds checking
    if (address >= MEMORY_SIZE) {
        // In a real scenario, might throw or handle error differently
        std::cerr << "Error: Read attempt outside memory bounds at address " << std::hex << address << std::endl;
        // Returning 0 or a specific error code might be alternatives
        // For now, let's throw an exception to be explicit about the error.
        throw std::out_of_range("Memory read access out of bounds");
    }
    // printMemory(address); // Logging can be verbose, enable if needed for debugging
    return mem_[address];
}

void Processor::writeMemory(uint16_t address, uint16_t value) {
    // Basic bounds checking
    if (address >= MEMORY_SIZE) {
        std::cerr << "Error: Write attempt outside memory bounds at address " << std::hex << address << std::endl;
        throw std::out_of_range("Memory write access out of bounds");
    }
    mem_[address] = value;
    // printMemory(address); // Logging can be verbose, enable if needed for debugging
}

void Processor::printMemory(uint16_t address) const {
    uint16_t startAddress = (address / 8) * 8;
    std::cout << "Memory at 0x" << std::hex << std::setfill('0') << std::setw(4) << startAddress << ":";
    for (int i = 0; i < 8; ++i) {
        uint16_t currentAddress = startAddress + i;
        if (currentAddress >= MEMORY_SIZE) break; // Ensure we don't read past memory end

        if (currentAddress == address) {
            std::cout << " *" << std::setfill('0') << std::setw(4) << mem_[currentAddress];
        } else {
            std::cout << "  " << std::setfill('0') << std::setw(4) << mem_[currentAddress];
        }
    }
    std::cout << std::dec << std::endl; // Switch back to decimal for subsequent prints if any
}

void Processor::printState() const {
    std::cout << "\nPC: " << std::hex << std::setfill('0') << std::setw(4) << PC_
              << ", AC: " << std::setfill('0') << std::setw(4) << AC_
              << std::dec << std::endl; // Switch back to decimal
    printMemory(PC_); // Show memory around Program Counter
}

void Processor::incrementPC() {
    PC_++;
    // Handle PC overflow if 65536 is a hard limit and PC should wrap or error
    // For now, simple increment. If PC_ is uint16_t, it will wrap naturally.
}
