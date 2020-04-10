/* ----------------------------------------
 led utility header

---------------------------------------- */
#ifndef  __LED_H__
#define  __LED_H__

#include  <..\stm32f1xx_cppLib\gpio.h>

/* ----------------------------------------
    prototypes 
---------------------------------------- */

/* ----------------------------------------
    instances or global variables
---------------------------------------- */

class LED : public GPIO
{
public:
  LED();
  LED( int pin );
  ~LED();
  void begin( int pin );
  void end();
  void On();
  void Off();
  void OnOff( bool bit );
  void toggle();
  bool odr();
  bool idr();

private:
  int pinNumber;
  GPIO_TypeDef* gpiox;
  uint16_t gpioPin;
};


#endif  /* __LED_H__ */

