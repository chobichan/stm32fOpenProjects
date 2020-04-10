/* ----------------------------------------
 pca8574 utility header

---------------------------------------- */
#ifndef  __PCA8574_H__
#define  __PCA8574_H__

#include  <Wire.h>
extern "C"
{
}

/* ----------------------------------------
    prototypes 
---------------------------------------- */

/* ----------------------------------------
    instances or global variables
---------------------------------------- */

class PCA8574 //  : public GPIO
{
public:
  PCA8574();
  PCA8574( STM32F_I2C *i2c, uint8_t adr );
  ~PCA8574();
  void begin( STM32F_I2C *i2c, uint8_t adr );

  int write( uint8_t data );
  int read();

private:
  STM32F_I2C *wire;
  uint8_t slave;
};


#endif  /* __PCA8574_H__ */

