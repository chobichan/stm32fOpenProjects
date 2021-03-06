/* ----------------------------------------
 stm32f1xx defines for system.
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
#ifndef  __SYSTEM_H__
#define  __SYSTEM_H__

#include  <stm32f10x.h>

/*****************************************************/
/* defines                                           */
/*****************************************************/


/*****************************************************/
/* global variables                                  */
/*****************************************************/

/*****************************************************/
/* prototypes                                        */
/*****************************************************/
void dly10us( uint32_t dly_us );
void dly100us( uint32_t dly_us );
void dly1ms( uint32_t dly_ms );

#endif  /* __SYSTEM_H__ */
