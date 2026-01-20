# Basic SMT32F4 Project

This is for a STM32F446 on Nucleo Board F446RE

### CMSIS Core [Link](https://github.com/STMicroelectronics/STM32CubeF4/tree/master/Drivers/CMSIS/Core/Include)

Need to following files:

```{bash}
cmsis_compiler.h
cmsis_gcc.h
cmsis_version.h
core_cm4.h
mpu_armv7.h
```

### CMSIS Device

Need the following files:
[Link](https://github.com/STMicroelectronics/cmsis-device-f4/tree/3c77349ce04c8af401454cc51f85ea9a50e34fc1/Include)

```{bash}
stm32f446xx.h
stm32f4xx.h
system_stm32f4xx.h
```

[Link](https://github.com/STMicroelectronics/cmsis-device-f4/tree/3c77349ce04c8af401454cc51f85ea9a50e34fc1/Source/Templates)

```{bash}
system_stm32f4xx.c
```

[Link](https://github.com/STMicroelectronics/cmsis-device-f4/tree/3c77349ce04c8af401454cc51f85ea9a50e34fc1/Source/Templates/gcc)

```{bash}
startup_stm32f446xx.s
```

Produce this file use a prebuild from STM32CudeIDE or STM32CUBEMx:

```{bash}
STM32F446RETX_FLASH.ld

```

### HAL-LL (Optional but recommended)

### Compile

```{bash}
cmake -S . -B build

```

### Flash

```{bash}
cd build
make flash-openocd
```
