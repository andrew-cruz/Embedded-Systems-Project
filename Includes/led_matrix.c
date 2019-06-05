
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

void LEDOff() {
  ShiftData(0xFF);
  ShiftData(0xFF);
  ShiftData(0xFF);
  ShiftData(0x00);
  ShiftDataEnable();

  ENEMY_COLLISION = FALSE;

  if(DECIMAL_SCORE > HIGH_SCORE) {
    HIGH_SCORE = DECIMAL_SCORE;
  }
  DECIMAL_SCORE = 0;
}

void LEDPaused() {
  ShiftData(0x00);
  ShiftData(0xFF);
  ShiftData(0xFF);
  ShiftData(0xFF);
  ShiftDataEnable();
}

void LEDGameOver() {
  ShiftData(0xFF);
  ShiftData(0x00);
  ShiftData(0xFF);
  ShiftData(0xFF);
  ShiftDataEnable();
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
