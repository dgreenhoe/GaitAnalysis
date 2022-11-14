//=============================================================================
//! \author Daniel J. Greenhoe
//! \file   io.c
//!         io operations supporting printf via UART/USB port
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "io.h"
#include "main.h"
#include "usbd_cdc_if.h"

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

//-----------------------------------------------------------------------------
//! \brief Write contents of buffer to COM port
// References: https://youtu.be/pC16Aon4crk
//             https://youtu.be/WnCpPf7u4Xo?t=139
//-----------------------------------------------------------------------------
int _write(int file, char *ptr, int len)
{
  uint8_t * const TxBuf     = (uint8_t *)ptr;
  uint16_t  const NumBytes  = (uint16_t)len;
  uint32_t  const TimeOut   = 1000;
  uint32_t  const TickStart = HAL_GetTick();
  uint32_t        Ticks     = 0;
  uint8_t         TxState   = USBD_BUSY;

  while( (TxState==USBD_BUSY) && (Ticks<TimeOut) )
  {
    TxState = CDC_Transmit_FS( TxBuf, NumBytes );
    Ticks = HAL_GetTick() - TickStart;
  }

  return len;
}

//-----------------------------------------------------------------------------
//! \brief Non-blocking get one character
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
