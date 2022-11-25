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

extern SPI_HandleTypeDef hspi3; //hspi3;

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
  HAL_StatusTypeDef const Status = HAL_OK;
  CS_Deassert();
  HAL_GPIO_WritePin( GPIOF, GPIO_PIN_5,  GPIO_PIN_SET );   // Deassert CS_ADWB of IIS3DWB Vibrometer
  HAL_GPIO_WritePin( GPIOD, GPIO_PIN_15, GPIO_PIN_SET );   // Deassert CS_DH   of IIS2DH 3-Axis Accel
  return Status;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
HAL_StatusTypeDef ISM330DHCX::CS_Assert(void)
{
  HAL_StatusTypeDef const Status = HAL_OK;
  HAL_GPIO_WritePin( GPIOF, GPIO_PIN_5,  GPIO_PIN_SET   ); // Deassert CS_ADWB of IIS3DWB Vibrometer
  HAL_GPIO_WritePin( GPIOD, GPIO_PIN_15, GPIO_PIN_SET   ); // Deassert CS_DH   of IIS2DH 3-Axis Accel
  HAL_GPIO_WritePin( GPIOF, GPIO_PIN_13, GPIO_PIN_RESET ); // Assert   CS_DHC  of ISM330DHCX 6-Axis Accel
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
  HAL_GPIO_WritePin( GPIOF, GPIO_PIN_13, GPIO_PIN_SET );
  return Status;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
HAL_StatusTypeDef ISM330DHCX::GetChipID( uint8_t* ChipID )
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
  HAL_StatusTypeDef  const Status2   = HAL_SPI_Receive(  Handle, RxData, 1, Timeout );
  HAL_StatusTypeDef  const Status3   = ISM330DHCX::CS_Deassert();
  *ChipID = RxData[0];
  //printf( "Chip ID from 0x%02X = 0x%02X 0x%02X\r\n", TxData[0], RxData[0], RxData[1] );
  return Status;
}

