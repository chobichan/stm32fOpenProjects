/* ----------------------------------------
  led utilities
---------------------------------------- */
#include  <led.h>

/* ----------------------------------------
    prototypes 
---------------------------------------- */

/* ----------------------------------------
    instances or global variables
---------------------------------------- */

/* ----------------------------------------
    constructor destructor
---------------------------------------- */
LED::LED()
{
}

LED::LED( int pin )
{
  pinNumber = pin;
  gpiox = whatGPIOType( pin );
  gpioPin = whatPin( pin );
  pinMode( pin, OUTPUT, GPIO_SPEED_SLOW );
}

LED::~LED()
{
  pinMode( pinNumber, INPUT_PULLUP );
}

/* ----------------------------------------
    begin and end
---------------------------------------- */
void LED::begin( int pin )
{
  pinNumber = pin;
  gpiox = whatGPIOType( pin );
  gpioPin = whatPin( pin );
  pinMode( pin, OUTPUT, GPIO_SPEED_SLOW );
}

void LED::end()
{
  pinMode( pinNumber, INPUT_PULLUP );
}


/* ----------------------------------------
    led turn on / off
---------------------------------------- */
void LED::On()
{
//  set( pinNumber );
  gpiox->BSRR = gpioPin;
}

void LED::Off()
{
//  reset( pinNumber );
  gpiox->BSRR = gpioPin << 16;
}

void LED::OnOff( bool bit )
{
  if( bit ) On();
  else Off();
}

void LED::toggle()
{
  OnOff( (odr()) ? false : true );
}

/* ----------------------------------------
    read odr
---------------------------------------- */
bool LED::odr()
{
  return (gpiox->ODR & gpioPin) ? true : false;
}

/* ----------------------------------------
    read idr
---------------------------------------- */
bool LED::idr()
{
  return (gpiox->IDR & gpioPin) ? true : false;
}
