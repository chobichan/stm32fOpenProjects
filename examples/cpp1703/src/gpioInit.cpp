/* ----------------------------------------
 gpio initialize header

---------------------------------------- */
#include  <gpioInit.h>

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
    gpioInit
---------------------------------------- */
/*************************************************************************/
/* CPUボードのGPIO初期化                                                 */
/*************************************************************************/
void GPIO_INIT::init()
{
  /* all pin make input pullup. */
  GPIO_InitTypeDef GPIO_InitStruct;

  /*stm32f103retなので、ポートの最大はPDまでとなる*/
  /*まず全てを入力、プルアップあり、出力はpush/pullに変更*/
  GPIO_StructInit( &GPIO_InitStruct );
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init( GPIOC, &GPIO_InitStruct );
  GPIO_Init( GPIOD, &GPIO_InitStruct );
  /*GPIOAの13、14、15pinはJTAG。但しSWDなら使用するのは13、14pinのみ*/
  /*GPIOBの3、4pinはJTAG。但しSWDなら使用しない*/
#if 0
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStruct.GPIO_Pin &= ~(GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
  GPIO_Init( GPIOA, &GPIO_InitStruct );
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStruct.GPIO_Pin &= ~(GPIO_Pin_3 | GPIO_Pin_4);
  GPIO_Init( GPIOB, &GPIO_InitStruct );
#else
  GPIO_PinRemapConfig( GPIO_Remap_SWJ_JTAGDisable, ENABLE );
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_Init( GPIOA, &GPIO_InitStruct );
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  // GPIO_InitStruct.GPIO_Pin &= ~(GPIO_Pin_13 | GPIO_Pin_14);
  GPIO_Init( GPIOA, &GPIO_InitStruct );

  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init( GPIOB, &GPIO_InitStruct );
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStruct.GPIO_Pin &= ~(GPIO_Pin_0 | GPIO_Pin_1);
  GPIO_Init( GPIOB, &GPIO_InitStruct );
#endif

  GPIOA->ODR = 0x0000;
  /*  PA0： PWM output*/
  /*  PA1： PWM output*/
  /*  PA2： PWM output*/
  /*  PA3： PWM output*/
  /*  PA6： PWM output*/
  /*  PA7： PWM output*/
  /*  PA4：未使用*/
  /*  PA5：未使用*/
  /*  PA8:GCLK_RESET output*/
  set( GCLK_RESET );
  pinMode( GCLK_RESET, OUTPUT, GPIO_SPEED_NORMAL );
  /*  PA9:USART1 TXD：Alternate function*/
  /*  PA10:USART1 RXD：Alternate function*/
  /*  PA11:DIVCLK Timer1 ch4 output*/
//  DCLK_IS_0;
//  GPIO_Output_Init( GPIOA, GPIO_Pin_11 );
/*  PA12:GCLK input*/
/*  PA13:SWDIO*/
/*  PA14:SWDCLK*/
/*  PA15：RTS4 output (REMAP)*/
  pinMode( RTS4, OUTPUT, GPIO_SPEED_NORMAL );

  GPIOB->ODR = 0x0000;
  /*  PB0： PWM output*/
  /*  PB1： PWM output*/
/*  PB2:BOOT1：LOWに固定しているのでRAMデバッグはできない */
/*  PB3:SEG_A output:JTAG TDO*/
/*  PB4:SEG_B output:JTAG TRST*/
/*  PB5:SEG_C output */
/*  PB6:SEG_D output*/
/*  PB7:SEG_E output*/
/*  PB8:SEG_F output*/
/*  PB9:SEG_G output*/
/*  PB10:SCL2：Alternate function*/
/*  PB11:SDA2：Alternate function*/
/*  PB12:SD CARD Slave select output*/
//  SD_SS_IS_1;
//  GPIO_Output_Init( GPIOB, GPIO_Pin_12 );
  set( SD_SS );
  pinMode( SD_SS, OUTPUT, GPIO_SPEED_FAST );
/*  PB13:SPI2_SCK output Alternate function*/
//  GPIO_Output_Init( GPIOB, GPIO_Pin_13 );
  pinMode( PB13, OUTPUT, GPIO_SPEED_FAST );
/*  PB14:SPI2_MISO input Alternate function*/
/*  PB15:SPI2_MOSI output Alternate function*/
//  GPIO_Output_Init( GPIOB, GPIO_Pin_15 );
  pinMode( PB15, OUTPUT, GPIO_SPEED_FAST );

/*  PC0:DIO0*/
/*  PC1:DIO1*/
/*  PC2:DIO2*/
/*  PC3:DIO3*/
/*  PC4：no connect*/
/*  PC5:W5500 interrupt*/
/*  PC6: SD CARD detect input*/
/*  PC7:W5500 CS output*/
  set( W5500_CS );
  pinMode( W5500_CS, OUTPUT, GPIO_SPEED_FAST );
/*  PC8:W5500 RESET output*/
  set( W5500_RST );
  pinMode( W5500_RST, OUTPUT, GPIO_SPEED_SLOW );
/*  PC9:1PPS input*/
/*  PC10:UART4 TXD：Alternate function*/
/*  PC11:UART4 RXD：Alternate function*/
/*  PC12:UART5 TXD：Alternate function*/
/*  PC13:ACT LED*/
//  GPIO_Output_Init( GPIOC, GPIO_Pin_13 );
  pinMode( ACT_LED, OUTPUT, GPIO_SPEED_SLOW );
/*  PC14、32kclock 入力 */
//  GPIO_InputFloat_Init( GPIOC, GPIO_Pin_14 );  /*PC14はOSC_INに接続されている*/
/*  PC15、32Kclock 出力 */
//  GPIO_Alternate_Init(  GPIOC, GPIO_Pin_15 );  /*PC15はOSC_OUTに接続されている*/

/*  PD2:UART5 RXD：Alternate function*/
}

/*********************************************************************************/
/* end of file                                                                   */
/*                                         designed by hamayan since 2009/05/21  */
/*********************************************************************************/
