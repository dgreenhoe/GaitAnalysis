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

extern USBD_HandleTypeDef hUsbDeviceFS;
int8_t CDC_Init_FS(void);
int8_t CDC_Receive(uint8_t* Buf, uint32_t *Len);
void CDC_Receive_Clear(void);

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

uint8_t UsbRxBuf[16];
uint8_t NewByte, NewByte2;
//-----------------------------------------------------------------------------
//! \brief Non-blocking get one character
// \ref https://www.openstm32.org/forumthread5015
//-----------------------------------------------------------------------------
bool GetOneByte( uint8_t* OneByte )
{
  bool ByteReceived = false;
  uint32_t Len = 1;
  CDC_Receive( OneByte, &Len );
  //printf("CDC OneByte=%02X ('%c') Len=%ld Rx=%d\r\n", *OneByte, *OneByte, Len, ByteReceived);
  return ByteReceived;
}

int8_t CDC_Receive(uint8_t* Buf, uint32_t *Len)
{
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &UsbRxBuf[0]);
  USBD_CDC_ReceivePacket(&hUsbDeviceFS);
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef *)(hUsbDeviceFS.pClassData);
  NewByte = hcdc->RxBuffer[0]; 
  Buf[0] = hcdc->RxBuffer[0];
//printf("Rx=%02x\r\n", hcdc->RxBuffer[0]);
  return (USBD_OK);
}

//void CDC_Receive_Clear(void)
//{
//  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &UsbRxBuf[0]);
//  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef *)(hUsbDeviceFS.pClassData);
//  hcdc->RxBuffer[0] = 0;
//  return (USBD_OK);
//}
