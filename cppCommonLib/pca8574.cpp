/* ----------------------------------------
  pca8574 utilities codes
---------------------------------------- */
#include  <pca8574.h>

/* ----------------------------------------
    prototypes 
---------------------------------------- */

/* ----------------------------------------
    instances or global variables
---------------------------------------- */

/* ----------------------------------------
    constructor destructor
---------------------------------------- */
PCA8574::PCA8574()
{
}

PCA8574::PCA8574( STM32F_I2C *i2c, uint8_t adr )
{
  begin( i2c, adr );
}

PCA8574::~PCA8574()
{
}

/* ----------------------------------------
    begin and end
---------------------------------------- */
void PCA8574::begin( STM32F_I2C *i2c, uint8_t adr )
{
  wire = i2c;
  slave = adr;
}

/* ----------------------------------------
    write
---------------------------------------- */
int PCA8574::write( uint8_t data )
{
  int ret = wire->beginTransmission( slave );
  if( ret < 0 )return ret;
  ret = wire->write( data );
  wire->endTransmission();
  return ret;
}


/* ----------------------------------------
    read
---------------------------------------- */
int PCA8574::read()
{
  int ret = wire->beginTransmission( slave );
  if( ret < 0 ) return ret;
  ret = wire->read();
  wire->endTransmission();
  return ret;
}
