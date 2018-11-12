cmake_minimum_required(VERSION 3.10)
project(barebone C)

#set(TOOLCHAIN_PREFIX arm-none-eabi-)

#set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
#set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
#set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)

function(foo)
    message(${test})
    set(test 2 PARENT_SCOPE)
    message(${test} PARENT_SCOPE)
endfunction(foo)    
set(test 1)
foo()
message(${test})

set(items_to_buy apple orange pear bear)

foreach(item ${items_to_buy})
    message("Don`t forget to buy one ${item}")
endforeach()

#option(USE_DARK_POWER "Do you want to use the dark power?")
set(USE_DARK_POWER OFF CACHE BOOL "Do you want to use the dark power?")
message("${USE_DARK_POWER}")
message(STATUS ${CMAKE_C_COMPILER})