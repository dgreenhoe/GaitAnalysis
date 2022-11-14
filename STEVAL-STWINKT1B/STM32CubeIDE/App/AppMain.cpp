//=============================================================================
//! \author Daniel J. Greenhoe
//! \file   AppMain.cpp
//!         Main application processing
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "io.h"
#include "main.h"

extern "C" void AppMain(void);

//-----------------------------------------------------------------------------
//! \brief App Main
//-----------------------------------------------------------------------------
void AppMain(void)
{
  while(1)
  {
    HAL_GPIO_WritePin(GPIOE, LED1_Pin, GPIO_PIN_SET);
    HAL_Delay(250);
    HAL_GPIO_WritePin(GPIOD, LED2_Pin, GPIO_PIN_SET);
    HAL_Delay(250);
    HAL_GPIO_WritePin(GPIOE, LED1_Pin, GPIO_PIN_RESET);
    HAL_Delay(250);
    HAL_GPIO_WritePin(GPIOD, LED2_Pin, GPIO_PIN_RESET);
    float pi = 3.14159265;
    printf("Hello your World!!! pi = %6.3f\r\n", pi );
  }
}
