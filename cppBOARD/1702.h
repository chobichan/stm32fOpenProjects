/* ----------------------------------------
 1702 utility header

---------------------------------------- */
#ifndef  __BOARD_1702_H__
#define  __BOARD_1702_H__

#include  <Timer.h>
#include  <Wire.h>
//#include  <..\stm32f1xx_cppLib\gpio.h>
#include  <gpio.h>
#include  <pca8574.h>
extern "C"
{
  #include  <mul_tsk.h>
  #include  <ctype.h>
}

#define  SCAN_INDEX_LIIMIT  6

#define  SEG_A      PB3
#define  SEG_B      PB4
#define  SEG_C      PB5
#define  SEG_D      PB6
#define  SEG_E      PB7
#define  SEG_F      PB8
#define  SEG_G      PB9

#define  SEG_PORT   GPIOB
#define  SEG_A_PIN  GPIO_Pin_3
#define  SEG_B_PIN  GPIO_Pin_4
#define  SEG_C_PIN  GPIO_Pin_5
#define  SEG_D_PIN  GPIO_Pin_6
#define  SEG_E_PIN  GPIO_Pin_7
#define  SEG_F_PIN  GPIO_Pin_8
#define  SEG_G_PIN  GPIO_Pin_9
#define  SEG_MASK  (SEG_A_PIN | SEG_B_PIN | SEG_C_PIN | SEG_D_PIN | SEG_E_PIN | SEG_F_PIN | SEG_G_PIN)

#define  IC3_RELAY1_BIT  0x01
#define  IC3_RELAY2_BIT  0x02
#define  IC3_RELAY3_BIT  0x04
#define  IC3_RELAY4_BIT  0x08
#define  IC3_DATE_BIT    0x10
#define  IC3_TIME_BIT    0x20
#define  IC3_LOCK_BIT    0x40


/* ----------------------------------------
    prototypes 
---------------------------------------- */

/* ----------------------------------------
    instances or global variables
---------------------------------------- */

//class BOARD_1702 : public GPIO
class BOARD_1702 : public STM32F_TIMER
{
public:
  BOARD_1702();
  BOARD_1702( PCA8574 *sc, PCA8574 *rl, const char *s, ID id = 0 );
  ~BOARD_1702();

  void begin( PCA8574 *sc, PCA8574 *rl, const char *s, ID id = 0 );
  void end();
  void i_update();
  void update();

  void relayOnOff( uint8_t bit, bool onOff );

private:
  PCA8574 *scan,*relay;
  uint8_t relayByte;
  int scanIndex;
  const char *str;
  ID semID;

  void segWrite( char c );
  void scanLine();
};


#endif  /* __BOARD_1702_H__ */

