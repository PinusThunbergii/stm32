cmake_minimum_required(VERSION 3.10)
project(barebone C)

set(TOOLCHAIN_PREFIX arm-none-eabi-)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_LINKER ${TOOLCHAIN_PREFIX}ld)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

set(LINKER_SCRIPT "linker-script/stm32f103c8t6.ld")
set(CMAKE_C_FLAGS "-mcpu=cortex-m3 -mthumb -nostdlib -o0 -g ")
set(CMAKE_EXE_LINKER_FLAGS "-T ${PROJECT_SOURCE_DIR}/${LINKER_SCRIPT}")

add_executable(${PROJECT_NAME} src/main.c src/vectors.c)

#Устанавливаем зависимость для ребилда при изменении скрипта линкера
set_target_properties(${PROJECT_NAME}  PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/${LINKER_SCRIPT})


add_custom_target(${PROJECT_NAME}.bin ALL DEPENDS ${PROJECT_NAME} COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin)
add_custom_target(${PROJECT_NAME}.hex ALL DEPENDS ${PROJECT_NAME} COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME} ${PROJECT_NAME}.hex)
add_custom_target(${PROJECT_NAME}.lss ALL DEPENDS ${PROJECT_NAME} COMMAND ${CMAKE_OBJDUMP} -x -D -d ${PROJECT_NAME} > ${PROJECT_NAME}.lss)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} ARGS ${PROJECT_NAME})