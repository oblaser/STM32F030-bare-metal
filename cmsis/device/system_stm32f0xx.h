/*
author          Oliver Blaser
date            27.12.2024
*/



/*

    This file has to exist (it gets included), but is not really needed.

    The non existance of the function `SystemInit()` is no problem. It's defined weak in `startup_stm32*.s`. So the line `bl  SystemInit` in the startup code is
    still fine. See: https://developer.arm.com/documentation/dui0803/l/Image-Structure-and-Generation/Weak-references-and-definitions?lang=en.

*/
