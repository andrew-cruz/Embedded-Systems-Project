#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#include "SM.h"
#include "io.h"
#include "led_matrix.h"


// SM for Game Controller
int GameSM(int state) {
  switch (state) {
    case Game_Home : {
      if(START_GAME == TRUE) {
        state = Game_Play;
      } else {
        state = Game_Home;
      }
      break;
    }
    case Game_Play : {
      if(ENEMY_COLLISION == TRUE) {
        state = Game_Over;
      } else if(PAUSE_GAME == TRUE) {
        state = Game_Paused;
      }  else {
        state = Game_Play;
      }
      break;
    }
    case Game_Paused : {
      if(PAUSE_GAME == FALSE) {
        state = Game_Play;
      } else {
        state = Game_Paused;
      }
      break;
    }
    case Game_Over : {
      if(RESTART_GAME == TRUE) {
        state = Game_Home;
      } else {
        state = Game_Over;
      }
      break;
    }
    default : {
      state = Game_Home;
      break;
    }
  }

  switch (state) {
    case Game_Home : {
      GAME_STATE = HOME;
      break;
    }
    case Game_Play : {
      GAME_STATE = GAME;
      break;
    }
    case Game_Paused : {
      GAME_STATE = PAUSED;
      break;
    }
    case Game_Over : {
      GAME_STATE = GAMEOVER;
      break;
    }
    default : {
      break;
    }
  }

  return state;
}

// SM for joystick input
int JoystickSM(int state) {
  if(GAME_STATE != GAME) {
    JOYSTICK_POSITION = STILL;
    return state;
  }
  //Get Input from button
  int16_t x_axis = adc_read(0);
  int16_t y_axis = adc_read(1);

//CS120B FINAL
//KNow #9 and #3.75 and #11

  if( y_axis >= 1023 && x_axis <= 1023 ) { //Joystick is pointing Up
    JOYSTICK_POSITION = LEFT;
  } else if( y_axis <= 25 && x_axis <= 1023) { //Joystick is pointing Down
    JOYSTICK_POSITION = RIGHT;
  } else if(x_axis <= 225 && y_axis <= 1023) { //Joystick is pointing to Right
    JOYSTICK_POSITION = UP;
  } else if(x_axis >= 1023 && y_axis <= 1023) { //JoyStick is pointing to Left
    JOYSTICK_POSITION = DOWN;
  } else {  //JoyStick is in middle
    JOYSTICK_POSITION = STILL;
  }

  return state;
}

