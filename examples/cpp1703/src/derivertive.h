/*********************************************************************************/
/* 全体に関する定義                                                              */
/*                                         designed by hamayan since 2009/05/21  */
/*********************************************************************************/
#ifndef _DERIVERTIVE_H_
#define _DERIVERTIVE_H_

#include  <stm32fPeripheral.h>

/*************************************************************************/
/* クロック関連定義                                                      */
/*************************************************************************/
#if 0
#define  SYS_CLK            (72000000UL)
#define  APB1_CLOCK         (36000000UL)
#define  APB2_CLOCK         (72000000UL)

#define  AHB_PSC_DIV   2
//#define  APB1_PSC_DIV  2
#define  APB1_PSC_DIV  1
#define  AHB_CLK       (SYS_CLK / AHB_PSC_DIV)
#define  APB1_CLK      (AHB_CLK / APB1_PSC_DIV)
#define  TIMX_CLK      (APB1_CLK)
//#define  PSC_DIV       ((TIMX_CLK / 500000UL) - 1)
//#define  PSC_DIV       ((TIMX_CLK / 250000UL) - 1)
#define  PSC_DIV       ((TIMX_CLK / 125000UL) - 1)
#define  PSC_DIV_4M    ((TIMX_CLK / 4000000UL) - 1)

//#ifndef __STM32F10x_H
//typedef  unsigned char   bool;
//enum BOOL { FALSE = 0, TRUE = ~FALSE };
//#endif
#endif

/*************************************************************************/
/* 割込み優先度定義                                                      */
/*************************************************************************/
#define  BASE_PRIORITY      2
#define  BASE_SUB_PRIORITY  0

#if 0
/*************************************************************************/
/* システムレジスタ定義                                                  */
/*************************************************************************/
#define  USGFAULTENA      (1 << 18)
#define  BUSFAULTENA      (1 << 17)
#define  MEMFAULTENA      (1 << 16)

/*************************************************************************/
/* バックアップレジスタ定義                                              */
/*************************************************************************/

/*************************************************************************/
/* PWRレジスタ定義                                                       */
/*************************************************************************/
#define  PWR_CR       *((volatile unsigned long *)((unsigned char *)PWR + 0x00))
#define  PWR_CSR      *((volatile unsigned long *)((unsigned char *)PWR + 0x04))

/*************************************************************************/
/* RCCレジスタ定義                                                       */
/*************************************************************************/
#define  RCC_CR       *((volatile unsigned long *)((unsigned char *)RCC + 0x00))
#define  RCC_CFGR     *((volatile unsigned long *)((unsigned char *)RCC + 0x04))
#define  RCC_CIR      *((volatile unsigned long *)((unsigned char *)RCC + 0x08))
#define  RCC_APB2RSTR *((volatile unsigned long *)((unsigned char *)RCC + 0x0c))
#define  RCC_APB1RSTR *((volatile unsigned long *)((unsigned char *)RCC + 0x10))
#define  RCC_AHBENR   *((volatile unsigned long *)((unsigned char *)RCC + 0x14))
#define  RCC_APB2ENR  *((volatile unsigned long *)((unsigned char *)RCC + 0x18))
#define  RCC_APB1ENR  *((volatile unsigned long *)((unsigned char *)RCC + 0x1c))
#define  RCC_BDCR     *((volatile unsigned long *)((unsigned char *)RCC + 0x20))
#define  RCC_CSR      *((volatile unsigned long *)((unsigned char *)RCC + 0x24))

/*************************************************************************/
/* NVICレジスタ定義                                                      */
/*************************************************************************/
#define  NVIC_TYPE    ((volatile unsigned long *)0xe000e004)
#endif

/*************************************************************************/
/* USART定義                                                             */
/*************************************************************************/
#define  SCI_1_SND_BUFFER_SIZE  0  // 1024
#define  SCI_1_RCV_BUFFER_SIZE  0  // 256
#define  SCI_2_SND_BUFFER_SIZE  0
#define  SCI_2_RCV_BUFFER_SIZE  0
#define  SCI_3_SND_BUFFER_SIZE  0
#define  SCI_3_RCV_BUFFER_SIZE  0
#define  SCI_4_SND_BUFFER_SIZE  0
#define  SCI_4_RCV_BUFFER_SIZE  0
#define  SCI_5_SND_BUFFER_SIZE  0
#define  SCI_5_RCV_BUFFER_SIZE  0

/*************************************************************************/
/* 端子定義                                                              */
/*************************************************************************/
/* USART1 TXD RXD */
#define  USART1_TXD_PORT      GPIOA
#define  USART1_RXD_PORT      GPIOA
#define  USART1_TXD_PIN       GPIO_Pin_9
#define  USART1_RXD_PIN       GPIO_Pin_10

/* USART2 TXD RXD */
#define  USART2_TXD_PORT      GPIOA
#define  USART2_RXD_PORT      GPIOA
#define  USART2_TXD_PIN       GPIO_Pin_2
#define  USART2_RXD_PIN       GPIO_Pin_3

/* USART3 TXD RXD */
#define  USART3_TXD_PORT      GPIOB
#define  USART3_RXD_PORT      GPIOB
#define  USART3_TXD_PIN       GPIO_Pin_10
#define  USART3_RXD_PIN       GPIO_Pin_11

/* UART4 TXD RXD */
#define  UART4_TXD_PORT      GPIOC
#define  UART4_RXD_PORT      GPIOC
#define  UART4_TXD_PIN       GPIO_Pin_10
#define  UART4_RXD_PIN       GPIO_Pin_11

/* UART5 TXD RXD */
#define  UART5_TXD_PORT      GPIOC
#define  UART5_RXD_PORT      GPIOD
#define  UART5_TXD_PIN       GPIO_Pin_12
#define  UART5_RXD_PIN       GPIO_Pin_2

