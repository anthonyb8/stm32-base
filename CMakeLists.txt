cmake_minimum_required(VERSION 3.22)

# Generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set toolchain file before project()
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/toolchain-arm-none-eabi.cmake)

# Project name and languages
project(stm32f446_base C ASM)

# MCU specific settings
set(MCU_FAMILY STM32F4xx)
set(MCU_MODEL STM32F446xx)
set(CPU_TYPE cortex-m4)
set(FPU_TYPE fpv4-sp-d16)
set(FLOAT_ABI hard)

# Startup and linker script files
set(STARTUP_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/templates/startup_stm32f446xx.s)
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32F446RETx_FLASH.ld)

# Compiler flags
set(CPU_FLAGS "-mcpu=${CPU_TYPE} -mthumb -mfpu=${FPU_TYPE} -mfloat-abi=${FLOAT_ABI}")
set(COMMON_FLAGS "${CPU_FLAGS} -Wall -Wextra -fdata-sections -ffunction-sections")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu11")
set(CMAKE_ASM_FLAGS "${CPU_FLAGS}")

# Build type specific flags
set(CMAKE_C_FLAGS_DEBUG "-Og -g3 -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CPU_FLAGS} -specs=nano.specs -T${LINKER_SCRIPT} -Wl,--gc-sections -Wl,-Map=${PROJECT_NAME}.map")

# CMSIS include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/core
    ${CMAKE_CURRENT_SOURCE_DIR}/include/device
)

# Defines
add_definitions(
    -D${MCU_MODEL}
    -DUSE_FULL_ASSERT
)

# Source files
set(SOURCES
    src/main.c
    src/templates/system_stm32f4xx.c
    ${STARTUP_FILE}
)

# Executable
add_executable(${PROJECT_NAME}.elf ${SOURCES})

# Post-build commands to generate hex and bin files
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
    COMMENT "Building HEX and BIN files"
)

# Flash target (using ST-Link)
add_custom_target(flash
    COMMAND st-flash write ${PROJECT_NAME}.bin 0x8000000
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Flashing target hardware"
)

# Alternative flash target using OpenOCD
add_custom_target(flash-openocd
    COMMAND openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program ${PROJECT_NAME}.elf verify reset exit"
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Flashing with OpenOCD"
)

# Clean extras
set_directory_properties(PROPERTIES ADDITIONAL_CLEAN_FILES
    "${PROJECT_NAME}.hex;${PROJECT_NAME}.bin;${PROJECT_NAME}.map"
)
