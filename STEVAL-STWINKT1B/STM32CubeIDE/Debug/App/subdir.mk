################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/io.c 

CPP_SRCS += \
../App/AppMain.cpp \
../App/ISM330DHCX.cpp \
../App/LEDs.cpp \
../App/menu.cpp 

C_DEPS += \
./App/io.d 

OBJS += \
./App/AppMain.o \
./App/ISM330DHCX.o \
./App/LEDs.o \
./App/io.o \
./App/menu.o 

CPP_DEPS += \
./App/AppMain.d \
./App/ISM330DHCX.d \
./App/LEDs.d \
./App/menu.d 


# Each subdirectory must supply rules for building sources it contributes
App/%.o: ../App/%.cpp App/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4R9xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/dan/personal/Repos/GaitAnalysis/STEVAL-STWINKT1B/STM32CubeIDE/App" -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
App/%.o: ../App/%.c App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4R9xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/dan/personal/Repos/GaitAnalysis/STEVAL-STWINKT1B/STM32CubeIDE/App" -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App

clean-App:
	-$(RM) ./App/AppMain.d ./App/AppMain.o ./App/ISM330DHCX.d ./App/ISM330DHCX.o ./App/LEDs.d ./App/LEDs.o ./App/io.d ./App/io.o ./App/menu.d ./App/menu.o

.PHONY: clean-App

