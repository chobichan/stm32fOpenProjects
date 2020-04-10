/* ----------------------------------------
 gpio initialize header

---------------------------------------- */
#ifndef  __GPIO_INIT_H__
#define  __GPIO_INIT_H__

#include  <..\stm32f1xx_cppLib\gpio.h>
#include  <derivertive.h>

extern "C"
{
}

/* ----------------------------------------
    defines
---------------------------------------- */


/* ----------------------------------------
    prototypes 
---------------------------------------- */

/* ----------------------------------------
    instances or global variables
---------------------------------------- */


/* ----------------------------------------
    class
---------------------------------------- */
class GPIO_INIT : public GPIO
{
public:
  void init();

private:
};


#endif  /* __GPIO_INIT_H__ */

