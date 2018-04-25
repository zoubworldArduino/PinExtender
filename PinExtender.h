#ifndef _PinExtender_H
#define _PinExtender_H
/**
This file allow to add I/O by Wire(I2c) and continue to use standard Arduino api(Digital/analogRead/Write).
This allow to keep you code very simple, and allow to continue to use generic(not core specific) library on extedned pin.
For instance you can use a library for motor control with pin comming form a PCA9685 module that is a PWM extension module.

To do that you need to implemented a PinExtender daugther class and intantiate it and do setPinExtender(MyPinExtObject);
you can daisy chain it by MyPinExtObject.setPinExtender(MyPinExtObject2) and so on.
to identify the pin use uint32_t variable or define like 0xaaaapppp.
aaaa is the I2C device address for instance for a PCA9685, '0xaaaa' will be 0b1aaaaaa where aaaaaa fit with pin A[5:0], 
and pppp will be between 0 and 15 to identify pin LED[0:15]
aaaa is the I2C device address for instance for a MCP23017, '0xaaaa' will be 0b0100aaa where aaa fit with pin A[2:0], 
and pppp will be between 0 and 7 to identify pin GPA[0:8] and between 8 and 15 to identify pin GPB[0:8].
For sure not all the api function will work correctly according to the limited capacity of these device, 
for example a analogRead will not work on previous device but analogWrite work on PCA9685 and have a basic behaviour on MCP23017.
to get the pin number dynamically you can do : MyPinExtObject2.getPin(channel)

supported core : SAMD from zoubwolrd.
To extend you core edit wiring_digital.c  wiring_analog.c from your arduino core and add call to like it is done on zoubworld_arduino core:
- PinExtention_analogWriteResolution(int res);
- PinExtention_digitalWrite( uint32_t ulPin, uint32_t ulVal );
- PinExtention_digitalRead( uint32_t ulPin );
- PinExtention_pinMode( uint32_t ulPin, uint32_t ulMode );
- PinExtention_analogRead( uint32_t pin );
PCA9685 and MCP23017 is already supported on dedicated library.
*/

#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Wire.h"

/** daisy chain to manage pin
*/
 class PinExtender
{
  private:	
	virtual bool acceptlocal(uint32_t p);
	virtual uint8_t pin2channel(uint32_t pin);
protected:
     uint8_t _i2caddr;
         TwoWire *_i2c;   
  public:

    PinExtender * _next;

    PinExtender();
    bool accept(uint32_t p);
    void setPinExtender(PinExtender * next);
  
    virtual void begin(TwoWire *MyWire,uint8_t addr);
    virtual void begin(uint8_t addr);
    virtual void begin(void);
	/** convert local pin number(uint8_t) of the board to arduino pin number(uint32_t) */
	virtual uint32_t getPin(uint8_t channel_local);
    virtual void pinMode(uint32_t pin_arduino, uint8_t d);
    virtual void digitalWrite(uint32_t pin_arduino, uint8_t d);
    virtual uint8_t digitalRead(uint32_t pin_arduino);
	
	virtual void analogWrite( uint32_t pin_arduino, uint32_t ulValue ) ;
    virtual void analogWriteResolution(int res);  
    virtual uint32_t analogRead( uint32_t pin );

};

#ifdef __cplusplus
 extern "C" {
#endif
void PinExtention_analogWriteResolution(int res);

void    PinExtention_digitalWrite( uint32_t ulPin, uint32_t ulVal );
int PinExtention_digitalRead( uint32_t ulPin );
      
void PinExtention_pinMode( uint32_t ulPin, uint32_t ulMode );
uint32_t PinExtention_analogRead( uint32_t pin );

void setPinExtender(PinExtender * next);
#ifdef __cplusplus
 }
#endif
#endif