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

extern SPI_HandleTypeDef hspi3;

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
SPI_HandleTypeDef* spi::GetHandle(void)
{
  SPI_HandleTypeDef* const Handle = &hspi3;
  return Handle;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
HAL_StatusTypeDef spi::CS_Assert(void)
{
  HAL_StatusTypeDef const Status = HAL_OK;
  HAL_GPIO_WritePin( GPIOF, GPIO_PIN_5,  GPIO_PIN_SET   ); // Deassert CS_ADWB of IIS3DWB Vibrometer
  HAL_GPIO_WritePin( GPIOD, GPIO_PIN_15, GPIO_PIN_SET   ); // Deassert CS_DH   of IIS2DH 3-Axis Accel
  HAL_GPIO_WritePin( GPIOF, GPIO_PIN_13, GPIO_PIN_RESET ); // Assert   CS_DHC  of ISM330DHCX 6-Axis Accel
  return Status;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
HAL_StatusTypeDef spi::CS_Deassert(void)
{
  HAL_StatusTypeDef const Status = HAL_OK;
  HAL_GPIO_WritePin( GPIOF, GPIO_PIN_13, GPIO_PIN_SET );
  return Status;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
HAL_StatusTypeDef spi::Init(void)
{
  HAL_GPIO_WritePin( GPIOF, GPIO_PIN_13, GPIO_PIN_SET );
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
//HAL_StatusTypeDef spi::TxByte( uint8_t const Register, uint8_t const OneByte )
//{
//  SPI_HandleTypeDef* const Handle    = GetHandle();
//  uint8_t            const ReadBit   = 0x01 << 7;
//  uint8_t            const ReadAddr  = ReadBit | Register;
//  uint8_t                  TxData[]  = { ReadAddr };
//  uint8_t                  RxData[]  = { 0x00 };
//  uint16_t           const TxSize    = sizeof( TxData ) / sizeof( uint8_t );
//  uint16_t           const RxSize    = sizeof( RxData ) / sizeof( uint8_t );
//  uint32_t           const Timeout   = 1000;
//  HAL_StatusTypeDef  const Status0   = CS_Assert();
//  HAL_StatusTypeDef  const Status1   = HAL_SPI_Transmit( Handle, &TxData[0], TxSize, Timeout );
//
//  return Status1;
//}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
HAL_StatusTypeDef spi::ReadOneByte( int const Device, uint8_t const Register, uint8_t* RxByte )
{
  switch( Device )
  {
    case SPI_ISM330DHCX: CS_Assert(); break;
  }
  SPI_HandleTypeDef* const Handle    = GetHandle();
  uint8_t            const ReadBit   = 0x01 << 7;
  uint8_t            const ReadAddr  = ReadBit | Register;
  uint8_t                  TxData[]  = { ReadAddr };
  uint8_t                  RxData[]  = { 0x00 };
  uint16_t           const TxSize    = sizeof( TxData ) / sizeof( uint8_t );
  uint16_t           const RxSize    = sizeof( RxData ) / sizeof( uint8_t );
  uint32_t           const Timeout   = 1000;
  HAL_StatusTypeDef  const Status1   = HAL_SPI_Transmit( Handle, &TxData[0], TxSize, Timeout );
  HAL_StatusTypeDef  const Status2   = HAL_SPI_Receive(  Handle, &RxData[0], RxSize, Timeout );
  switch( Device )
  {
    case SPI_ISM330DHCX: CS_Deassert(); break;
  }
  *RxByte = RxData[0];
  return Status2;
}

//-----------------------------------------------------------------------------
// !\brief Read N Bytes
//-----------------------------------------------------------------------------
HAL_StatusTypeDef spi::ReadNBytes( int const Device, uint8_t const Register, uint8_t const RxSize, uint8_t* RxData )
{
  switch( Device )
  {
    case SPI_ISM330DHCX: CS_Assert(); break;
  }
  SPI_HandleTypeDef* const Handle    = GetHandle();
  uint8_t            const ReadBit   = 0x01 << 7;
  uint8_t            const ReadAddr  = ReadBit | Register;
  uint8_t                  TxData[]  = { ReadAddr };
  uint16_t           const TxSize    = sizeof( TxData ) / sizeof( uint8_t );
  uint32_t           const Timeout   = 1000;
  //HAL_StatusTypeDef  const Status1   = HAL_SPI_Transmit( Handle, &TxData[0], TxSize, Timeout );
  //HAL_StatusTypeDef  const Status2   = HAL_SPI_Receive(  Handle, &RxData[0], RxSize, Timeout );
  for( uint8_t n=0; n<RxSize; n++ )
  {
    TxData[0] = n | 0x80;
    HAL_SPI_Transmit( Handle, &TxData[0], TxSize, Timeout );
    HAL_SPI_Receive(  Handle, &RxData[n], 1, Timeout );
  //printf( "TxData[0]=%02X\r\n", TxData[0] );
  }
  switch( Device )
  {
    case SPI_ISM330DHCX: CS_Deassert(); break;
  }
  return HAL_OK;
}

//-----------------------------------------------------------------------------
// !\brief ISM330DHCX Init
//-----------------------------------------------------------------------------
HAL_StatusTypeDef spi::WriteOneByte( int const Device, uint8_t const Register, uint8_t TxByte )
{
  switch( Device )
  {
    case SPI_ISM330DHCX: CS_Assert(); break;
  }
  SPI_HandleTypeDef* const Handle    = GetHandle();
  uint8_t            const WriteBit  = 0x00 << 7;
  uint8_t            const WriteAddr = WriteBit | Register;
  uint8_t                  TxData[]  = { WriteAddr, TxByte };
  uint16_t           const TxSize    = sizeof( TxData ) / sizeof( uint8_t );
  uint32_t           const Timeout   = 1000;
  HAL_StatusTypeDef  const Status    = HAL_SPI_Transmit( Handle, &TxData[0], TxSize, Timeout );
  switch( Device )
  {
    case SPI_ISM330DHCX: CS_Deassert(); break;
  }
  return Status;
}
