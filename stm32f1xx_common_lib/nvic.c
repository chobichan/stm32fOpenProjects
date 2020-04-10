/* ----------------------------------------
 stm32f1xx defines for nvic.
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
#include  <string.h>
#include  "stm32f10x.h"
#include  "derivertive.h"
#include  "peripheral.h"
#include  "mul_tsk.h"
#include  "i2c.h"
#include  "us2066.h"

/***********************************************************/
/* 端子定義                                                */
/***********************************************************/

/***********************************************************/
/* その他の定義                                            */
/***********************************************************/

/***********************************************************/
/* IOレジスタ定義                                          */
/***********************************************************/

/***********************************************************/
/* プロトタイプ宣言                                        */
/***********************************************************/

/***********************************************************/
/* 大域変数宣言                                            */
/***********************************************************/

/***********************************************************/
/* NVICの初期化                                            */
/***********************************************************/
void nvicInit( uint8_t irqCh, uint8_t pri, uint8_t sub )
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = irqCh;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = pri;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init( &NVIC_InitStructure );
}
