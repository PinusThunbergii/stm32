cmake_minimum_required(VERSION 3.10)
project(barebone C)

set(TOOLCHAIN_PREFIX arm-none-eabi-)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_LINKER ${TOOLCHAIN_PREFIX})
set(LINKER_SCRIPT "linker-script/stm32f103c8t6.ld")
set(CMAKE_C_FLAGS "-mcpu=cortex-m3 -mthumb -nostdlib -o0 -g -T ${PROJECT_SOURCE_DIR}/${LINKER_SCRIPT}")

add_executable(main main.c)
set_target_properties(main PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
#add_custom_target()
message(STATUS ${CMAKE_C_COMPILER})