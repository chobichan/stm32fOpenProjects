#include  <stm32f10x.h>
//#include  "stm32f10x_conf.h"
#include  <time.h>
#include  <HardwareSerial.h>
#include  <gpioInit.h>
#include  <Timer.h>
#include  <Wire.h>
#include  <led.h>
#include  <us2066.h>
#include  <pca8574.h>
#include  <1702.h>

extern "C"
{
  #include  <system.h>
  #include  <mul_tsk.h>
}

/* ----------------------------------------
    defines
---------------------------------------- */

/* ----------------------------------------
    prototypes
---------------------------------------- */
void RCC_Configuration( void );
void NVIC_Configuration( void );

/* ----------------------------------------
    instances or global valiables
---------------------------------------- */
SEM_OBJECT sem_obj[ MAX_SEM_NUMBER ];

SYSTIM systim;
time_t unixTime;
time_t sumTotalTime;  /*‹N“®Žž‚©‚ç‚Ì’ÊŽZŽžŠÔ*/

Serial Serial1;  /* hardware serial 1 */
GPIO_INIT gpio;  /* initialize gpio */
STM32F_I2C i2c2;

/* ----------------------------------------
    tasks
---------------------------------------- */
void stackMonitor( void );
void loopBack( void );
void board1716( void );
void board1702( void );

uint8_t tsk1_stk[256 * 4];  // stack for task1
uint8_t tsk2_stk[256 * 4];  // stack for task2
//uint8_t tsk3_stk[256 * 4];  // stack for task3
uint8_t tsk4_stk[256 * 4];  // stack for task4

/* ----------------------------------------
    task initialize
---------------------------------------- */
void tsk_ini( void )
{
  reg_tsk( ID_stackMonitor,(void *)stackMonitor, tsk1_stk, sizeof(tsk1_stk), 0,0,0,0 );
  reg_tsk( ID_loopBack,(void *)loopBack, tsk2_stk, sizeof(tsk2_stk), 0,0,0,0 );
//  reg_tsk( ID_board1716,(void *)board1716, tsk3_stk, sizeof(tsk3_stk), 0,0,0,0 );
  reg_tsk( ID_board1702,(void *)board1702, tsk4_stk, sizeof(tsk4_stk), 0,0,0,0 );

  sta_tsk( ID_stackMonitor );
  sta_tsk( ID_loopBack );
//  sta_tsk( ID_board1716 );
  sta_tsk( ID_board1702 );
}


/* ----------------------------------------
    main
---------------------------------------- */
int main(void)
{
  RCC_Configuration();
  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
  NVIC_Configuration();

  /* Setup SysTick Timer for 1 millisec interrupts, also enables Systick and Systick-Interrupt */
  if( SysTick_Config(SystemCoreClock / 1000UL) )
  {
    /* Capture error */
    while (1);
  }

  /* initialize gpio */
  gpio.init();
  GPIO_PinRemapConfig( GPIO_FullRemap_USART3, ENABLE );

  struct tm localTime =
    {0,0,17,27,3-1,2020-1900,0,0,0};
#if 1
  unixTime = mktime( &localTime );
#endif

  /* initialize serial */
  Serial1.begin( SCI_1, 115200UL );
  Serial1.printf( "    1703 CHRONOS\r\n" );
  Serial1.printf( "    designed by hamayan.\r\n" );

  /* initialize i2c */
  if( i2c2.begin( I2C2, SDA2, SCL2 ) != I2C_SUCCESS )
  {
    while( 1 ) { ACT_IS_1; dly_tsk( 50UL ); ACT_IS_0; dly_tsk( 50UL ); }
  }

//  STM32F_TIMER tim8;
//  tim8.begin( TIM8 );
//  uint32_t freq = 2000UL;
//  tim8.frequency( freq );
//  tim8.toggle( TIMx_CH4, PC9 );
  /* get prescaler and period */
//  uint32_t prescaler,period;
//  tim8.prePeri( freq, &prescaler, &period );
//  tim8.pwm1( TIMx_CH4, PC9, period * 9 / 10 );
//  tim8.startInterrupt( TIMx_CH4 );
//  tim8.start();
//  dly_tsk( 10 * 1000UL );
//  tim8.stop();

  /* initialize tasks and start dispatch. */
  tsk_ini();  //
  sta_rdq( ID_stackMonitor );  // start round robin

  while(1) {}
}

/* ----------------------------------------
    task stack monitor.
---------------------------------------- */
void stackMonitor( void )
{
  LED blueLED( ACT_LED );  //

  struct tm localTime;
  volatile int i = 0;
  while( 1 )
  {
    blueLED.toggle();
    dly_tsk( 500UL );  // dly1ms( 500UL );
    blueLED.OnOff( ( blueLED.odr() ) ? false : true );
    dly_tsk( 500UL );  // dly1ms( 500UL );
    Serial1.printf( "    count = %d\r\n", ++i );

    localtime_r( &unixTime, &localTime );
    Serial1.printf( "  %d/%d/%d %d:%d:%d\r\n",
      localTime.tm_year + 1900,
      localTime.tm_mon + 1,
      localTime.tm_mday,
      localTime.tm_hour,
      localTime.tm_min,
      localTime.tm_sec
    );
  }
}


void loopBack( void )
{
  while( 1 )
  {
    while( Serial1.available() == 0 ) rot_rdq();
    int c = Serial1.read();
    Serial1.write( c );
  }
}

