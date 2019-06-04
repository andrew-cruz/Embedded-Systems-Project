#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__

#include "Entities.h"

  #define COLUMN_SIZE 0x08
  #define ROW_SIZE 0x08

  #define RED 0x01
  #define BLUE 0x02
  #define GREEN 0x03

  #define ENEMY_1 0x04
  #define ENEMY_2 0x05
  #define ENEMY_3 0x06

  #define CHERRY_1 0x07
  #define CHERRY_2 0x08
  #define CHERRY_3 0x09
  #define CHERRY_4 0x0A
  #define CHERRY_5 0x0B
  #define CHERRY_6 0x0C
  #define CHERRY_7 0x0D
  #define CHERRY_8 0x0E
  #define CHERRY_9 0x0F
  #define CHERRY_10 0x10

  #define PLAYER 0x20

  #define FALSE 0x00
  #define TRUE 0x01

  // typedef PLAYER Entity;
  // typedef ENEMY Entity;

  // PLAYER player;
  // ENEMY enemy_1;
  // ENEMY enemy_2;
  // ENEMY enemy_3;

  unsigned char PLAYER_POS[2] = {3 , 4}; //{i,j}

  unsigned char NUM_ENEMIES = 3;
  unsigned char NUM_CHERRIES = 10;

  unsigned char ENEMIES[3] = {ENEMY_1, ENEMY_2, ENEMY_3};
  unsigned char CHERRIES[10] = {CHERRY_1, CHERRY_2, CHERRY_3, CHERRY_4, CHERRY_5, CHERRY_6, CHERRY_7, CHERRY_8, CHERRY_9, CHERRY_10};

  void shiftData(uint8_t data);
  void sendDataToLED(unsigned char t, unsigned char c);
  void clearLED();

  void initGame() {
    // player.x = 3;
    // player.y = 4;
    // player.isDead = FALSE;
    //
    // enemy_1.x = 3;
    // enemy_1.y = 4;
    // enemy_1.isDead = FALSE;
    //
    // enemy_2.x = 3;
    // enemy_2.y = 4;
    // enemy_2.isDead = FALSE;
    //
    // enemy_3.x = 3;
    // enemy_3.y = 4;
    // enemy_3.isDead = FALSE;
  }
#endif
