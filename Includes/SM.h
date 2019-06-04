#ifndef __SM_H__
#define __SM_H__

  //MACROS for Global Variable States
    //Button
  #define FALSE 0x00
  #define TRUE 0x01
    //JoyStick
  #define STILL 0x00
  #define LEFT 0x01
  #define RIGHT 0x02
  #define UP 0x03
  #define DOWN 0x04
    //Game State
  #define HOME 0
  #define GAME 1
  #define PUASED 2
  #define GAMEOVER 3

  //Global variables
  unsigned char BUTTON = FALSE;
  unsigned char GAME_STATE = HOME;
  unsigned char JOYSTICK_POSITION = STILL;
  unsigned char LCD_DISPLAY_STRING[12] = "";

  enum GAME_SM_STATES { Game_Home, Game_Play, Game_Paused, Game_Over };
  int GAME_SM(int);

  enum LCD_SM_States { LCD_Start, LCD_Play, LCD_Pause, LCD_GameOver };
  int LCD_SM(int);

  enum Button_SM_States { Button_Wait, Button_Press, Button_Release };
  int Button_SM(int);

  enum JoyStick_SM_States {Joystick_Still, JoyStick_Left, JoyStick_Right, JoyStick_Up, JoyStick_Down};
  int joyStickSM(int);

  enum LED_Matrix_States { LED_Matrix_Red, LED_Matrix_Blue, LED_Matrix_Green };
  int LED_Matrix_SM(int);

  enum LED_Light_States {SM4_Init, SM4_Left, SM4_Right, SM4_Up, SM4_Down, SM4_Button };
  int LED_Light_SM(int);

#endif
