#ifndef __IO_H__
#define __IO_H__

  volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

  void LCDInit();
  void LCD_ClearScreen(void);
  void LCD_WriteCommand (unsigned char Command);
  void LCD_Cursor (unsigned char column);
  void LCD_DisplayString(unsigned char column ,const unsigned char *string);
  void delay_ms(int miliSec);
  unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b);
  unsigned char GetBit(unsigned char x, unsigned char k);
  void ADC_init();
  void ADCInit();
  uint16_t adc_read(uint8_t ch);
  
#endif
