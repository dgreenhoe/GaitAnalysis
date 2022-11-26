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
  CS_Deassert();
  HAL_GPIO_WritePin( GPIOF, GPIO_PIN_5,  GPIO_PIN_SET );   // Deassert CS_ADWB of IIS3DWB Vibrometer
  HAL_GPIO_WritePin( GPIOD, GPIO_PIN_15, GPIO_PIN_SET );   // Deassert CS_DH   of IIS2DH 3-Axis Accel
  SPI_HandleTypeDef* const Handle = GetHandle();
  Handle->Instance                = SPI3;
  Handle->Init.Mode               = SPI_MODE_MASTER;
  Handle->Init.Direction          = SPI_DIRECTION_2LINES;
  Handle->Init.DataSize           = SPI_DATASIZE_8BIT;
  Handle->Init.CLKPolarity        = SPI_POLARITY_HIGH;
  Handle->Init.CLKPhase           = SPI_PHASE_2EDGE;
  Handle->Init.NSS                = SPI_NSS_SOFT;
  Handle->Init.BaudRatePrescaler  = SPI_BAUDRATEPRESCALER_128;  // 2,4,8,16,32,64,128,256
  Handle->Init.FirstBit           = SPI_FIRSTBIT_MSB;
  Handle->Init.TIMode             = SPI_TIMODE_DISABLE;
  Handle->Init.CRCCalculation     = SPI_CRCCALCULATION_DISABLE;
  Handle->Init.CRCPolynomial      = 7;
  Handle->Init.CRCLength          = SPI_CRC_LENGTH_DATASIZE;
  Handle->Init.NSSPMode           = SPI_NSS_PULSE_DISABLE;
  HAL_StatusTypeDef const Status  = HAL_SPI_Init( Handle );
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
// !\brief ISM330DHCX Get Chip ID
//-----------------------------------------------------------------------------
HAL_StatusTypeDef ISM330DHCX::GetChipID( uint8_t* ChipID )
{
  SPI_HandleTypeDef* const Handle    = ISM330DHCX::GetHandle();
  uint8_t            const Addr      = static_cast<uint8_t>( ISM330DHCX_Regs::WHO_AM_I );
  uint8_t            const ReadBit   = 0x01 << 7;
  uint8_t            const ReadAddr  = ReadBit | Addr;
  uint8_t                  TxData[]  = { ReadAddr };
  uint8_t                  RxData[]  = { 0x00 };
  uint16_t           const TxSize    = sizeof( TxData ) / sizeof( uint8_t );
  uint16_t           const RxSize    = sizeof( RxData ) / sizeof( uint8_t );
  uint32_t           const Timeout   = 1000;
  HAL_StatusTypeDef  const Status0   = ISM330DHCX::CS_Assert();
  HAL_StatusTypeDef  const Status1   = HAL_SPI_Transmit( Handle, &TxData[0], TxSize, Timeout );
  HAL_StatusTypeDef  const Status2   = HAL_SPI_Receive(  Handle, &RxData[0], RxSize, Timeout );
  HAL_StatusTypeDef  const Status3   = ISM330DHCX::CS_Deassert();
  uint8_t            const chipID    = RxData[0];
  HAL_StatusTypeDef  const Status    = ( chipID == 0x6B )? HAL_OK : HAL_ERROR;
  *ChipID = chipID;
  return Status;
}

