set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.20)

# specify cross compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project(misaka-bms C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_compile_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()

add_definitions(-DUSE_FULL_LL_DRIVER
                -DUSE_HAL_DRIVER
                -DSTM32F103xB)

set(linker_script ${CMAKE_SOURCE_DIR}/gcc/STM32F103C8Tx_FLASH.ld)

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
add_link_options(-T ${linker_script})

file(GLOB_RECURSE src_file
     "cubemx/Core/Src/*.c"
     "app/app_main.c"
     "cubemx/Drivers/STM32F1xx_HAL_Driver/Src/*.c"
     )

file(GLOB_RECURSE no_src_file "cubemx/Drivers/STM32F1xx_HAL_Driver/Src/*template.c")

list(REMOVE_ITEM src_file ${no_src_file})

include_directories( cubemx/Core/Inc
                     cubemx/Drivers/STM32F1xx_HAL_Driver/Inc
                     cubemx/Drivers/STM32F1xx_HAL_Driver/Inc
                     cubemx/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
                     cubemx/Drivers/CMSIS/Device/ST/STM32F1xx/Include
                     cubemx/Drivers/CMSIS/Include
                     )

add_executable(${PROJECT_NAME}.elf "gcc/startup_stm32f103xb.s" ${src_file} ${linker_script})

set(hex_file ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(bin_file ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${hex_file}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${bin_file}
        COMMENT "Building ${hex_file}
        Building ${bin_file}")
