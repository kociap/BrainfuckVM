#include "BrainfuckVM.hpp"
#include <chrono>
#include <iostream>

int main() {
    Brainfuck_VM vm;
    vm.load_program(
        ">++[<+++++++++++++>-]<[[>+>+<<-]>[<+>-]++++++++[>++++++++<-]>.[-]<<>++++++++++[>++++++++++[>++++++++++[>++++++++++[>++++++++++[>++++++++++[>++++++++++"
        "[-]<-]<-]<-]<-]<-]<-]<-]++++++++++.");
    auto start = std::chrono::steady_clock::now();
    //for (int i = 0; i < 10; ++i) {
        vm.run();
    //}
    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time in milliseconds : " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " milliseconds"
              << std::endl;
    return 0;
}
