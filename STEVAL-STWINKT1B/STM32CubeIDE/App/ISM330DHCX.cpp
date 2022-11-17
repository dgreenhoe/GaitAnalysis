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
#include "ISM330DHCX.hpp"

extern SPI_HandleTypeDef hspi3;

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
SPI_HandleTypeDef* ISM330DHCX::GetHandle(void)
{
  SPI_HandleTypeDef* const Handle = &hspi3;
  return Handle;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
HAL_StatusTypeDef ISM330DHCX::Init(void)
{
  HAL_GPIO_WritePin(GPIOF, 13, GPIO_PIN_SET );
  return HAL_OK;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
HAL_StatusTypeDef ISM330DHCX::CS_Assert(void)
{
  HAL_StatusTypeDef const Status = HAL_OK;
  HAL_GPIO_WritePin(GPIOF, 13, GPIO_PIN_RESET );
  HAL_Delay(10);
  return Status;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
HAL_StatusTypeDef ISM330DHCX::CS_Deassert(void)
{
  HAL_StatusTypeDef const Status = HAL_OK;
  HAL_Delay(10);
  HAL_GPIO_WritePin(GPIOF, 13, GPIO_PIN_SET );
  return Status;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
HAL_StatusTypeDef ISM330DHCX::GetChipID(void)
{
  SPI_HandleTypeDef* const Handle    = ISM330DHCX::GetHandle();
  uint8_t            const Addr      = static_cast<uint8_t>( ISM330DHCX_Regs::WHO_AM_I );
  uint8_t            const ReadAddr  = 0x80 | Addr;
  uint8_t                  TxData[1] = { ReadAddr };
  uint8_t                  RxData[2] = { 0x00, 0x00 };
  uint16_t           const Size      = sizeof( TxData ) / sizeof( uint8_t );
  uint32_t           const Timeout   = 1000;
  HAL_StatusTypeDef  const Status0   = ISM330DHCX::CS_Assert();
//HAL_StatusTypeDef  const Status    = HAL_SPI_TransmitReceive( Handle, TxData, RxData, 2, Timeout);
  HAL_StatusTypeDef  const Status    = HAL_SPI_Transmit( Handle, TxData, 1, Timeout );
  HAL_StatusTypeDef  const Status2   = HAL_SPI_Receive(  Handle, RxData, 2, Timeout );
  HAL_StatusTypeDef  const Status3   = ISM330DHCX::CS_Deassert();
  printf( "Chip ID from 0x%02X = 0x%02X 0x%02X\r\n", TxData[0], RxData[0], RxData[1] );
  return Status;
}
