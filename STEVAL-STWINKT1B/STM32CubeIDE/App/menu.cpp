//=============================================================================
//! \file menu.c
//!       Menu configuration
//! \author Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "LEDs.hpp"
#include "menu.hpp"

static char* Number_to_BinaryString( const int Number, char *buf );

//-----------------------------------------------------------------------------
// !\brief Display menu options
//-----------------------------------------------------------------------------
int Menu_Options(void)
{
  printf("Menu Options:\r\n");
  return 0;
}

//-----------------------------------------------------------------------------
//! \brief Display menu options
//-----------------------------------------------------------------------------
int Menu_Processing( const uint8_t oneChar )
{
  switch( oneChar )
  {
    case 'M':                                    Menu_Options()  ;  break;
    default :  printf("Char = %02X = %d ('%c')\r\n", oneChar, oneChar, oneChar ); break;
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

