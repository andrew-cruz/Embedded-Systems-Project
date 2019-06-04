#ifndef __IO_H__
#define __IO_H__

  volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

  //--------Task scheduler data structure---------------------------------------
  // Struct for Tasks represent a running process in our simple real-time operating system.
  typedef struct _task {
    /*Tasks should have members that include: state, period,
    a measurement of elapsed time, and a function pointer.*/
    signed char state; //Task's current state
    unsigned long int period; //Task period
    unsigned long int elapsedTime; //Time elapsed since last task tick
    int (*TickFct)(int); //Task tick function
  } task;

  void LCDInit();
  void LCD_ClearScreen(void);
  void LCD_WriteCommand (unsigned char Command);
  void LCD_Cursor (unsigned char column);
  void LCD_DisplayString(unsigned char column ,const unsigned char *string);
  void delay_ms(int miliSec);
  unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b);
  unsigned char GetBit(unsigned char x, unsigned char k);
  void ADCInit();
  uint16_t adc_read(uint8_t ch);
  unsigned long int findGCD(unsigned long int a, unsigned long int b);

#endif
