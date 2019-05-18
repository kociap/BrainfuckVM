#ifndef BRAINFUCK_VM_HPP_INCLUDE
#define BRAINFUCK_VM_HPP_INCLUDE

#include <cstdint>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdio>

#define OPTIMIZE_BRAINFUCK

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
	void run();

private:
	std::vector<Bytecode_Op> bytecode;
};

#endif // !BRAINFUCK_VM_HPP_INCLUDE
