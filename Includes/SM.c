#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "SM.h"
#include "io.h"
#include "led_matrix.h"

#define FALSE 0x00
#define TRUE 0x01

//Global variables
unsigned char PAUSE = FALSE;
unsigned char GAMEOVER = FALSE;
unsigned char PLAY = FALSE;
unsigned char BUTTON0 = FALSE;

// Monitors button connected to PA0.
// When button is pressed, shared variable "pause" is toggled.
int LCD_SM(int state) {

  // //REPLACE LATER
  // unsigned char button0 = GetBit(~PINA, 3);
  //
  //
  // switch (state) {
  //   case LCD_Start: {
  //     if(button0) {
  //       state = LCD_Play;
  //     } else {
  //       state = LCD_Start;
  //     }
  //     break;
  //   }
  //   case LCD_Play: {
  //     if(button0 & ~button1) {
  //       state = LCD_Pause;
  //     } if(~button0 & button1) {
  //       state = LCD_GameOver;
  //     } else  {
  //       state = LCD_Play;
  //     }
  //     break;
  //   }
  //   case LCD_Pause: {
  //     if(button0) {
  //       state = LCD_Play;
  //     } else {
  //       state = LCD_Pause;
  //     }
  //     break;
  //   }
  //   case LCD_GameOver: {
  //     if(button0) {
  //       state = LCD_Start;
  //     }
  //     break;
  //   }
  //   default : {
  //     state = LCD_Start;
  //     break;
  //   }
  // }
  return 0;
}

// If paused: Do NOT toggle LED connected to PB0
// If unpaused: toggle LED connected to PB0
int Button_SM(int state) {
  //Get Input from button
  unsigned char buttonPress0 = GetBit(~PINA, 3);
  // unsigned char buttonPress1 = GetBit(~PINA, 4);

  //State Transistions for button press
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
      BUTTON0 = (BUTTON0 == FALSE) ? TRUE : FALSE;
      break;
    }
    case Button_Release: break; //Waiting for button to be released
    default: break;
  }

  return state;
}



// If paused: Do NOT toggle LED connected to PB1
// If unpaused: toggle LED connected to PB1
int LED_SM(int state) {
  return 0;
}

// Combine blinking LED outputs from SM2 and SM3, and output on PORTB
int SMTick4(int state) {
  return 0;
}
