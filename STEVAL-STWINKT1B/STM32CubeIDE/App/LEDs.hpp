//=============================================================================
//! \author Daniel J. Greenhoe
//! \file   LEDs.h
//!         LED control
//=============================================================================


class LEDs
{
  private:
    inline void Green_On (  void ){ HAL_GPIO_WritePin(GPIOE, LED1_Pin, GPIO_PIN_SET  ); }
    inline void Green_Off(  void ){ HAL_GPIO_WritePin(GPIOE, LED1_Pin, GPIO_PIN_RESET); }
    inline void Orange_On ( void ){ HAL_GPIO_WritePin(GPIOD, LED2_Pin, GPIO_PIN_SET  ); }
    inline void Orange_Off( void ){ HAL_GPIO_WritePin(GPIOD, LED2_Pin, GPIO_PIN_RESET); }

  public:
    void StateMachine(void);
};
