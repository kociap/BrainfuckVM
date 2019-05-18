#include "BrainfuckVM.hpp"
#include <chrono>
#include <iostream>

int main() {
    Brainfuck_VM vm;
    vm.load_program(">++[<+++++++++++++>-]<[[>+>+<<-]>[<+>-]++++++++[>++++++++<-]>.[-]<<>++++++++++[>++++++++++[>++++++++++[>++++++++++[>++++++++++[>++++++++++[>++++++++++[-]<-]<-]<-]<-]<-]<-]<-]++++++++++.");
    vm.run();
    return 0;
}