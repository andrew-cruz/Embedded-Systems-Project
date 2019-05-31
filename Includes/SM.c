#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#include "SM.h"
#include "io.h"
#include "led_matrix.h"

// SM for Game Controller
int GAME_SM(int state) {
  switch (state) {
    case Game_Home : {
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

  switch (state) {
    case Game_Home : {
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

// SM for LCD Screen
int LCD_SM(int state) {
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

  return 0;
}

// SM for Button Press
int Button_SM(int state) {
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

// SM for joystick input
int joyStickSM(int state) {
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

// SM fir LED Matrix
int LED_Matrix_SM(int state) {
  return 0;
}

// SM for LED Debugging Lights
int LED_Light_SM(int state) {
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
