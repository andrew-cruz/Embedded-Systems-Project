#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#include "SM.h"
#include "io.h"
#include "led_matrix.h"
#include "Entities.h"

// SM for Game Controller
int GameSM(int state) {
  switch (state) {
    case Game_Home : {
      state = Game_Play;
      break;
    }
    case Game_Play : {
      break;
    }
    case Game_Paused : {
      break;
    }
    case Game_Over : {
      break;
    }
    default : {
      state = Game_Play;
      break;
    }
  }

  switch (state) {
    case Game_Home : {
      // initGame();
      break;
    }
    case Game_Play : {

      break;
    }
    case Game_Paused : {
      break;
    }
    case Game_Over : {
      break;
    }
    default : {
      break;
    }
  }

  return 0;
}

// SM for joystick input
int JoystickSM(int state) {
  //Get Input from button
  int16_t x_axis = adc_read(0);
  int16_t y_axis = adc_read(1);
  // unsigned char buttonPress1 = GetBit(~PINA, 4);

  switch (state) {
    case Joystick_Still: { //Wait for Joystick Input
      if( y_axis >= 1023 && x_axis <= 1023 ) { //Joystick is pointing Up
        state = JoyStick_Down;
  		} else if( y_axis <= 25 && x_axis <= 1023) { //Joystick is pointing Down
        state = JoyStick_Up;
  		} else if(x_axis <= 225 && y_axis <= 1023) { //Joystick is pointing to Right
        state = JoyStick_Left;
  		} else if(x_axis >= 1023 && y_axis <= 1023) { //JoyStick is pointing to Left
        state = JoyStick_Right;
  		} else {  //JoyStick is in middle
        state = Joystick_Still;
  		}
      break;
    }
    case JoyStick_Left: {  //Button had been pressed
      if( y_axis >= 1023 && x_axis <= 1023 ) { //Joystick is pointing Up
        state = JoyStick_Down;
  		} else if( y_axis <= 25 && x_axis <= 1023) { //Joystick is pointing Down
        state = JoyStick_Up;
  		} else if(x_axis <= 225 && y_axis <= 1023) { //Joystick is pointing to Right
        state = JoyStick_Left;
  		} else if(x_axis >= 1023 && y_axis <= 1023) { //JoyStick is pointing to Left
        state = JoyStick_Right;
  		} else {  //JoyStick is in middle
        state = Joystick_Still;
  		}
      break;
    }
    case JoyStick_Right: { //Wait for button to get released
      if( y_axis >= 1023 && x_axis <= 1023 ) { //Joystick is pointing Up
        state = JoyStick_Down;
  		} else if( y_axis <= 25 && x_axis <= 1023) { //Joystick is pointing Down
        state = JoyStick_Up;
  		} else if(x_axis <= 225 && y_axis <= 1023) { //Joystick is pointing to Right
        state = JoyStick_Left;
  		} else if(x_axis >= 1023 && y_axis <= 1023) { //JoyStick is pointing to Left
        state = JoyStick_Right;
  		} else {  //JoyStick is in middle
        state = Joystick_Still;
  		}
      break;
    }
    case JoyStick_Up: {  //Button had been pressed
      if( y_axis >= 1023 && x_axis <= 1023 ) { //Joystick is pointing Up
        state = JoyStick_Down;
  		} else if( y_axis <= 25 && x_axis <= 1023) { //Joystick is pointing Down
        state = JoyStick_Up;
  		} else if(x_axis <= 225 && y_axis <= 1023) { //Joystick is pointing to Right
        state = JoyStick_Left;
  		} else if(x_axis >= 1023 && y_axis <= 1023) { //JoyStick is pointing to Left
        state = JoyStick_Right;
  		} else {  //JoyStick is in middle
        state = Joystick_Still;
  		}
      break;
    }
    case JoyStick_Down: { //Wait for button to get released
      if( y_axis >= 1023 && x_axis <= 1023 ) { //Joystick is pointing Up
        state = JoyStick_Down;
  		} else if( y_axis <= 25 && x_axis <= 1023) { //Joystick is pointing Down
        state = JoyStick_Up;
  		} else if(x_axis <= 225 && y_axis <= 1023) { //Joystick is pointing to Right
        state = JoyStick_Left;
  		} else if(x_axis >= 1023 && y_axis <= 1023) { //JoyStick is pointing to Left
        state = JoyStick_Right;
  		} else {  //JoyStick is in middle
        state = Joystick_Still;
  		}
      break;
    }
    default: {  //Default to joystick in middle position
      state = Joystick_Still;
      break;
    }
  }

  switch (state) { //State Machine actions
    case Joystick_Still: JOYSTICK_POSITION = STILL; //Joystick is still
      break;
    case JoyStick_Left: JOYSTICK_POSITION = LEFT; //Joystick is in left pos
      break;
    case JoyStick_Right: JOYSTICK_POSITION = RIGHT; //Joystick is in right pos
      break;
    case JoyStick_Up: JOYSTICK_POSITION = UP; //Joystick is in up pos
      break;
    case JoyStick_Down: JOYSTICK_POSITION = DOWN; //Joystick is in down pos
      break;
    default: JOYSTICK_POSITION = STILL; //Default to middle pos
      break;
  }

  return state;
}