// SM for Button Press
int ButtonSM(int state) {
  //Get Input from button
  // unsigned char buttonPress0 = 0;
  unsigned char buttonPress0 = GetBit(~PINB, 0);

  switch (state) {
    case Button_Wait: { //Wait for Button Press
      if(buttonPress0 == 1) {
        state = Button_Press;
      } else {
        state = Button_Wait;
      }
      break;
    }
    case Button_Press: {  //Button had been pressed
      state = Button_Release;
      break;
    }
    case Button_Release: { //Wait for button to get released
      if(buttonPress0 == 0) {
        state = Button_Wait;
      } else {
        state = Button_Release;
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
      if(GAME_STATE == HOME) {
        START_GAME = (START_GAME == FALSE) ? TRUE : FALSE;
        PAUSE_GAME = FALSE;
        RESTART_GAME = FALSE;
      } else if(GAME_STATE == GAME || GAME_STATE == PAUSED) {
        START_GAME = FALSE;
        PAUSE_GAME = (PAUSE_GAME == FALSE) ? TRUE : FALSE;
        RESTART_GAME = FALSE;
      } else if(GAME_STATE == GAMEOVER){
        START_GAME = FALSE;
        PAUSE_GAME = FALSE;
        RESTART_GAME = (RESTART_GAME == FALSE) ? TRUE : FALSE;
      }
      break;
    }
    case Button_Release: break; //Waiting for button to be released
    default: break;
  }

  return state;
}

int PlayerSM(int state) {
  // CheckCollisionEnemy();
  if(JOYSTICK_POSITION == UP) {
    if(PLAYER_POS[0] + 1 > 7) {
      PLAYER_POS[0] = 0;
    } else {
      PLAYER_POS[0] += 1;
    }
  } else if(JOYSTICK_POSITION == DOWN) {
    if(PLAYER_POS[0] - 1 < 0) {
      PLAYER_POS[0] = 7;
    } else {
      PLAYER_POS[0] -= 1;
    }
  } else if(JOYSTICK_POSITION == LEFT) {
    if(PLAYER_POS[1] - 1 < 0) {
      PLAYER_POS[1] = 7;
    } else {
      PLAYER_POS[1] -= 1;
    }
  } else if(JOYSTICK_POSITION == RIGHT) {
    if(PLAYER_POS[1] + 1 > 7) {
      PLAYER_POS[1] = 0;
    } else {
      PLAYER_POS[1] += 1;
    }
  }
  CheckCollisionEnemy();
  CheckCollisionPellet();

  return state;
}

int EnemySM(int state) {
  if(GAME_STATE != GAME) {
    return state;
  }

  for(unsigned char i = 0; i < NUM_ENEMIES; i++) {
    unsigned char direction = rand() % 4;
    if(direction == 0) {
      //Enemy moves left
      if(ENEMY_POS[i][1] - 1 < 0) {
        ENEMY_POS[i][1] = 7;
      } else {
        ENEMY_POS[i][1] -= 1;
      }
    } else if(direction == 1) {
      //Enemy moves right
      if(ENEMY_POS[i][1] + 1 > 7) {
        ENEMY_POS[i][1] = 0;
      } else {
        ENEMY_POS[i][1] += 1;
      }
    } else if(direction == 2) {
      //Enemy moves down
      if(ENEMY_POS[i][0] - 1 < 0) {
        ENEMY_POS[i][0] = 7;
      } else {
        ENEMY_POS[i][0] -= 1;
      }
    } else if(direction == 3) {
      //enemy moves up
      if(ENEMY_POS[i][0] + 1 > 7) {
        ENEMY_POS[i][0] = 0;
      } else {
        ENEMY_POS[i][0] += 1;
      }
    }
  }

  return state;
}

int LEDMatrixSM(int state) {
  static unsigned char prev_state;
  switch (state) {
    case LED_Matrix_OFF: {
      if(GAME_STATE == GAME) {
        state = LED_Matrix_Player;
      } else {
        state = LED_Matrix_OFF;
      }
      break;
    }
    case LED_Matrix_Player: {
      if(GAME_STATE == GAME) {
        state = LED_Matrix_Enemy;
      } else if(GAME_STATE == PAUSED) {
        prev_state = LED_Matrix_Player;
        state = LED_Matrix_Pause;
      } else if(GAME_STATE == GAMEOVER) {
        state = LED_Matrix_GameOver;
      } else {
        state = LED_Matrix_OFF;
      }
      break;
    }
    case LED_Matrix_Enemy: {
      if(GAME_STATE == GAME) {
        state = LED_Matrix_Pelletes;
      } else if(GAME_STATE == PAUSED) {
        prev_state = LED_Matrix_Enemy;
        state = LED_Matrix_Pause;
      } else if(GAME_STATE == GAMEOVER) {
        state = LED_Matrix_GameOver;
      } else {
        state = LED_Matrix_OFF;
      }
      break;
    }
    case LED_Matrix_Pelletes: {
      if(GAME_STATE == GAME){
        state = LED_Matrix_Player;
      } else if(GAME_STATE == PAUSED) {
        prev_state = LED_Matrix_Pelletes;
        state = LED_Matrix_Pause;
      } else if(GAME_STATE == GAMEOVER) {
        state = LED_Matrix_GameOver;
      }  else {
        state = LED_Matrix_OFF;
      }
      break;
    }
    case LED_Matrix_Pause: {
      if(GAME_STATE == GAME) {
        state = prev_state;
      } else {
        state = LED_Matrix_Pause;
      }
      break;
    }
    case LED_Matrix_GameOver: {
      if(GAME_STATE == HOME) {
        state = LED_Matrix_OFF;
      } else {
        state = LED_Matrix_GameOver;
      }
      break;
    }
    default:
      state = LED_Matrix_OFF;
      break;
  }

  switch (state) {
    case LED_Matrix_OFF: {
      LEDOff();
      break;
    }
    case LED_Matrix_Player: {
      SendPlayerToLED();
      break;
    }
    case LED_Matrix_Enemy: {
      SendEnemiesToLED();
      break;
    }
    case LED_Matrix_Pelletes: {
      SendPelletToLED();
      break;
    }
    case LED_Matrix_Pause: {
      LEDPaused();
      break;
    }
    case LED_Matrix_GameOver: {
      LEDGameOver();
      LEDResetComponents();
      break;
    }
    default:
      break;
  }

  return state;
}

// SM for LCD Screen
int LCDScreenSM(int state) {
  static unsigned char count = 0;
  char temp[32] = "";
  char score[10];

  if(GAME_STATE == HOME) {
    itoa(HIGH_SCORE, score, 10);
    strcpy(temp,"Click to start  Highscore:");
    strcat(temp,score);
  } else if(GAME_STATE == GAME) {
    itoa(DECIMAL_SCORE, score, 10);
    strcpy(temp,"Score:");
    strcat(temp, score);
  } else if(GAME_STATE == PAUSED) {
    itoa(DECIMAL_SCORE, score, 10);
    strcpy(temp,"Game Paused     Score:");
    strcat(temp, score);
  } else if(GAME_STATE == GAMEOVER) {
    itoa(DECIMAL_SCORE, score, 10);
    strcpy(temp,"Game Over       ");

    if(DECIMAL_SCORE > HIGH_SCORE) {
      count++;
      if(count <= 5) {
        strcat(temp, "New High Score!");
      } else if(count > 5 && count <= 10) {
        strcat(temp, score);
      } else {
        count = 0;
      }
    } else {
      strcat(temp, "Score: ");
      strcat(temp, score);
    }

  } else {
    strcpy(temp,"ERROR");
  }

  if( strcmp(temp,LCD_DISPLAY_STRING) != 0 ) {
    LCD_ClearScreen();
    strcpy(LCD_DISPLAY_STRING,temp);
    LCD_DisplayString(1,LCD_DISPLAY_STRING);
  }

  return state;
}

// SM for LED Debugging Lights
int SoundSM(int state) {
  return 0;
}
