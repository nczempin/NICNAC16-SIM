#pragma once

#include <cstdint>
#include <memory>

// Forward declaration
class Processor;

class Instruction {
public:
    virtual ~Instruction() = default;
    virtual void execute(uint16_t word, Processor& p) = 0;
};

class NopInstruction : public Instruction {
public:
    void execute(uint16_t word, Processor& p) override;
};

class JmpInstruction : public Instruction {
public:
    void execute(uint16_t word, Processor& p) override;
};

class BlInstruction : public Instruction {
public:
    void execute(uint16_t word, Processor& p) override;
};

class RetInstruction : public Instruction {
public:
    void execute(uint16_t word, Processor& p) override;
};

class LdaInstruction : public Instruction {
public:
    void execute(uint16_t word, Processor& p) override;
};

class StaInstruction : public Instruction {
public:
    void execute(uint16_t word, Processor& p) override;
};

class AddInstruction : public Instruction {
public:
    void execute(uint16_t word, Processor& p) override;
};

class BanInstruction : public Instruction {
public:
    void execute(uint16_t word, Processor& p) override;
};
