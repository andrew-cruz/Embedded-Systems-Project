// #include <stdlib.h>
// #include <time.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "led_matrix.h"
#include "io.h"
#include "SM.h"

void ShiftData(uint8_t data) {
  int i;
  for(i = 7; i >= 0; i--) {
    //SRCLR to HIGH
    //Clear SRCLK
    PORTD = 0x18;
    //SER gets next bit
    PORTD |= ((data >> i) & 0x01);
    //SRCLK HIGH
    PORTD |= 0x14;
  }
  //RCLK HIGH
  PORTD |= 0x12;
  //Clear data Lines
  PORTD = 0x18;
}

void ShiftDataEnable() {
  PORTD = 0x08;
}

void SendPlayerToLED() {
  if(PLAYER_POS[0] < 0 || PLAYER_POS[0] > 7) {
    ShiftData(0xFF);
    ShiftData(0xFF);
    ShiftData(0xFF);
    ShiftData(0x00);
    ShiftDataEnable();
    return;
  }
  if(PLAYER_POS[1] < 0 || PLAYER_POS[1] > 7) {
    ShiftData(0xFF);
    ShiftData(0xFF);
    ShiftData(0xFF);
    ShiftData(0x00);
    ShiftDataEnable();
    return;
  }
  unsigned char column = 0x00;
  unsigned char row = 0xFF;

  column = SetBit(column, PLAYER_POS[0], 1);
  row = SetBit(row, PLAYER_POS[1], 0);

  ShiftData(row);
  ShiftData(0xFF);
  ShiftData(row);
  ShiftData(column);
  ShiftDataEnable();
}

void SendEnemiesToLED() {
  for(unsigned char i = 0; i < NUM_ENEMIES; i++) {
    if(ENEMY_POS[i][1] < 0 || ENEMY_POS[i][1] > 7) {
      ShiftData(0xFF);
      ShiftData(0xFF);
      ShiftData(0xFF);
      ShiftData(0x00);
      ShiftDataEnable();
      continue;
    }
    if(ENEMY_POS[i][0] < 0 || ENEMY_POS[i][0] > 7) {
      ShiftData(0xFF);
      ShiftData(0xFF);
      ShiftData(0xFF);
      ShiftData(0x00);
      ShiftDataEnable();
      continue;
    }
    unsigned char column = 0x00;
    unsigned char row = 0xFF;

    column = SetBit(column, ENEMY_POS[i][1], 1);
    row = SetBit(row, ENEMY_POS[i][0], 0);

    if(ENEMY_POS[i][2] == RED) {
      ShiftData(0xFF);
      ShiftData(0xFF);
      ShiftData(row);
    } else if (ENEMY_POS[i][2] == CYAN) {
      ShiftData(row);
      ShiftData(row);
      ShiftData(0xFF);
    } else if (ENEMY_POS[i][2] == MAGENTA) {
      ShiftData(0xFF);
      ShiftData(row);
      ShiftData(row);
    } else if(ENEMY_POS[i][2] == BLUE){
      ShiftData(0xFF);
      ShiftData(row);
      ShiftData(0xFF);
    } else {
      ShiftData(0xFF);
      ShiftData(0xFF);
      ShiftData(0xFF);
    }

    ShiftData(column);
    ShiftDataEnable();
  }
}

void SendPelletToLED() {
  unsigned char column = 0x00;
  unsigned char row = 0xFF;

  column = SetBit(column, PELLET[1], 1);
  row = SetBit(row, PELLET[0], 0);

  ShiftData(row);
  ShiftData(0xFF);
  ShiftData(0xFF);
  ShiftData(column);
  ShiftDataEnable();
}

