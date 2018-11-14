cmake_minimum_required(VERSION 3.10)
project(barebone C)

set(TOOLCHAIN_PREFIX arm-none-eabi-)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_LINKER ${TOOLCHAIN_PREFIX})
set(CMAKE_C_FLAGS "-mcpu=cortex-m3 -mthumb -nostdlib -o0 -g")
add_executable(main main.c)

#add_custom_target()
message(STATUS ${CMAKE_C_COMPILER})