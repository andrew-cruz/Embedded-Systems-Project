#ifndef __SM_H__
#define __SM_H__
  //Enumeration of states for LCD_SM.
  enum LCD_SM_States { LCD_Start, LCD_Play, LCD_Pause, LCD_GameOver };
  int LCD_SM(int);

  enum Button_SM_States { Button_Wait, Button_Press, Button_Release };
  int Button_SM(int);

  enum LED_SM_States { SM3_wait, SM3_blink };
  int LED_SM(int);

  enum SM4_States { SM4_display };
  int SMTick4(int);

#endif
