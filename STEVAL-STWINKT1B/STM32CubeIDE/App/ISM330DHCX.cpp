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
  return Status;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Get Chip ID
//-----------------------------------------------------------------------------
HAL_StatusTypeDef ISM330DHCX::GetChipID( uint8_t* ChipID )
{
  SPI_HandleTypeDef* const Handle    = spi::GetHandle();
  uint8_t            const Addr      = static_cast<uint8_t>( ISM330DHCX_Regs::WHO_AM_I );
  uint8_t RxByte=0x00;
  uint8_t            const ReadBit   = 0x01 << 7;
  uint8_t            const ReadAddr  = ReadBit | Addr;
  uint8_t                  TxData[]  = { ReadAddr };
  uint8_t                  RxData[]  = { 0x00 };
  uint16_t           const TxSize    = sizeof( TxData ) / sizeof( uint8_t );
  uint16_t           const RxSize    = sizeof( RxData ) / sizeof( uint8_t );
  uint32_t           const Timeout   = 1000;
  spi::ReadOneByte( SPI_ISM330DHCX, Addr, &RxData[0] );
  uint8_t            const chipID    = RxData[0];
  HAL_StatusTypeDef  const Status    = ( chipID == 0x6B )? HAL_OK : HAL_ERROR;
  *ChipID = chipID;
  return Status;
}

