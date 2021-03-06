/* ----------------------------------------
  pca8574 utilities
  for STMicroelectronics SPL library

  Copyright (c) 2020 hamayan (hamayan.contact@gmail.com).
  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Created 2020 by hamayan (hamayan.contact@gmail.com)
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
