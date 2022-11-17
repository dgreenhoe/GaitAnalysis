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


static LED_States LED_State = LED_States::LED_Grn0_Org0;
static uint32_t TickStart = 0;
//-----------------------------------------------------------------------------
//! \brief App Main
//-----------------------------------------------------------------------------
void LEDs::StateMachine(void)
{
  uint32_t TickNow = HAL_GetTick();

  switch( LED_State )
  {
    case LED_States::LED_Grn0_Org0:
      Green_Off();
      Orange_Off();
      LED_State = LED_States::LED_Grn0_Org0_Hold;
      TickStart = TickNow;
    //printf( "Tick = %6ld ms\r\n", TickNow );
      break;
    case LED_States::LED_Grn0_Org0_Hold:
      if( TickNow - TickStart >= 500 )
        LED_State = LED_States::LED_Grn0_Org1;
      break;

    case LED_States::LED_Grn0_Org1:
      Green_Off();
      Orange_On();
      LED_State = LED_States::LED_Grn0_Org1_Hold;
      TickStart = TickNow;
      break;
    case LED_States::LED_Grn0_Org1_Hold:
      if( TickNow - TickStart >= 500 )
        LED_State = LED_States::LED_Grn1_Org0;
      break;

    case LED_States::LED_Grn1_Org0:
      Green_On();
      Orange_Off();
      LED_State = LED_States::LED_Grn1_Org0_Hold;
      TickStart = TickNow;
      break;
    case LED_States::LED_Grn1_Org0_Hold:
      if( TickNow - TickStart >= 500 )
        LED_State = LED_States::LED_Grn1_Org1;
      break;

    case LED_States::LED_Grn1_Org1:
      Green_On();
      Orange_On();
      LED_State = LED_States::LED_Grn1_Org1_Hold;
      TickStart = TickNow;
      break;
    case LED_States::LED_Grn1_Org1_Hold:
      if( TickNow - TickStart >= 500 )
        LED_State = LED_States::LED_Grn0_Org0;
      break;

    default:
      LED_State = LED_States::LED_Grn0_Org0;
      break;
  }

}