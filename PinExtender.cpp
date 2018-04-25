
#include "PinExtender.h"


 PinExtender * pinExtention;
#ifdef __cplusplus
 extern "C" {
#endif
  
void PinExtention_analogWriteResolution(int res)
{
  if( pinExtention) 
    pinExtention->analogWriteResolution(res);
}


void setPinExtender(PinExtender * next)
{
  pinExtention=next;
}
void    PinExtention_digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
  if( pinExtention) 
    pinExtention->digitalWrite( ulPin,  ulVal );
}
int PinExtention_digitalRead( uint32_t ulPin )
 {
  if( pinExtention) 
    return pinExtention->digitalRead(  ulPin );
  return LOW;
}     
void PinExtention_pinMode( uint32_t ulPin, uint32_t ulMode )
{
  if( pinExtention) 
    pinExtention->pinMode(  ulPin,  ulMode );
}
uint32_t PinExtention_analogRead( uint32_t pin )
{
  if( pinExtention)
    return pinExtention->analogRead(  pin );
  return 0;
}
#ifdef __cplusplus
 }
#endif
bool PinExtender::accept(uint32_t p)
{
	if(acceptlocal( p))
		return true;
	if (_next)
		return _next->accept( p);
	return false;
}
void PinExtender::setPinExtender(PinExtender * next)
{
  _next==next;
}
PinExtender::PinExtender() :  _i2caddr(0),
  _i2c(0),   
  _next(0)
{
 
}















     void PinExtender::begin(TwoWire *MyWire,uint8_t addr) {};
     void PinExtender::begin(uint8_t addr) {};
     void PinExtender::begin(void) {};
	/** convert local pin number(uint8_t) of the board to arduino pin number(uint32_t) */
     uint32_t PinExtender::getPin(uint8_t channel_local) {return 0;};
     void PinExtender::pinMode(uint32_t pin_arduino, uint8_t d) {};
     void PinExtender::digitalWrite(uint32_t pin_arduino, uint8_t d) {};
     uint8_t PinExtender::digitalRead(uint32_t pin_arduino) {return 0;};
     void PinExtender::analogWrite( uint32_t pin_arduino, uint32_t ulValue )  {};
     void PinExtender::analogWriteResolution(int res) {};  
     uint32_t PinExtender::analogRead( uint32_t pin ) {return 0;};
     bool PinExtender::acceptlocal(uint32_t p){return 0;};
     uint8_t PinExtender::pin2channel(uint32_t pin){return 0;};