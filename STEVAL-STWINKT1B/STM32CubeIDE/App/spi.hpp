//=============================================================================
//! \file spi.hpp
//!       SPI header
//! \author Daniel J. Greenhoe
//=============================================================================

//-----------------------------------------------------------------------------
// !\brief Devices on SPI bus
//-----------------------------------------------------------------------------
enum 
{
  SPI_ISM330DHCX = 0
};

//-----------------------------------------------------------------------------
// !\brief SPI Class Definition
//-----------------------------------------------------------------------------
class spi
{
  private:
    HAL_StatusTypeDef CS_Assert(void);
    HAL_StatusTypeDef CS_Deassert(void);
  public:
    SPI_HandleTypeDef* GetHandle(void);
    HAL_StatusTypeDef  Init(void);
    HAL_StatusTypeDef  TxByte( uint8_t const Addr, uint8_t const OneByte );
    HAL_StatusTypeDef  ReadOneByte(  int const Device, uint8_t const Register, uint8_t* RxByte );
    HAL_StatusTypeDef  WriteOneByte( int const Device, uint8_t const Register, uint8_t  TxByte );
    HAL_StatusTypeDef  ReadNBytes( int const Device, uint8_t const Register, uint8_t const RxSize, uint8_t* RxData );
};
