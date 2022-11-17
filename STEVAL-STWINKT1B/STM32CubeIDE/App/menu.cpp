//=============================================================================
//! \file menu.cpp
//!       Menu configuration
//! \author Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "LEDs.hpp"
#include "ISM330DHCX.hpp"
#include "menu.hpp"

//-----------------------------------------------------------------------------
// !\brief Display menu options
//-----------------------------------------------------------------------------
int UserInterface::Options(void)
{
  printf("Menu Options:\r\n");
  printf(" %-30s ", "m: This menu"         );  printf("| %-30s\r\n", "M: This menu"               );
  printf(" %-30s ", "1: ISM330DHCX Init"   );  printf("| %-30s\r\n", "2: ISM330DHCX Chip ID\r\n"  );
  return 0;
}

//-----------------------------------------------------------------------------
//! \brief Display menu options
//-----------------------------------------------------------------------------
int UserInterface::Processing( const uint8_t oneChar )
{
  switch( oneChar )
  {
    case 'm':
    case 'M': Options();               break;
    case '1': ISM330DHCX::Init();      break;
    case '2': ISM330DHCX::GetChipID(); break;
    case  0 :                          break;
    default : printf("oneChar = %02X = %d ('%c')\r\n", oneChar, oneChar, oneChar ); 
  }
  return 0;
}

//-----------------------------------------------------------------------------
//! \brief Splash Screen
//-----------------------------------------------------------------------------
void UserInterface::Splash(void)
{
  printf( " ===========================================\r\n"  );
  printf( "| Gait Analysis                             |\r\n" );
  printf( "| https://github.com/dgreenhoe/GaitAnalysis |\r\n" );
  printf( " ===========================================\r\n"  );
}

//-----------------------------------------------------------------------------
//! \brief Convert 8 bit number to binary string.
//-----------------------------------------------------------------------------
char* UserInterface::Number_to_BinaryString( const int Number, char *buf )
{
  int Mask = 0x0080;
  for( int i=0; i<=8; i++ )
  {
    buf[i] = ( Number & Mask )? '1' : '0';
    Mask >>= 1;
    if( i==3 )
    {
      i++;
      buf[i] = '_';
    }
  }
  buf[9] = '\0';
  return buf;
}

