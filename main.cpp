#include "BrainfuckVM.hpp"

int main() {
	Brainfuck_VM vm;
	vm.load_program("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.");
	vm.run();
	return 0;
}