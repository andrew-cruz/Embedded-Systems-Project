#include "led_matrix.h"
#include "io.h"

unsigned char matrix[8][8] = {
                       {ENEMY_1,0,0,0,CHERRY_10,0,0,ENEMY_2},
                       {CHERRY_5,0,0,0,0,0,CHERRY_1,0},
                       {0,CHERRY_2,0,0,0,0,0,0},
                       {CHERRY_9,0,0,0,PLAYER,0,0,CHERRY_6},
                       {0,0,0,0,CHERRY_3,0,0,0},
                       {0,CHERRY_4,0,0,0,CHERRY_5,0,0},
                       {0,0,0,0,CHERRY_7,0,0,0},
                       {ENEMY_3,0,CHERRY_9,0,0,0,CHERRY_8,}
             };

void shiftData(uint8_t data) {
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

void shiftData_() {
  PORTD = 0x08;
}

sendRedToLED() {
  unsigned char column = 0x00;
  unsigned char row = 0xFF;

  for(unsigned char i = 0; i < ROW_SIZE; i++) {
    for(unsigned char j = 0; j < COLUMN_SIZE; j++) {
      if(matrix[i][j] == RED) {
        column = SetBit(column, 7 - j, 1);
        row = SetBit(row, 7 - i, 0);
      }
    }
  }

  shiftData(0xFF); //Green
  shiftData(0xFF); //Blue
  shiftData(row); //Red
  shiftData(column); //Colum
  shiftData_();

}

sendBlueToLED() {
  unsigned char column = 0x00;
  unsigned char row = 0xFF;

  for(unsigned char i = 0; i < ROW_SIZE; i++) {
    for(unsigned char j = 0; j < COLUMN_SIZE; j++) {
      if(matrix[i][j] == BLUE) {
        column = SetBit(column, 7 - j, 1);
        row = SetBit(row, 7 - i, 0);
      }
    }
  }

  shiftData(0xFF); //Green
  shiftData(row); //Blue
  shiftData(0xFF); //Red
  shiftData(column); //Colum
  shiftData_();

}

sendGreenToLED() {
  unsigned char column = 0x00;
  unsigned char row = 0xFF;

  for(unsigned char i = 0; i < ROW_SIZE; i++) {
    for(unsigned char j = 0; j < COLUMN_SIZE; j++) {
      if(matrix[i][j] == GREEN) {
        column = SetBit(column, 7 - j, 1);
        row = SetBit(row, 7 - i, 0);
      }
    }
  }

  shiftData(row); //Green
  shiftData(0xFF); //Blue
  shiftData(0xFF); //Red
  shiftData(column); //Colum
  shiftData_();

}

void sendDataToLED(unsigned char target, unsigned char color) {

  unsigned char column = 0x00;
  unsigned char row = 0xFF;

  for(unsigned char i = 0; i < ROW_SIZE; i++) {
    for(unsigned char j = 0; j < COLUMN_SIZE; j++) {
      if(matrix[i][j] == target) {
        column = SetBit(column, 7 - j, 1);
        row = SetBit(row, 7 - i, 0);
        goto next;
      }
    }
  }

  next:
    if(color == GREEN) {
      shiftData(row);
      shiftData(0xFF);
      shiftData(0xFF);
    } else if(color == BLUE) {
      shiftData(0xFF);
      shiftData(row);
      shiftData(0xFF);
    } else if(color == RED) {
      shiftData(0xFF);
      shiftData(0xFF);
      shiftData(row);
    } else {
      shiftData(0xFF);
      shiftData(0xFF);
      shiftData(0xFF);
    }
    shiftData(column);
    shiftData_();

}

void clearLED() {
  for(int i = 0; i < 4; i++) {
    shiftData(0x00);
  }
}
