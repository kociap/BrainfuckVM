cmake_minimum_required(VERSION 3.12)
project(BrainfuckVM)

add_executable(BrainfuckVM 
    "${CMAKE_CURRENT_SOURCE_DIR}/BrainfuckVM.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/BrainfuckVM.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

target_compile_definitions(BrainfuckVM PRIVATE COMPILER_CLANG=1 COMPILER_GCC=2 COMPILER_MSVC=3)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    target_compile_definitions(BrainfuckVM PRIVATE COMPILER_ID=1)
    if(MSVC)
        # Clang driver does not recognize -pedantic
        target_compile_options(BrainfuckVM PRIVATE
            -Wall -Wextra /clang:-pedantic
            -Wno-c++98-compat -Wno-c++98-compat-pedantic
        )
    else()
        target_compile_options(BrainfuckVM PRIVATE
            -Wall -Wextra -pedantic
            -Wno-c++98-compat -Wno-c++98-compat-pedantic
        )
    endif()
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    target_compile_definitions(BrainfuckVM PRIVATE COMPILER_ID=2)
    target_compile_options(BrainfuckVM PRIVATE
        -Wall -Wextra -pedantic
        -Wno-c++98-compat -Wno-c++98-compat-pedantic
    )
elseif(MSVC)
    target_compile_definitions(BrainfuckVM PRIVATE COMPILER_ID=3)
    target_compile_options(BrainfuckVM PRIVATE
        /Wall
    )
else()
    message(FATAL "Unknown compiler")
endif()
