//=============================================================================
//! \file menu.cpp
//!       Menu configuration
//! \author Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "LEDs.hpp"
#include "spi.hpp"
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
  uint8_t ChipID = 0x00;
  char    Buf[16];
  switch( oneChar )
  {
    case 'm':
    case 'M':
      Splash();
      Options();
      break;
    case '1': ISM330DHCX::Init();
      break;
    case '2':
      ISM330DHCX::GetChipID( &ChipID );
      printf( "Chip ID = 0x%02X = %sb\r\n", ChipID, Number_to_BinaryString( (const int)ChipID, Buf ) );
      break;
    case  0 :
      break;
    case '3': HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET );  printf( "PB3 Lo CLK\r\n"  ); break;
    case '#': HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET   );  printf( "PB3 Hi CLK\r\n"  ); break;
    case '4': HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET );  printf( "PB4 Lo MISO\r\n" ); break;
    case '$': HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET   );  printf( "PB4 Hi MISO\r\n" ); break;
    case '5': HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET );  printf( "PB5 Lo MOSI\r\n" ); break;
    case '%': HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET   );  printf( "PB5 Hi MOSI\r\n" ); break;
    case 'x': HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET );  break;
    case 'y': HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET );  break;
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