void LEDOff(unsigned int i) {
  if(i % 100 == 0) {
    if(PLAYER_POS[0] == 7) {
      PLAYER_POS[1]++;
      if(PLAYER_POS[1] > 7) {
        PLAYER_POS[0]--;
        PLAYER_POS[1] = 7;
      }
    } else if(PLAYER_POS[0] == 0) {
      if(PLAYER_POS[1] == 0) {
        PLAYER_POS[0]++;
        PLAYER_POS[1] = 0;
      } else {
        PLAYER_POS[1]--;
      }
    } else if(PLAYER_POS[1] == 7) {
      PLAYER_POS[0]--;
      if(PLAYER_POS[0] < 0) {
        PLAYER_POS[0] = 0;
        PLAYER_POS[1]--;
      }
    } else if(PLAYER_POS[1] == 0) {
      PLAYER_POS[0]++;
      if(PLAYER_POS[1] > 7) {
        PLAYER_POS[0] = 7;
        PLAYER_POS[1]++;
      }
    }

    for(unsigned char k = 0; k < NUM_ENEMIES; k++) {
      if(ENEMY_POS[k][1] == 7) {
        ENEMY_POS[k][0]++;
        if(ENEMY_POS[k][0] > 7) {
          ENEMY_POS[k][1]--;
          ENEMY_POS[k][0] = 7;
        }
      } else if(ENEMY_POS[k][1] == 0) {
        if(ENEMY_POS[k][0] == 0) {
          ENEMY_POS[k][1]++;
          ENEMY_POS[k][0] = 0;
        } else {
          ENEMY_POS[k][0]--;
        }
      } else if(ENEMY_POS[k][0] == 7) {
        ENEMY_POS[k][1]--;
        if(ENEMY_POS[k][1] < 0) {
          ENEMY_POS[k][1] = 0;
          ENEMY_POS[k][0]--;
        }
      } else if(ENEMY_POS[k][0] == 0) {
        ENEMY_POS[k][1]++;
        if(ENEMY_POS[k][0] > 7) {
          ENEMY_POS[k][1] = 7;
          ENEMY_POS[k][0]++;
        }
      }
    }
  }

  return;
}

void LEDPaused(unsigned int i) {
  if(i % 100) {
    SendPelletToLED();
    SendEnemiesToLED();
    SendPlayerToLED();
  } else {
    ShiftData(0xFF);
    ShiftData(0xFF);
    ShiftData(0xFF);
    ShiftData(0x00);
    ShiftDataEnable();
  }
}

void LEDGameOver(unsigned int i) {
  if(i % 100 == 0) {
    PLAYER_POS[1] -= 1;
    ENEMY_POS[0][0] -= 1;
    ENEMY_POS[1][0] -= 1;
    ENEMY_POS[2][0] -= 1;
    ENEMY_POS[3][0] -= 1;
  }
}


void CheckCollisionPellet() {
  if(PELLET[1] == PLAYER_POS[0]) {
    if(PELLET[0] == PLAYER_POS[1]) {
      DECIMAL_SCORE++;

      unsigned char new_x;
      unsigned char new_y;
      new_x = rand() % 8;
      new_y = rand() % 8;
      if(new_x == PELLET[0] && new_y == PELLET[1]) {
        new_x = rand() % (rand() % 8);
        new_y = rand() % (rand() % 8);
      }
      PELLET[0] = new_x;
      PELLET[1] = new_y;
    }
  }
}

void CheckCollisionEnemy() {
  for(unsigned char i = 0; i < NUM_ENEMIES; i++) {
    if(PLAYER_POS[0] == ENEMY_POS[i][1] && PLAYER_POS[1] == ENEMY_POS[i][0]) {
      ENEMY_COLLISION = TRUE;
      return;
    }
  }
}

void LEDResetComponents() {
  PLAYER_POS[0] = 3;
  PLAYER_POS[1] = 4;

  unsigned char new_x;
  unsigned char new_y;
  new_x = rand() % 8;
  new_y = rand() % 8;
  if(new_x == PELLET[0] && new_y == PELLET[1]) {
    new_x = rand() % (rand() % 8);
    new_y = rand() % (rand() % 8);
  }
  PELLET[0] = new_x;
  PELLET[1] = new_y;

  unsigned char init[4][2] = {{7,0}, {7,7}, {0,0}, {0,7}};
  for(unsigned char i = 0; i < NUM_ENEMIES; i++) {
    ENEMY_POS[i][0] = init[i][0];
    ENEMY_POS[i][1] = init[i][0];
  }

  return;
}

unsigned char RandomNum() {
  unsigned char random_seed = 0;

  for(unsigned char i = 0; i < 16; i++) {
    random_seed = random_seed << 1 | (adc_read(2)&0xb1);
  }

  return random_seed;
}

void GameOverSetup() {
  PLAYER_POS[0] = 4;
  PLAYER_POS[1] = 7;

  for(unsigned char i = 0; i < NUM_ENEMIES; i++) {
    ENEMY_POS[i][0] = 7 + (i + 1);
    ENEMY_POS[i][1] = 4;
  }
  return;
}

void LEDHomeSetup() {
  PLAYER_POS[0] = 7; //UP down
  PLAYER_POS[1] = 4; //Left right

  for(unsigned char i = 0; i < NUM_ENEMIES; i++) {
    ENEMY_POS[i][0] = i;
    ENEMY_POS[i][1] = 7;
  }

  ENEMY_COLLISION = FALSE;

  if(DECIMAL_SCORE > HIGH_SCORE) {
    HIGH_SCORE = DECIMAL_SCORE;
  }
  DECIMAL_SCORE = 0;
  return;
}
