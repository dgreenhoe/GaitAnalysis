//=============================================================================
//! \author Daniel J. Greenhoe
//! \file   io.c
//!         io operations supporting printf via UART/USB port
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "io.h"
#include "main.h"
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

//-----------------------------------------------------------------------------
// \Drivers\STM32H7xx_HAL_Driver\Src\stm32h7xx_hal_uart.c
// Reference: https://youtu.be/WnCpPf7u4Xo?t=139
//-----------------------------------------------------------------------------
int _write(int file, char *ptr, int len)
{
  UART_HandleTypeDef * const Handle   = &huart2;
  uint8_t *            const TxBuf    = (uint8_t *)ptr;
  uint16_t             const NumBytes = (uint16_t)len;
  uint32_t             const Timeout  = 1000;
  HAL_UART_Transmit( Handle, TxBuf, NumBytes, Timeout );
  return len;
}

//-----------------------------------------------------------------------------
// \brief Non-blocking get one character
// \ref https://www.openstm32.org/forumthread5015
//-----------------------------------------------------------------------------
bool GetOneByte(uint8_t * OneByte)
{
  bool ByteReceived = false;
  UART_HandleTypeDef * const Handle = &huart2;
  if (__HAL_UART_GET_FLAG( Handle, UART_FLAG_ORE  ) )
    __HAL_UART_CLEAR_FLAG( Handle, UART_FLAG_ORE  );
  if (__HAL_UART_GET_FLAG( Handle, UART_FLAG_RXNE ))
  {
    *OneByte = Handle->Instance->RDR & 0x1FF;
    ByteReceived = true;
  }
  return ByteReceived;
}
