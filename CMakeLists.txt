cmake_minimum_required(VERSION 3.10)

# 设置CMP0123策略，抑制ARMClang cpu/arch标志警告
cmake_policy(SET CMP0123 NEW)

# 设置交叉编译工具链
set(CMAKE_TOOLCHAIN_FILE ./toolchain.cmake)

# 设置项目名称
project(stm32)

# 明确指定编译器命令行，包含所有必要的包含路径
set(CMAKE_C_COMPILE_OBJECT "${CMAKE_C_COMPILER} -c <SOURCE> -o <OBJECT> --target=arm-arm-none-eabi -march=armv7-m -mcpu=cortex-m3 -O0 -g -I${CMAKE_CURRENT_SOURCE_DIR} -I${PACKS_PATH}/ARM/CMSIS/5.9.0/CMSIS/Core/Include -I${PACKS_PATH}/Keil/STM32F1xx_DFP/2.4.1/Device/Include -I${PACKS_PATH}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc -I${CMAKE_CURRENT_SOURCE_DIR}/stmcpp -I${CMAKE_CURRENT_SOURCE_DIR}/GPIO_LED/User")
set(CMAKE_CXX_COMPILE_OBJECT "${CMAKE_CXX_COMPILER} -c <SOURCE> -o <OBJECT> --target=arm-arm-none-eabi -march=armv7-m -mcpu=cortex-m3 -O0 -g -I${CMAKE_CURRENT_SOURCE_DIR} -I${PACKS_PATH}/ARM/CMSIS/5.9.0/CMSIS/Core/Include -I${PACKS_PATH}/Keil/STM32F1xx_DFP/2.4.1/Device/Include -I${PACKS_PATH}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc -I${CMAKE_CURRENT_SOURCE_DIR}/stmcpp -I${CMAKE_CURRENT_SOURCE_DIR}/GPIO_LED/User")
#include(./toolchain.cmake)
set(PACKS_PATH C:/Users/Administrator/AppData/Local/Arm/Packs)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${PACKS_PATH}/ARM/CMSIS/5.9.0/CMSIS/Core/Include
	${PACKS_PATH}/Keil/STM32F1xx_DFP/2.4.1/Device/Include
	${PACKS_PATH}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc
	${CMAKE_CURRENT_SOURCE_DIR}/stmcpp
)

# -xc -std=c90 --target=arm-arm-none-eabi -mcpu=cortex-m3 -c
# -fno-rtti -funsigned-char -fshort-enums -fshort-wchar
# -D__EVAL -gdwarf-4 -O0 -ffunction-sections -Wno-packed -Wno-missing-variable-declarations -Wno-missing-prototypes -Wno-missing-noreturn -Wno-sign-conversion -Wno-nonportable-include-path -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality -Wno-reserved-identifier -Wno-covered-switch-default -Wno-unreachable-code-break -I StdPeriph_Driver/inc -I User -I ../stmcpp
# -I./RTE/Device/STM32F103C8
# -I./RTE/_Target_1
# -IC:/Users/Administrator/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include
# -IC:/Users/Administrator/AppData/Local/Arm/Packs/Keil/STM32F1xx_DFP/2.4.1/Device/Include
# -IC:/Users/Administrator/AppData/Local/Arm/Packs/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/inc
# -IC:/Users/Administrator/AppData/Local/Arm/Packs/Keil/STM32F1xx_DFP/2.4.1/RTE_Driver
# -D__UVISION_VERSION="538" -D_RTE_ -DSTM32F10X_MD -D_RTE_ -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD
# -o ./Objects/*.o -MD

add_definitions(
	-DUSE_STDPERIPH_DRIVER
	-DSTM32F10X_MD
)

add_subdirectory(stmcpp)

# 添加STM32标准外设库
set(STM32F10X_STD_PERIPH_DRIVER_SRC
	${PACKS_PATH}/Keil/STM32F1xx_DFP/2.4.1/Device/Source/system_stm32f10x.c
	${PACKS_PATH}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/misc.c
	${PACKS_PATH}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/stm32f10x_gpio.c
	${PACKS_PATH}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/stm32f10x_rcc.c
	${PACKS_PATH}/Keil/STM32F1xx_DFP/2.4.1/Device/StdPeriph_Driver/src/stm32f10x_usart.c
)

# 创建标准外设库
add_library(stm32f10x_std_periph_driver ${STM32F10X_STD_PERIPH_DRIVER_SRC})

# 强制包含assert.h文件，定义assert_param宏
target_compile_options(stm32f10x_std_periph_driver PRIVATE -include ${CMAKE_CURRENT_SOURCE_DIR}/assert.h)

# 接入GPIO_LED项目
add_subdirectory(GPIO_LED)

