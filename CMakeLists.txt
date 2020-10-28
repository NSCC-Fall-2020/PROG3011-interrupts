set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_SYSTEM_VERSION 1)

cmake_minimum_required(VERSION 3.17)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_C_COMPILER arm-none-eabi-gcc.exe)
set(CMAKE_ASM_COMPILER arm-none-eabi-as.exe)

project(hello_arm C ASM)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-O0 -mcpu=cortex-m0plus -mthumb -Wall -nostartfiles")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m0plus -mthumb")

add_link_options(-T${CMAKE_SOURCE_DIR}/stm32.ld)
add_link_options(--specs=nosys.specs)

add_executable(hello_arm.elf
        main.c
        startup.s
        stm32.ld)
