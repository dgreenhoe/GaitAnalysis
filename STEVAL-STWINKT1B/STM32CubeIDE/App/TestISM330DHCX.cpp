//=============================================================================
//! \file TestISM330DHCX.cpp
//!       Test routines on 6-Axis sensor
//! \author Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "spi.hpp"
#include "ISM330DHCX.hpp"
#include "TestISM330DHCX.hpp"

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
HAL_StatusTypeDef TestISM330::Display_Registers(void)
{
  uint8_t RxBuf[128];
  uint8_t const Register = 0x00;
  uint8_t const NumBytes = sizeof( RxBuf ) / sizeof ( uint8_t );
  for( uint8_t n=0; n<NumBytes; n++ ) RxBuf[n] = 0xAB;
  ISM330DHCX::ReadNBytes( Register, NumBytes, RxBuf );
  for( uint8_t n=0; n<NumBytes; n++ )
  {
    if( n%16==0 ) printf( "\r\n" );
    printf( " %02X", RxBuf[n] );
  }
  printf( "\r\n" );
  return HAL_OK;
}
