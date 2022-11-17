//=============================================================================
//! \file menu.hpp
//!       Menu configuration header
//! \author Daniel J. Greenhoe
//=============================================================================

class UserInterface : public ISM330DHCX, public LEDs
{
  private:
    char* Number_to_BinaryString( const int Number, char *buf );

  public:
    void  Splash( void );
    int Options( void );
    int Processing( const uint8_t oneChar );
};
