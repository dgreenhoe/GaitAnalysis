//=============================================================================
//! \author Daniel J. Greenhoe
//! \file   AppMain.cpp
//!         Main application processing
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
//#include "io.h"
#include "LEDs.hpp"
#include "menu.hpp"
#include "ISM330DHCX.hpp"

//-----------------------------------------------------------------------------
//! \brief App Main
//-----------------------------------------------------------------------------

extern "C" void AppMain(void);
extern "C" bool GetOneByte( uint8_t* OneByte );

void Splash(void);

//-----------------------------------------------------------------------------
//! \brief App Main
//-----------------------------------------------------------------------------
void AppMain(void)
{
  uint8_t OneByte;
  Splash();
  ISM330DHCX_Init();
  while(1)
  {
    bool ByteReceived = GetOneByte( &OneByte );
    if( ByteReceived )
      Menu_Processing( OneByte );
    LED_StateMachine();
  }
}

//-----------------------------------------------------------------------------
//! \brief Splash Screen
//-----------------------------------------------------------------------------
void Splash(void)
{
  printf( " ===========================================\r\n"  );
  printf( "| Gait Analysis                             |\r\n" );
  printf( "| https://github.com/dgreenhoe/GaitAnalysis |\r\n" );
  printf( " ===========================================\r\n"  );
}

