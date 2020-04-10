/* ----------------------------------------
  1702 utilities
---------------------------------------- */
#include  <1702.h>

/* ----------------------------------------
    prototypes 
---------------------------------------- */

/* ----------------------------------------
    instances or global variables
---------------------------------------- */
extern STM32F_I2C i2c2;

/* ----------------------------------------
    constructor destructor
---------------------------------------- */
BOARD_1702::BOARD_1702()
{
}

BOARD_1702::BOARD_1702( PCA8574 *sc, PCA8574 *rl, const char *s, ID id )
{
  begin( sc, rl, s, id );
}

BOARD_1702::~BOARD_1702()
{
  end();
}

/* ----------------------------------------
    begin and end
---------------------------------------- */
void BOARD_1702::begin( PCA8574 *sc, PCA8574 *rl, const char *s, ID id )
{
  scan = sc;
  relay = rl;
  relayByte = 0;
  relay->write( relayByte );
  str = s;
  semID = id;
  wai_sem( semID );
  scan->write( 0xFF );
  sig_sem( semID );

  wordWrite( SEG_PORT, 0, SEG_MASK );
  pinMode( SEG_A, OUTPUT );
  pinMode( SEG_B, OUTPUT );
  pinMode( SEG_C, OUTPUT );
  pinMode( SEG_D, OUTPUT );
  pinMode( SEG_E, OUTPUT );
  pinMode( SEG_F, OUTPUT );
  pinMode( SEG_G, OUTPUT );
  scanIndex = 0;
}

void BOARD_1702::end()
{
  wai_sem( semID );
  scan->write( 0xFF );
  sig_sem( semID );

  pinMode( SEG_A, INPUT_PULLDOWN );
  pinMode( SEG_B, INPUT_PULLDOWN );
  pinMode( SEG_C, INPUT_PULLDOWN );
  pinMode( SEG_D, INPUT_PULLDOWN );
  pinMode( SEG_E, INPUT_PULLDOWN );
  pinMode( SEG_F, INPUT_PULLDOWN );
  pinMode( SEG_G, INPUT_PULLDOWN );
}


/* ----------------------------------------
    segment data write
---------------------------------------- */
void BOARD_1702::segWrite( char c )
{
  static const uint16_t segDec[] =
  {
    SEG_A_PIN | SEG_B_PIN | SEG_C_PIN | SEG_D_PIN | SEG_E_PIN | SEG_F_PIN,  // 0
    SEG_B_PIN | SEG_C_PIN,  // 1
    SEG_A_PIN | SEG_B_PIN | SEG_G_PIN | SEG_E_PIN | SEG_D_PIN,  // 2
    SEG_A_PIN | SEG_B_PIN | SEG_G_PIN | SEG_C_PIN | SEG_D_PIN,  // 3
    SEG_F_PIN | SEG_G_PIN | SEG_B_PIN | SEG_C_PIN,  // 4
    SEG_A_PIN | SEG_F_PIN | SEG_G_PIN | SEG_C_PIN | SEG_D_PIN,  // 5
    SEG_A_PIN | SEG_F_PIN | SEG_G_PIN | SEG_C_PIN | SEG_D_PIN | SEG_E_PIN,  // 6
    SEG_A_PIN | SEG_B_PIN | SEG_C_PIN,  // 7
    SEG_A_PIN | SEG_B_PIN | SEG_C_PIN | SEG_D_PIN | SEG_E_PIN | SEG_F_PIN | SEG_G_PIN,  // 8
    SEG_A_PIN | SEG_B_PIN | SEG_C_PIN | SEG_D_PIN | SEG_F_PIN | SEG_G_PIN,  // 9
  };
  static const uint16_t segAlpha[] =
  {
    SEG_A_PIN | SEG_B_PIN | SEG_C_PIN | SEG_E_PIN | SEG_F_PIN | SEG_G_PIN,  // A
    SEG_F_PIN | SEG_E_PIN | SEG_D_PIN | SEG_C_PIN | SEG_G_PIN,  // b
    SEG_G_PIN | SEG_E_PIN | SEG_D_PIN,  // c
    SEG_B_PIN | SEG_C_PIN | SEG_D_PIN | SEG_E_PIN | SEG_G_PIN,  // d
    SEG_A_PIN | SEG_F_PIN | SEG_G_PIN | SEG_E_PIN | SEG_D_PIN,  // E
    SEG_A_PIN | SEG_F_PIN | SEG_G_PIN | SEG_E_PIN,  // F
  };

  uint16_t segPattern = 0;
  int moji = c;
  if( isalpha(moji) )
  {
    moji = toupper( moji );
    if( c < 'A' || c > 'F' ) segPattern = 0;
    else
    {
      moji = moji - 'A';
      segPattern = segAlpha[ moji ];
    }
  }
  else if( isdigit(moji) )
  {
    if( c < '0' || c > '9' ) segPattern = 0;
    else
    {
      moji = moji - '0';
      segPattern = segDec[ moji ];
    }
  }
  else segPattern = 0;

  wordWrite( SEG_PORT, segPattern, SEG_MASK );
}

/* ----------------------------------------
    scan line
---------------------------------------- */
void BOARD_1702::scanLine()
{
//  wai_sem( semID );
  switch ( scanIndex )
  {
    case 0 :
      scan->write( ~0x01 );
      break;
    case 1 :
      scan->write( ~0x02 );
      break;
    case 2 :
      scan->write( ~0x04 );
      break;
    case 3 :
      scan->write( ~0x08 );
      break;
    case 4 :
      scan->write( ~0x10 );
      break;
    case 5 :
      scan->write( ~0x20 );
      break;
    default :
      scan->write( 0xFF );
      break;
  }
//  sig_sem( semID );
}

/* ----------------------------------------
    update
---------------------------------------- */
void BOARD_1702::i_update()
{
  T_RSEM pk_rsem;
  ref_sem( semID, &pk_rsem );
  if( pk_rsem.semcnt != 0 )
  {
    /* next index. */
    if( ++scanIndex >= SCAN_INDEX_LIIMIT ) scanIndex = 0;
    return;
  }

  /* turn off segment led. */
  segWrite( 0 );

  /* set scan line. */
  scanLine();

  /* set segment data. */
  segWrite( str[scanIndex] );

  /* next index. */
  if( ++scanIndex >= SCAN_INDEX_LIIMIT ) scanIndex = 0;
}

void BOARD_1702::update()
{
  /* turn off segment led. */
  segWrite( 0 );

  /* set scan line. */
  wai_sem( semID );
  scanLine();
  sig_sem( semID );

  /* set segment data. */
  segWrite( str[scanIndex] );

  /* next index. */
  if( ++scanIndex >= SCAN_INDEX_LIIMIT ) scanIndex = 0;
}


/* ----------------------------------------
    relay On/Off
---------------------------------------- */
void BOARD_1702::relayOnOff( uint8_t bit, bool onOff )
{
  uint8_t tempUC = relayByte & ~bit;  /* bit off */
  if( onOff ) tempUC |= bit;  /* bit on */
  relayByte = tempUC;
  wai_sem( semID );
  relay->write( relayByte );
  sig_sem( semID );
}

