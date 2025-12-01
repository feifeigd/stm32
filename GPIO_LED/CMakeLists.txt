# GPIO_LED项目的CMakeLists.txt

# 源文件
set(GPIO_LED_SRC
	User/main.cpp
	User/stm32f10x_it.c
)

# 创建可执行目标
add_executable(gpio_led.elf ${GPIO_LED_SRC})

# 链接库
target_link_libraries(gpio_led.elf stmcpp stm32f10x_std_periph_driver)
