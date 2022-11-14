//=============================================================================
//! \author Daniel J. Greenhoe
//! \file   LEDs.cpp
//!         LED control
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "io.h"
#include "main.h"
#include "LEDs.hpp"

enum class LED_States
{
  LED_Grn0_Org0,
  LED_Grn0_Org0_Hold,
  LED_Grn0_Org1,
  LED_Grn0_Org1_Hold,
  LED_Grn1_Org0,
  LED_Grn1_Org0_Hold,
  LED_Grn1_Org1,
  LED_Grn1_Org1_Hold
};

inline void LED_Grn_On ( void ){ HAL_GPIO_WritePin(GPIOE, LED1_Pin, GPIO_PIN_SET  ); }
inline void LED_Grn_Off( void ){ HAL_GPIO_WritePin(GPIOE, LED1_Pin, GPIO_PIN_RESET); }
inline void LED_Org_On ( void ){ HAL_GPIO_WritePin(GPIOD, LED2_Pin, GPIO_PIN_SET  ); }
inline void LED_Org_Off( void ){ HAL_GPIO_WritePin(GPIOD, LED2_Pin, GPIO_PIN_RESET); }

static LED_States LED_State = LED_States::LED_Grn0_Org0;
//-----------------------------------------------------------------------------
//! \brief App Main
//-----------------------------------------------------------------------------
void LED_StateMachine(void)
{
  switch( LED_State )
  {
    case LED_States::LED_Grn0_Org0:
      LED_Grn_Off();
      LED_Org_Off();
      LED_State = LED_States::LED_Grn0_Org0_Hold;
      break;
    case LED_States::LED_Grn0_Org0_Hold:
      HAL_Delay(200);
      LED_State = LED_States::LED_Grn0_Org1;
      break;

    case LED_States::LED_Grn0_Org1:
      LED_Grn_Off();
      LED_Org_On();
      LED_State = LED_States::LED_Grn0_Org1_Hold;
      break;
    case LED_States::LED_Grn0_Org1_Hold:
      HAL_Delay(200);
      LED_State = LED_States::LED_Grn1_Org0;
      break;

    case LED_States::LED_Grn1_Org0:
      LED_Grn_On();
      LED_Org_Off();
      LED_State = LED_States::LED_Grn1_Org0_Hold;
      break;
    case LED_States::LED_Grn1_Org0_Hold:
      HAL_Delay(200);
      LED_State = LED_States::LED_Grn1_Org1;
      break;

    case LED_States::LED_Grn1_Org1:
      LED_Grn_On();
      LED_Org_On();
      LED_State = LED_States::LED_Grn1_Org1_Hold;
      break;
    case LED_States::LED_Grn1_Org1_Hold:
      HAL_Delay(200);
      LED_State = LED_States::LED_Grn0_Org0;
      break;

    default:
      LED_State = LED_States::LED_Grn0_Org0;
      break;
  }
}