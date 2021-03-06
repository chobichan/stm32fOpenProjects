/* ----------------------------------------
 gpio utility header
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
#ifndef  __GPIO_H__
#define  __GPIO_H__

#include  <stm32fPeripheral.h>

/* ----------------------------------------
    prototypes 
---------------------------------------- */


/* ----------------------------------------
    defines
---------------------------------------- */
/* ----------------------------------------
  type
  GPIO_Mode_AIN or GPIO_Mode_IN_FLOATING
  or GPIO_Mode_IPD or GPIO_Mode_IPU
  or GPIO_Mode_Out_OD or GPIO_Mode_Out_PP
  or GPIO_Mode_AF_OD or GPIO_Mode_AF_PP
---------------------------------------- */
enum GPIO_PIN_MODE
{
  ANALOG = GPIO_Mode_AIN,
  INPUT = GPIO_Mode_IN_FLOATING,
  INPUT_PULLDOWN = GPIO_Mode_IPD,
  INPUT_PULLUP = GPIO_Mode_IPU,
  OUTPUT_OPEN_DRAIN = GPIO_Mode_Out_OD,
  OUTPUT = GPIO_Mode_Out_PP,
  ALTERNATE_OD = GPIO_Mode_AF_OD,
  ALTERNATE_PP = GPIO_Mode_AF_PP,
};

/* ----------------------------------------
  speed
  GPIO_Speed_10MHz or GPIO_Speed_2MHz
  or GPIO_Speed_50MHz
---------------------------------------- */
enum GPIO_PIN_SPEED
{
  GPIO_SPEED_NORMAL = GPIO_Speed_10MHz,
  GPIO_SPEED_SLOW = GPIO_Speed_2MHz,
  GPIO_SPEED_FAST = GPIO_Speed_50MHz,
};


/*  */
/* ----------------------------------------
    instances or global variables
---------------------------------------- */

class GPIO  // : public hoge_class
{
public:
  GPIO_TypeDef* whatGPIOType( int pin );
  uint16_t whatPin( int pin );
  void allPullup();
  void pinMode( GPIO_TypeDef *gpiox, uint16_t gpioPin, int type, int speed = GPIO_SPEED_FAST );
  void pinMode( int pin, int type, int speed = GPIO_SPEED_FAST );

  void set( int pin );
  void reset( int pin );
  bool digitalRead( int pin );
  void wordWrite( GPIO_TypeDef *gpiox, uint16_t data, uint16_t mask );
private:
};


#endif  /* __GPIO_H__ */

