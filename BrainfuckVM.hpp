#ifndef BRAINFUCK_VM_HPP_INCLUDE
#define BRAINFUCK_VM_HPP_INCLUDE

#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>

#define OPTIMIZE_BRAINFUCK 1

enum class Instruction {
    add,
    incr,
    prnt,
    read,
    jmp,
};

struct Bytecode_Op {
    Instruction op;
    int64_t value;
};

class Brainfuck_VM {
public:
    void load_program(std::string);
    void run() const;

private:
    std::vector<Bytecode_Op> bytecode;
};

#endif // !BRAINFUCK_VM_HPP_INCLUDE
