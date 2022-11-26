//=============================================================================
//! \author Daniel J. Greenhoe
//! \file   AppMain.cpp
//!         Main application processing
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "LEDs.hpp"
#include "spi.hpp"
#include "ISM330DHCX.hpp"
#include "menu.hpp"
#include "AppMain.hpp"
//#include "AppMain.h"

AppMain appmain;

//-----------------------------------------------------------------------------
//! \brief App Main
//-----------------------------------------------------------------------------

extern "C" void AppMain(void);
extern "C" bool GetOneByte( uint8_t* OneByte );

//-----------------------------------------------------------------------------
//! \brief App Main
//-----------------------------------------------------------------------------
void AppMain(void)
{
  uint8_t OneByte;
  appmain.SystemInit();
  appmain.AppMainLoop();
}

//-----------------------------------------------------------------------------
//! \brief App Main
//-----------------------------------------------------------------------------
void AppMain::SystemInit(void)
{
  spi::Init();
  ISM330DHCX::Init();
}

//-----------------------------------------------------------------------------
//! \brief App Main
//-----------------------------------------------------------------------------
void AppMain::AppMainLoop(void)
{
  uint8_t OneByte;
  UserInterface::Splash();

  while(1)
  {
    bool ByteReceived = GetOneByte( &OneByte );
    if( ByteReceived )
      UserInterface::Processing( OneByte );
    LEDs::StateMachine();
  }
}