// SM for Button Press
int ButtonSM(int state) {
  //Get Input from button
  unsigned char buttonPress0 = GetBit(~PINA, 3);
  // unsigned char buttonPress1 = GetBit(~PINA, 4);

  switch (state) {
    case Button_Wait: { //Wait for Button Press
      if(buttonPress0) {
        state = Button_Press;
      }
      break;
    }
    case Button_Press: {  //Button had been pressed
      state = Button_Release;
      break;
    }
    case Button_Release: { //Wait for button to get released
      if(~buttonPress0) {
        state = Button_Wait;
      }
      break;
    }
    default: {
      state = Button_Wait;
      break;
    }
  }

  //State Machine actions
  switch (state) {
    case Button_Wait: break; //Waiting for button to press no action
    case Button_Press: {  //Button pressed. Update global variable
      BUTTON = (BUTTON == FALSE) ? TRUE : FALSE;
      break;
    }
    case Button_Release: break; //Waiting for button to be released
    default: break;
  }

  return state;
}

int PlayerSM(int state) {
  switch (state) {
    case Player_Still: {
      if(JOYSTICK_POSITION == STILL) {
        state = Player_Still;
      } else if(JOYSTICK_POSITION == UP) {
        state = Player_Up;
      } else if(JOYSTICK_POSITION == DOWN) {
        state = Player_Down;
      } else if(JOYSTICK_POSITION == LEFT) {
        state = Player_Left;
      } else if(JOYSTICK_POSITION == RIGHT) {
        state = Player_Right;
      } else {
        state = Player_Still;
      }
      break;
    }
    case Player_Up: {
      if(JOYSTICK_POSITION == STILL) {
        state = Player_Still;
      } else if(JOYSTICK_POSITION == UP) {
        state = Player_Up;
      } else if(JOYSTICK_POSITION == DOWN) {
        state = Player_Down;
      } else if(JOYSTICK_POSITION == LEFT) {
        state = Player_Left;
      } else if(JOYSTICK_POSITION == RIGHT) {
        state = Player_Right;
      } else {
        state = Player_Still;
      }
      break;
    }
    case Player_Down: {
      if(JOYSTICK_POSITION == STILL) {
        state = Player_Still;
      } else if(JOYSTICK_POSITION == UP) {
        state = Player_Up;
      } else if(JOYSTICK_POSITION == DOWN) {
        state = Player_Down;
      } else if(JOYSTICK_POSITION == LEFT) {
        state = Player_Left;
      } else if(JOYSTICK_POSITION == RIGHT) {
        state = Player_Right;
      } else {
        state = Player_Still;
      }
      break;
    }
    case Player_Left: {
      if(JOYSTICK_POSITION == STILL) {
        state = Player_Still;
      } else if(JOYSTICK_POSITION == UP) {
        state = Player_Up;
      } else if(JOYSTICK_POSITION == DOWN) {
        state = Player_Down;
      } else if(JOYSTICK_POSITION == LEFT) {
        state = Player_Left;
      } else if(JOYSTICK_POSITION == RIGHT) {
        state = Player_Right;
      } else {
        state = Player_Still;
      }
      break;
    }
    case Player_Right: {
      if(JOYSTICK_POSITION == STILL) {
        state = Player_Still;
      } else if(JOYSTICK_POSITION == UP) {
        state = Player_Up;
      } else if(JOYSTICK_POSITION == DOWN) {
        state = Player_Down;
      } else if(JOYSTICK_POSITION == LEFT) {
        state = Player_Left;
      } else if(JOYSTICK_POSITION == RIGHT) {
        state = Player_Right;
      } else {
        state = Player_Still;
      }
      break;
    }
    default: {
      state = Player_Still;
      break;
    }
  }

  switch (state) {
    case Player_Still: {
      //DO Nothing to Player Position
      break;
    }
    case Player_Up: {
      //Move i component up
      if(PLAYER_POS[0] - 1 < 0) {
        PLAYER_POS[0] = 7;
      } else {
        PLAYER_POS[0] -= 1;
      }
      break;
    }
    case Player_Down: {
      //Move i component down
      if(PLAYER_POS[0] + 1 > 7) {
        PLAYER_POS[0] = 0;
      } else {
        PLAYER_POS[0] += 1;
      }
      break;
    }
    case Player_Left: {
      //Move j component left
      if(PLAYER_POS[1] - 1 < 0) {
        PLAYER_POS[1] = 7;
      } else {
        PLAYER_POS[1] -= 1;
      }
      break;
    }
    case Player_Right: {
      //Move j component right
      if(PLAYER_POS[1] + 1 > 7) {
        PLAYER_POS[1] = 0;
      } else {
        PLAYER_POS[1] += 1;
      }
      break;
    }
    default: {
      break;
    }
  }
}