#define  GCLK_RESET PA8
#define  TXD1       PA9
#define  RXD1       PA10
#define  DIVCLK     PA11
#define  GCLK       PA12
#define  SWDIO      PA13
#define  SWDCLK     PA14
#define  RTS4       PA15
#define  SEG_A      PB3
#define  SEG_B      PB4
#define  SEG_C      PB5
#define  SEG_D      PB6
#define  SEG_E      PB7
#define  SEG_F      PB8
#define  SEG_G      PB9
#define  SCL2       PB10
#define  SDA2       PB11
#define  SD_SS      PB12
#define  SPI2_SCK   PB13
#define  SPI2_MISO  PB14
#define  SPI2_MOSI  PB15
#define  DIO0       PC0
#define  DIO1       PC1
#define  DIO2       PC2
#define  DIO3       PC3
#define  W5500_INT  PC5
#define  SD_CD      PC6
#define  W5500_CS   PC7
#define  W5500_RST  PC8
#define  PPS        PC9
#define  TXD4       PC10
#define  RXD4       PC11
#define  TXD5       PC12
#define  ACT_LED    PC13
#define  RXD5       PD2

#define  I2C2_PORT  GPIOB
#define  I2C2_SCL_PIN  GPIO_Pin_10
#define  I2C2_SDA_PIN  GPIO_Pin_11
#define  I2C2_SCL_IS_0  I2C2_PORT->BSRR = (I2C2_SCL_PIN << 16)
#define  I2C2_SCL_IS_1  I2C2_PORT->BSRR = (I2C2_SCL_PIN << 0)
#define  I2C2_SDA_IS_0  I2C2_PORT->BSRR = (I2C2_SCL_PIN << 16)
#define  I2C2_SDA_IS_1  I2C2_PORT->BSRR = (I2C2_SCL_PIN << 0)

/* ACT LED */
#define  ACT_PORT   GPIOC
#define  ACT_PIN    GPIO_Pin_13
#define  ACT_IS_0   ACT_PORT->BSRR = (ACT_PIN << 16)
#define  ACT_IS_1   ACT_PORT->BSRR = (ACT_PIN)

/* US2066 */
#define  US2066_I2C       I2C2
#define  RCC_US2066_I2C   RCC_APB1Periph_I2C2
#define  US2066_0_ADR     (0x3C << 0)
#define  US2066_SCL_PORT  GPIOB
#define  US2066_SDA_PORT  GPIOB
#define  US2066_SCL_PIN   GPIO_Pin_10
#define  US2066_SDA_PIN   GPIO_Pin_11
#define  US2066_SCL_IS_0  US2066_SCL_PORT->BSRR = (US2066_SCL_PIN << 16)
#define  US2066_SCL_IS_1  US2066_SCL_PORT->BSRR = (US2066_SCL_PIN << 0)
#define  US2066_SDA_IS_0  US2066_SDA_PORT->BSRR = (US2066_SDA_PIN << 16)
#define  US2066_SDA_IS_1  US2066_SDA_PORT->BSRR = (US2066_SDA_PIN << 0)

/* ----------------------------------------
    board 1716
---------------------------------------- */
#define  BOARD_1716_OUTLED  PC10
#define  BOARD_1716_ACTLED  PA15

/*************************************************************************/
/* その他の定義                                                          */
/*************************************************************************/
#if 0
typedef enum
{
  STDNULL=0,
  STDOUT=1,
  STDOUT2,
  STDOUT3,
  STDOUT4,
  STDOUT5,
  STDEND,
} HANDLES;
#define  STDIN                    STDOUT

#define  Cpu_Delay100US(delay)    Dly100us(delay)
#define  HEAPSIZE                 (10000)  /**/

typedef struct
{
  const char *fn;
  const char *dateTime;
  unsigned long dataOffset;
  void *data;
  const char *auth;
  void *exec;
  unsigned long dataSize;
} FILE_PROPERTIES;
#endif

/*************************************************************************/
/* 大域変数宣言                                                          */
/*************************************************************************/

/*************************************************************************/
/* プロトタイプ宣言                                                      */
/*************************************************************************/
#if 0
//#include  "mul_tsk.h"
int xprintf(int fd,const char *fmt, ...);
int _xwrite(int fd, char *str, int len);
int _xread(int fd, char *str, int len);
void gpioInit( void );
void Dly10us( int delay );
void Dly50us( int delay );
void Dly100us( int delay );
void cris_en( void );  // stop he interrupt.
void cris_ex( void );  // start he interrupt.
#endif

/*************************************************************************/
/* マルチタスク関連                                                      */
/*************************************************************************/
#define  MAX_TASK_NUMBER  3  //
enum GR_SAKURA_TSK_ID
{
  ID_stackMonitor,
  ID_loopBack,
//  ID_board1716,
  ID_board1702,
};

#define  MAX_MBX_NUMBER    3  //最大メールボックス数
enum GR_SAKURA_MBX_ID
{
  MBXID_dummy,         //使用しない
  MBXID_ANONYMOUS_IF,         //
  MBXID_ATCMD,         //
};

#define  MAX_SEM_NUMBER    1
enum GR_SAKURA_SEM_ID
{
  SEMID_I2C = 1,
};

//暴走箇所を検出するデバッグメッセージ
#define _DBG_passedFileAndLine() {strncpy(_file, __FILE__, sizeof(_file)); _line = __LINE__;}
extern char _file[];
extern int _line;


#endif /*_DERIVERTIVE_H_*/


/*********************************************************************************/
/* end of file                                                                   */
/*                                         designed by hamayan since 2009/05/21  */
/*********************************************************************************/
