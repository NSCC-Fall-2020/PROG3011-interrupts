set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_SYSTEM_VERSION 1)

cmake_minimum_required(VERSION 3.17)

set(CMAKE_C_COMPILER_WORKS 1)
unset(CMAKE_CXX_COMPILER)
set(toolchain "C:/Program Files (x86)/GNU Arm Embedded Toolchain/bin")
set(CMAKE_C_COMPILER ${toolchain}/arm-none-eabi-gcc.exe)
set(CMAKE_ASM_COMPILER ${toolchain}/arm-none-eabi-as.exe)

project(semihosting C ASM)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-mcpu=cortex-m0plus -mthumb -Wall -Wno-main -nostartfiles -fomit-frame-pointer")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m0plus -mthumb")

set(CMAKE_ASM_FLAGS_DEBUG "-g3")
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0")

set(CMAKE_ASM_FLAGS_RELEASE "")
set(CMAKE_C_FLAGS_RELEASE "-O0 -DNDEBUG=1")

add_link_options(-T${CMAKE_SOURCE_DIR}/stm32.ld)
add_link_options(--specs=nosys.specs)

add_executable(semihosting.elf
        main.c
        startup.s
        stm32.ld)
