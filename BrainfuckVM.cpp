#include "BrainfuckVM.hpp"

void Brainfuck_VM::load_program(std::string program) {
    bytecode.clear();
    std::vector<uint64_t> loop_stack;
    bool break_op_accumulation = false;
    int64_t program_size = static_cast<int64_t>(program.size());
    for (int64_t i = 0; i < program_size; ++i) {
        char c = program[i];
#if defined(OPTIMIZE_BRAINFUCK) && OPTIMIZE_BRAINFUCK
        if (c == '+') {
            if (!break_op_accumulation && bytecode.size() != 0 && bytecode.back().op == Instruction::add) {
                ++bytecode.back().value;
                if (bytecode.back().value == 0) {
                    bytecode.pop_back();
                }
            } else {
                bytecode.push_back({Instruction::add, 1});
                break_op_accumulation = false;
            }
        } else if (c == '-') {
            if (!break_op_accumulation && bytecode.size() != 0 && bytecode.back().op == Instruction::add) {
                --bytecode.back().value;
                if (bytecode.back().value == 0) {
                    bytecode.pop_back();
                }
            } else {
                bytecode.push_back({Instruction::add, -1});
                break_op_accumulation = false;
            }
        } else if (c == '>') {
            if (!break_op_accumulation && bytecode.size() != 0 && bytecode.back().op == Instruction::incr) {
                ++bytecode.back().value;
                if (bytecode.back().value == 0) {
                    bytecode.pop_back();
                }
            } else {
                bytecode.push_back({Instruction::incr, 1});
                break_op_accumulation = false;
            }
        } else if (c == '<') {
            if (!break_op_accumulation && bytecode.size() != 0 && bytecode.back().op == Instruction::incr) {
                --bytecode.back().value;
                if (bytecode.back().value == 0) {
                    bytecode.pop_back();
                }
            } else {
                bytecode.push_back({Instruction::incr, -1});
                break_op_accumulation = false;
            }
        } else if (c == '[') {
            break_op_accumulation = true;
            loop_stack.push_back(bytecode.size());
        } else if (c == ']') {
            if (loop_stack.size() == 0) {
                bytecode.clear();
                throw std::runtime_error("Invalid instruction (" + std::to_string(i) + "): " + c + " missing loop opening");
            }

            int64_t jmp_offset = loop_stack.back() - bytecode.size();
            if (jmp_offset != 0) {
                bytecode.push_back({Instruction::jmp, jmp_offset});
            }
            loop_stack.pop_back();
        } else if (c == ',') {
            bytecode.push_back({Instruction::read, 0});
        } else if (c == '.') {
            bytecode.push_back({Instruction::prnt, 0});
        }
#else
        if (c == '+') {
            bytecode.push_back({Instruction::add, 1});
        } else if (c == '-') {
            bytecode.push_back({Instruction::add, -1});
        } else if (c == '>') {
            bytecode.push_back({Instruction::incr, 1});
        } else if (c == '<') {
            bytecode.push_back({Instruction::incr, -1});
        } else if (c == '[') {
            loop_stack.push_back(bytecode.size());
        } else if (c == ']') {
            if (loop_stack.size() == 0) {
                bytecode.clear();
                throw std::runtime_error("Invalid instruction (" + std::to_string(i) + "): " + c + " missing loop opening");
            }

            int64_t jmp_offset = loop_stack.back() - bytecode.size();
            if (jmp_offset != 0) {
                bytecode.push_back({Instruction::jmp, jmp_offset});
            }
            loop_stack.pop_back();
        } else if (c == ',') {
            bytecode.push_back({Instruction::read, 0});
        } else if (c == '.') {
            bytecode.push_back({Instruction::prnt, 0});
        }
#endif // OPTIMIZE_BRAINCUFK
    }

    if (loop_stack.size() != 0) {
        bytecode.clear();
        throw std::runtime_error("Missing loop end");
    }
}

void Brainfuck_VM::run() const {
    constexpr uint64_t mem_max = 50000;
    int64_t mem[mem_max] = {};
    int64_t mem_ptr = 0;
    for (Bytecode_Op const *offset = bytecode.data(), *bytecode_end = bytecode.data() + bytecode.size(); offset != bytecode_end;) {
        Bytecode_Op instr = *offset;
        switch (instr.op) {
        case Instruction::add:
            mem[mem_ptr] += instr.value;
            ++offset;
            break;
        case Instruction::incr:
            mem_ptr = (mem_ptr + instr.value) % mem_max;
            ++offset;
            break;
        case Instruction::jmp:
            if (mem[mem_ptr]) {
                offset += instr.value;
            } else {
                ++offset;
            }
            break;
        case Instruction::prnt:
            putchar(static_cast<char>(mem[mem_ptr]));
            ++offset;
            break;
        case Instruction::read:
            mem[mem_ptr] = getchar();
            ++offset;
            break;
        }
    }
}
