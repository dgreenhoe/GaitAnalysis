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

static char* Number_to_BinaryString( const int Number, char *buf );
void CDC_Receive_Clear(void);

//-----------------------------------------------------------------------------
// !\brief Display menu options
//-----------------------------------------------------------------------------
int Menu_Options(void)
{
  printf("Menu Options:\r\n");
  printf(" %-30s ", "m: This menu"         );  printf("| %-30s\r\n", "M: This menu"               );
  printf(" %-30s ", "1: ISM330DHCX Init"   );  printf("| %-30s\r\n", "2: ISM330DHCX Chip ID\r\n"  );
  return 0;
}

//-----------------------------------------------------------------------------
//! \brief Display menu options
//-----------------------------------------------------------------------------
int Menu_Processing( const uint8_t oneChar )
{
  switch( oneChar )
  {
    case  0 :                         break;
    case 'm':
    case 'M': Menu_Options()   ;      break;
    case '1': ISM330DHCX_Init();      break;
    case '2': ISM330DHCX_GetChipID(); break;
    default : printf("oneChar = %02X = %d ('%c')\r\n", oneChar, oneChar, oneChar ); 
  }
  return 0;
}

//-----------------------------------------------------------------------------
//! \brief Convert 8 bit number to binary string.
//-----------------------------------------------------------------------------
static char* Number_to_BinaryString( const int Number, char *buf )
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