int EnemySM(int state) {
  return 0;
}

int LEDMatrixSM(int state) {
  switch (state) {
    case LED_Matrix_Red: {
      state = LED_Matrix_Blue;
      break;
    }
    case LED_Matrix_Blue: {
      state = LED_Matrix_Green;
      break;
    }
    case LED_Matrix_Green: {
      state = LED_Matrix_Red;
      break;
    }
    default:
      state = LED_Matrix_Red;
      break;
  }

  switch (state) {
    case LED_Matrix_Red: {
        for(unsigned char i = 0; i < NUM_ENEMIES; i++) {
          SendDataToLED(ENEMIES[i], RED);
        }
      break;
    }
    case LED_Matrix_Blue: {
      SendPlayerToLED();
      break;
    }
    case LED_Matrix_Green: {
      for(unsigned char i = 0; i < NUM_CHERRIES; i++) {
        SendDataToLED(CHERRIES[i], GREEN);
      }
      break;
    }
    default:
      break;
  }

  return state;
}

// SM for LCD Screen
int LCDScreenSM(int state) {
  unsigned char temp[12] = "";

  if(JOYSTICK_POSITION == STILL) {
    strcpy(temp,"Still");
  } else if(JOYSTICK_POSITION == LEFT) {
    strcpy(temp,"Left");
  } else if(JOYSTICK_POSITION == RIGHT) {
    strcpy(temp,"Right");
  } else if(JOYSTICK_POSITION == UP) {
    strcpy(temp,"Up");
  } else if(JOYSTICK_POSITION == DOWN) {
    strcpy(temp,"Down");
  } else {
    strcpy(temp,"Still");
  }

  if(strcmp(temp,LCD_DISPLAY_STRING) != 0) {
    LCD_ClearScreen();
    strcpy(LCD_DISPLAY_STRING,temp);
    LCD_DisplayString(1,LCD_DISPLAY_STRING);
  }
  return state;
}

