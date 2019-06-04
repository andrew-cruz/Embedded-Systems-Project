#include "led_matrix.h"
#include "io.h"
#include "Entities.h"

unsigned char led_screen[8][8] = {
                       {ENEMY_1,0,0,0,CHERRY_10,0,0,ENEMY_2},
                       {CHERRY_5,0,0,0,0,0,CHERRY_1,0},
                       {0,CHERRY_2,0,0,0,0,0,0},
                       {CHERRY_9,0,0,0,PLAYER,0,0,CHERRY_6},
                       {0,0,0,0,CHERRY_3,0,0,0},
                       {0,CHERRY_4,0,0,0,CHERRY_5,0,0},
                       {0,0,0,0,CHERRY_7,0,0,0},
                       {ENEMY_3,0,CHERRY_9,0,0,0,CHERRY_8,}
             };

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

void SendDataToLED(unsigned char target, unsigned char color) {
  unsigned char column = 0x00;
  unsigned char row = 0xFF;

  for(unsigned char i = 0; i < ROW_SIZE; i++) {
    for(unsigned char j = 0; j < COLUMN_SIZE; j++) {
      if(led_screen[i][j] == target) {
        column = SetBit(column, 7 - j, 1);
        row = SetBit(row, 7 - i, 0);
        goto next;
      }
    }
  }

  next:
    if(color == GREEN) {
      ShiftData(row);
      ShiftData(0xFF);
      ShiftData(0xFF);
    } else if(color == BLUE) {
      ShiftData(0xFF);
      ShiftData(row);
      ShiftData(0xFF);
    } else if(color == RED) {
      ShiftData(0xFF);
      ShiftData(0xFF);
      ShiftData(row);
    } else {
      ShiftData(0xFF);
      ShiftData(0xFF);
      ShiftData(0xFF);
    }
    ShiftData(column);
    ShiftDataEnable();

}
