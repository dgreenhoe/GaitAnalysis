//=============================================================================
//! \file ISM330DHCX.cpp
//!       6-Axis sensor
//! \author Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "io.h"
#include "main.h"
#include "LEDs.hpp"
#include "spi.hpp"
#include "ISM330DHCX.hpp"

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
HAL_StatusTypeDef ISM330DHCX::Init(void)
{
  HAL_StatusTypeDef const Status  = HAL_OK;
  int     const Device   = SPI_ISM330DHCX;
  //uint8_t const Register = REG_FUNC_CFG_ACCESS;
  //uint8_t const RegVal   = BIT_FUNC_CFG_ACCESS | BIT_SHUB_REG_ACCESS;
  //spi::WriteOneByte( Device, Register, RegVal );
  spi::WriteOneByte( Device, REG_FUNC_CFG_ACCESS, 0x00 );
  spi::WriteOneByte( Device, REG_CTRL1_XL,        0x50 );
  spi::WriteOneByte( Device, REG_CTRL2_G,         0x50 );
  spi::WriteOneByte( Device, REG_CTRL3_C,         0x02 );
  spi::WriteOneByte( Device, REG_CTRL4_C,         0x4C );
  spi::WriteOneByte( Device, REG_CTRL5_C,         0x00 );
//spi::WriteOneByte( Device, REG_CTRL6_C,         0x00 );
//spi::WriteOneByte( Device, REG_CTRL7_G,         0x00 );
//spi::WriteOneByte( Device, REG_CTRL8_XL,        0x00 );
//spi::WriteOneByte( Device, REG_CTRL9_XL,        0x00 ); // "It is recommended to always set this bit to 1 during device configuration."
//spi::WriteOneByte( Device, REG_CTRL10_C,        0x00 );
//spi::WriteOneByte( Device, ALL_INT_SRC,         0x00 );


  return Status;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Get Chip ID
//-----------------------------------------------------------------------------
HAL_StatusTypeDef ISM330DHCX::SoftReset( void )
{
  uint8_t RegVal = 0x00;
  int     const Device   = SPI_ISM330DHCX;
  HAL_StatusTypeDef const Status1 = spi::ReadOneByte( Device, REG_CTRL3_C, &RegVal );
  HAL_StatusTypeDef const Status = spi::WriteOneByte( Device, REG_CTRL3_C, RegVal | 0x01 );
  return Status;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Get Chip ID
//-----------------------------------------------------------------------------
HAL_StatusTypeDef ISM330DHCX::GetChipID( uint8_t* ChipID )
{
  uint8_t            const Register  = REG_WHO_AM_I;
  uint8_t                  RxData[]  = { 0x00 };
  spi::ReadOneByte( SPI_ISM330DHCX, Register, &RxData[0] );
  uint8_t            const chipID    = RxData[0];
  HAL_StatusTypeDef  const Status    = ( chipID == 0x6B )? HAL_OK : HAL_ERROR;
  *ChipID = chipID;
  return Status;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Read Temperature
//-----------------------------------------------------------------------------
HAL_StatusTypeDef ISM330DHCX::ReadTemp( uint8_t* Temp )
{
  uint8_t            const RegLo     = REG_OUT_TEMP_L;
  uint8_t            const RegHi     = REG_OUT_TEMP_H;
  uint8_t                  RxData[]  = { 0x00, 0x00 };
  uint8_t            const RxSize    = sizeof( RxData ) / sizeof( uint8_t );
//spi::ReadNBytes( SPI_ISM330DHCX, RegLo, RxSize, &RxData[0] );
  spi::ReadOneByte( SPI_ISM330DHCX, RegLo, &RxData[0] );
  spi::ReadOneByte( SPI_ISM330DHCX, RegHi, &RxData[1] );
printf("RegLo=%02X %02X\r\n", RxData[0], RxData[1] );
  return HAL_OK;
}