// SM for LED Debugging Lights
int SoundSM(int state) {
  switch (state) {
    case SM4_Init: { //Wait for Joystick Input
      if(JOYSTICK_POSITION == LEFT) {
        state = SM4_Left;
      } else if(JOYSTICK_POSITION == RIGHT) {
        state = SM4_Right;
      } else if(JOYSTICK_POSITION == UP) {
        state = SM4_Up;
      } else if(JOYSTICK_POSITION == DOWN) {
        state = SM4_Down;
      } else if(BUTTON == TRUE) {
        state = SM4_Button;
      } else {
        state = SM4_Init;
      }
      break;
    }
    case SM4_Left: { //Wait for Joystick Input
      if(JOYSTICK_POSITION == LEFT) {
        state = SM4_Left;
      } else if(JOYSTICK_POSITION == RIGHT) {
        state = SM4_Right;
      } else if(JOYSTICK_POSITION == UP) {
        state = SM4_Up;
      } else if(JOYSTICK_POSITION == DOWN) {
        state = SM4_Down;
      } else if(BUTTON == TRUE) {
        state = SM4_Button;
      } else {
        state = SM4_Init;
      }
      break;
    }
    case SM4_Right: {  //Button had been pressed
      if(JOYSTICK_POSITION == LEFT) {
        state = SM4_Left;
      } else if(JOYSTICK_POSITION == RIGHT) {
        state = SM4_Right;
      } else if(JOYSTICK_POSITION == UP) {
        state = SM4_Up;
      } else if(JOYSTICK_POSITION == DOWN) {
        state = SM4_Down;
      } else if(BUTTON == TRUE) {
        state = SM4_Button;
      } else {
        state = SM4_Init;
      }
      break;
    }
    case SM4_Up: { //Wait for button to get released
      if(JOYSTICK_POSITION == LEFT) {
        state = SM4_Left;
      } else if(JOYSTICK_POSITION == RIGHT) {
        state = SM4_Right;
      } else if(JOYSTICK_POSITION == UP) {
        state = SM4_Up;
      } else if(JOYSTICK_POSITION == DOWN) {
        state = SM4_Down;
      } else if(BUTTON == TRUE) {
        state = SM4_Button;
      } else {
        state = SM4_Init;
      }
      break;
    }
    case SM4_Down: {  //Button had been pressed
      if(JOYSTICK_POSITION == LEFT) {
        state = SM4_Left;
      } else if(JOYSTICK_POSITION == RIGHT) {
        state = SM4_Right;
      } else if(JOYSTICK_POSITION == UP) {
        state = SM4_Up;
      } else if(JOYSTICK_POSITION == DOWN) {
        state = SM4_Down;
      } else if(BUTTON == TRUE) {
        state = SM4_Button;
      } else {
        state = SM4_Init;
      }
      break;
    }
    case SM4_Button: { //Wait for button to get released
      if(JOYSTICK_POSITION == LEFT) {
        state = SM4_Left;
      } else if(JOYSTICK_POSITION == RIGHT) {
        state = SM4_Right;
      } else if(JOYSTICK_POSITION == UP) {
        state = SM4_Up;
      } else if(JOYSTICK_POSITION == DOWN) {
        state = SM4_Down;
      } else if(BUTTON == TRUE) {
        state = SM4_Button;
      } else {
        state = SM4_Init;
      }
      break;
    }
    default: {  //Default to joystick in middle position
      state = SM4_Init;
      break;
    }
  }
  unsigned char temp;
  switch (state) {
    case SM4_Init: {
      PORTB = PORTB & 0xE0;
      break;
    }
    case SM4_Left: {
      temp = PORTB & 0xE0;
      PORTB = temp | 0x04;
      break;
    }
    case SM4_Right: {
      temp = PORTB & 0xE0;
      PORTB = temp | 0x01;
      break;
    }
    case SM4_Up: {
      temp = PORTB & 0xE0;
      PORTB = temp | 0x08;
      break;
    }
    case SM4_Down: {
      temp = PORTB & 0xE0;
      PORTB = temp | 0x02;
      break;
    }
    case SM4_Button: {
      temp = PORTB & 0xE0;
      PORTB = temp | 0x10;
      break;
    }
    default: {
      break;
    }
  }

  return 0;
}
