
set(TOOLCHAIN_PATH "C:/Keil_v5/ARM/ARMCLANG/bin")

# 设置交叉编译目标系统
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m3)
set(CMAKE_SYSTEM_ARCH armv7-m)

# 设置编译器
set(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}/armclang.exe")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/armclang.exe")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH}/armasm.exe")

# 设置链接器
set(CMAKE_C_LINK_EXECUTABLE "${TOOLCHAIN_PATH}/armlink.exe")
set(CMAKE_CXX_LINK_EXECUTABLE "${TOOLCHAIN_PATH}/armlink.exe")
set(CMAKE_ASM_LINK_EXECUTABLE "${TOOLCHAIN_PATH}/armlink.exe")

# 设置编译器和链接器标志
set(CMAKE_C_FLAGS "-march=armv7-m -mcpu=cortex-m3 -O0 -g" CACHE STRING "C compiler flags")
set(CMAKE_CXX_FLAGS "-march=armv7-m -mcpu=cortex-m3 -O0 -g" CACHE STRING "CXX compiler flags")
set(CMAKE_ASM_FLAGS "-march=armv7-m -mcpu=cortex-m3 -O0 -g" CACHE STRING "ASM compiler flags")
set(CMAKE_EXE_LINKER_FLAGS "--scatter C:/Keil_v5/ARM/ARMCLANG/bin/../lib/linker/arm/ scatter.sct" CACHE STRING "Linker flags")

set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_ASM_COMPILER_WORKS TRUE)
