cmake_minimum_required(VERSION 3.10)
project(barebone C CXX)

#set(CMAKE_VERBOSE_MAKEFILE on)

set(TOOLCHAIN_PREFIX arm-none-eabi-)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_LINKER ${TOOLCHAIN_PREFIX}ld)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

set(LINKER_SCRIPT "linker-script/stm32f103c8t6.ld")
set(CMAKE_C_FLAGS "-mcpu=cortex-m3 -mthumb -Wall -g -nostdlib -nostartfiles -Wall -g  -fno-unwind-tables -fno-exceptions -fno-rtti") #-ffunction-sections -fno-unwind-tables  -fno-unwind-tables -fno-exceptions
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-T ${PROJECT_SOURCE_DIR}/${LINKER_SCRIPT}")
set(
    MYSOURCES 
    src/cxx_stub.c
    src/vectors.c
    src/startup.c
    src/main.cpp
    src/clock.c
    src/test_class.cpp
)
include_directories(third-party/CMSIS/CM3/DeviceSupport/ST/STM32F10x/ third-party/CMSIS/CM3/CoreSupport/)
#add_library(vectors src/vectors.c)
#add_library(startup src/startup.c)
#target_include_directories(startup PUBLIC third-party/CMSIS/CM3/DeviceSupport/ST/STM32F10x/ third-party/CMSIS/CM3/CoreSupport/) 

add_executable(${PROJECT_NAME} ${MYSOURCES})
#target_link_libraries(${PROJECT_NAME} vectors startup)

#Устанавливаем зависимость для ребилда при изменении скрипта линкера
set_target_properties(${PROJECT_NAME}  PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/${LINKER_SCRIPT})


add_custom_target(${PROJECT_NAME}.bin ALL DEPENDS ${PROJECT_NAME} COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin)
add_custom_target(${PROJECT_NAME}.hexdump ALL DEPENDS ${PROJECT_NAME}.bin COMMAND hd ${PROJECT_NAME}.bin > ${PROJECT_NAME}.hexdump)
add_custom_target(${PROJECT_NAME}.hex ALL DEPENDS ${PROJECT_NAME} COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME} ${PROJECT_NAME}.hex)
add_custom_target(${PROJECT_NAME}.lss ALL DEPENDS ${PROJECT_NAME} COMMAND ${CMAKE_OBJDUMP} -x -D  -d ${PROJECT_NAME} > ${PROJECT_NAME}.lss) #-S --source

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} ARGS ${PROJECT_NAME})