/* ----------------------------------------
    board 1716 task.
---------------------------------------- */
void board1716( void )
{
  #define  PCA8574_IC3  0x21
  LED out( BOARD_1716_OUTLED );

  /* initialize pca8574 for switch scan. */
  PCA8574 pcaIC3( &i2c2, PCA8574_IC3 );
  pcaIC3.write( 0xFF );

  US2066 oled( &i2c2 );
  oled.init();
  dly_tsk( 1000UL );
  oled.clear();
  oled.contrast( 127 );
//  oled.functionSet( SO2002A_FUNCTION_1LINE | SO2002A_FUNCTION_DOUBLE_HEIGHT );
  oled.printf( "1716 SIGNAL\r\n GENERATOR %d.", 1000 );
  dly_tsk( 200UL );
  oled.shift( SO2002A_CURSOR_SHIFT | SO2002A_CURSOR_RIGHT );
  dly_tsk( 200UL );
  oled.shift( SO2002A_CURSOR_SHIFT | SO2002A_CURSOR_RIGHT );
  dly_tsk( 200UL );
  oled.shift( SO2002A_CURSOR_SHIFT | SO2002A_CURSOR_RIGHT );
  dly_tsk( 200UL );
  oled.shift( SO2002A_CURSOR_SHIFT | SO2002A_CURSOR_LEFT );
  dly_tsk( 200UL );
  oled.shift( SO2002A_CURSOR_SHIFT | SO2002A_CURSOR_LEFT );
  dly_tsk( 200UL );
  oled.shift( SO2002A_CURSOR_SHIFT | SO2002A_CURSOR_LEFT );

  dly_tsk( 200UL );
  oled.shift( SO2002A_DISPLAY_SHIFT );
  dly_tsk( 200UL );
  oled.shift( SO2002A_DISPLAY_SHIFT );

  while( 1 )
  {
    int sw = pcaIC3.read();
    if( sw >= 0 )
    {
      if( sw & 0x20 ) out.Off();
      else out.On();
    }
    dly_tsk( 50UL );
  }
}

/* ----------------------------------------
    board 1702 task.
---------------------------------------- */
PCA8574 ic3,ic4;
BOARD_1702 bd1702;
LED  pps;
uint32_t segmentUpdate;

/* call back routine */
void cbDateDisplay( void )
{
//  bd1702.i_update();
  pps.toggle();
  segmentUpdate++;
}

void board1702( void )
{
  #define  PCA8574_IC3  0x21
  #define  PCA8574_IC4  0x22
  char segStrintg[ 8 ] = "000000";

  /* initialize pca8574 for switch scan and relay output. */
  ic3.begin( &i2c2, PCA8574_IC3 );
  ic3.write( 0xF0 );
  ic4.begin( &i2c2, PCA8574_IC4 );
  ic4.write( 0xFF );

  /* 7segment LED initialize. */
  bd1702.begin( &ic4, &ic3, (const char *)segStrintg, SEMID_I2C );

  pps.begin( PC9 );
  /* 7segment scan timer initialize. */
  STM32F_TIMER tim7;
  tim7.begin( TIM7 );
  tim7.frequency( 6 * 50UL );  /* 6segments and 50Hz flicker */
  tim7.callBack( TIM7_INT_UP, cbDateDisplay );
  tim7.start();

  time_t baseTim = unixTime;
  uint32_t segmentUpdateOld = segmentUpdate;
  int count = 0;
  while( 1 )
  {
    rot_rdq();
    if( segmentUpdate != segmentUpdateOld )
    {
      segmentUpdateOld = segmentUpdate;
      bd1702.update();
    }
    if( unixTime != baseTim )
    {
      baseTim = unixTime;
      sprintf( segStrintg, "%06d", count++ );
      if( baseTim & 1 )
      {
//        bd1702.relayOnOff( IC3_TIME_BIT | IC3_LOCK_BIT, true );
        bd1702.relayOnOff( IC3_DATE_BIT, false );
      }
      else
      {
//        bd1702.relayOnOff( IC3_TIME_BIT | IC3_LOCK_BIT, false );
        bd1702.relayOnOff( IC3_DATE_BIT, true );
      }
    }
  }
}



/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration( void )
{
  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,
     initialize the PLL and update the SystemFrequency variable. */
  SystemInit();

  /* Enable GPIO clock */
//  RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE );
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE );
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE );

//  RCC_APB2PeriphResetCmd( RCC_APB2Periph_TIM1, DISABLE );
  RCC_APB2PeriphResetCmd( RCC_APB2Periph_AFIO, DISABLE );
  RCC_APB2PeriphResetCmd( RCC_APB2Periph_GPIOA, DISABLE );
  RCC_APB2PeriphResetCmd( RCC_APB2Periph_GPIOB, DISABLE );
  RCC_APB2PeriphResetCmd( RCC_APB2Periph_GPIOC, DISABLE );
  RCC_APB2PeriphResetCmd( RCC_APB2Periph_GPIOD, DISABLE );

#if 0
  /* Enable spi1 clock enable */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1, ENABLE );
  RCC_APB2PeriphResetCmd( RCC_APB2Periph_SPI1, DISABLE );

  /* DMA1,2 clock enable */
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2, ENABLE);
#endif
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//extern uint32_t _isr_vectorsflash_offs;
void NVIC_Configuration( void )
{
  /* Set the Vector Table base location at 0x08000000+_isr_vectorsflash_offs */
  NVIC_SetVectorTable( NVIC_VectTab_FLASH, 0 );  // VECT_TAB_OFFSET = 0
}
