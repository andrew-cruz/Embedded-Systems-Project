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

  enum GameSMSTATES { Game_Home, Game_Play, Game_Paused, Game_Over };
  int GameSM(int);

  enum JoyStickSMStates {Joystick_Still, JoyStick_Left, JoyStick_Right, JoyStick_Up, JoyStick_Down};
  int JoystickSM(int);

  enum ButtonSMStates { Button_Wait, Button_Press, Button_Release };
  int ButtonSM(int);

  enum PlayerSMStates {Player_Still, Player_Up, Player_Down, Player_Left, Player_Right};
  int PlayerSM(int);

  enum EnemySMStates {Enemy_Still, Enemy_Up, Enemy_Down, Enemy_Left, Enemy_Right};
  int EnemySM(int);

  enum LEDMatrixStates { LED_Matrix_Red, LED_Matrix_Blue, LED_Matrix_Green };
  int LEDMatrixSM(int);

  enum LCDSMStates { LCD_Start, LCD_Play, LCD_Pause, LCD_GameOver };
  int LCD_SM(int);

  enum SoundtStates {SM4_Init, SM4_Left, SM4_Right, SM4_Up, SM4_Down, SM4_Button };
  int SoundSM(int);

#endif
