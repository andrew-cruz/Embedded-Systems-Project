#include "led_matrix.h"
#include "io.h"

#define DATA_BUS PORTD
#define DATA 0
#define DATA_OUTPUT_ENABLE 1
#define LATCH 2
#define CLOCK 3
#define RESET 4

#define HIGH 1
#define LOW 0

#define COLUMN_SIZE 8
#define ROW_SIZE 8

#define RED 0
#define GREEN 1
#define BLUE 2

unsigned char HappyFace[8][8] = {{0,0,3,3,3,3,0,0},
                        {0,3,3,3,3,3,3,0},
                        {3,3,4,3,3,4,3,3},
                        {3,3,3,3,3,3,3,3},
                        {3,3,3,3,3,3,3,3},
                        {3,3,2,3,3,2,3,3},
                        {0,3,3,2,2,3,3,0},
                        {0,0,3,3,3,3,0,0}};


void init() {
  SetBit(DATA_BUS, DATA, LOW);
  SetBit(DATA_BUS, DATA_OUTPUT_ENABLE, LOW);
  SetBit(DATA_BUS, LATCH, LOW);
  SetBit(DATA_BUS, CLOCK, LOW);

  SetBit(DATA_BUS, RESET, HIGH);

}

void transmitData(uint8_t data) {
  SetBit(DATA_BUS, DATA,  data);
  SetBit(DATA_BUS, CLOCK, HIGH);
  SetBit(DATA_BUS, CLOCK, LOW);
  SetBit(DATA_BUS, DATA,  LOW);
}

void sendDataToLED() {
  unsigned char line;
  unsigned char row;
  uint8_t type;

  for(line = 0; line < COLUMN_SIZE; line++) {
    //Sets anode line i.e COLUMNS?
    for(row = 0; row < ROW_SIZE; line++) {
      type = (line == row) ? HIGH : LOW;
      transmitData(type);
    }

    //Set Red Row
    for(row = 0; row < ROW_SIZE; row++) {
      type = ((Screen[line][row] & 1) == 0) ? HIGH : LOW;
      transmitData(type);
    }

    SetBit(DATA_BUS, LATCH, HIGH);
    SetBit(DATA_BUS, LATCH, LOW);


  }

}

void Clear()
{
  unsigned char lineIndex;
  unsigned char rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = 0;
    }
  }
}

void ShowHappyFace()
{
  unsigned char lineIndex;
  unsigned char rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = HappyFace[lineIndex][rowIndex];
    }
  }
}
