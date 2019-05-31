#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__

  #define SHIFT_REG_DATA_BUS PORTD

  #define DATA 4
  #define DATA_OUTPUT_ENABLE 3
  #define LATCH 2
  #define CLOCK 1
  #define RESET 0

  #define HIGH 1
  #define LOW 0

  #define COLUMN_SIZE 8
  #define ROW_SIZE 8

  #define RED 0
  #define GREEN 1
  #define BLUE 2

  unsigned char ledScreen[8][8] = {
						             {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0}
							 };
   unsigned char HappyFace[8][8] = {
                           {1,0,1,0,1,0,1,0},
                           {1,0,1,0,1,0,1,0},
                           {1,0,1,0,1,0,1,0},
                           {1,0,1,0,1,0,1,0},
                           {1,0,1,0,1,0,1,0},
                           {1,0,1,0,1,0,1,0},
                           {1,0,1,0,1,0,1,0},
                           {1,0,1,0,1,0,1,0}
                       };

  void shiftRegInit();
  void shiftData(uint8_t data);
  void displayData();
  void clearShiftRegister();
  void sendDataToLED();
  void clearLED();

#endif
