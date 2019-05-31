#include "led_matrix.h"
#include "io.h"

void shiftRegInit() {
  PORTD = SetBit(SHIFT_REG_DATA_BUS, RESET, HIGH);
  PORTD = SetBit(SHIFT_REG_DATA_BUS, LATCH, LOW);
  PORTD = SetBit(SHIFT_REG_DATA_BUS, DATA, LOW);
  PORTD = SetBit(SHIFT_REG_DATA_BUS, DATA_OUTPUT_ENABLE, HIGH);
  PORTD = SetBit(SHIFT_REG_DATA_BUS, CLOCK, LOW);
}

void shiftData(uint8_t data) {;
  int i;
  for (i = 7; i >= 0 ; i--) {
  	// Sets SRCLR to 1 allowing data to be set
  	// Also clears SRCLK in preparation of sending data
  	PORTB = 0x80;
  	// set SER = next bit of data to be sent.
  	PORTB |= (((data >> i) & 0x01) << 4);
  	// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
  	PORTB |= 0x40;
  }
  // set RCLK = 1. Rising edge copies data from the “Shift” register to the
  //“Storage” register
  PORTB |= 0x20;
  // clears all lines in preparation of a new transmission
  PORTB = 0x00;
}

void displayData() {
  PORTD = SetBit(SHIFT_REG_DATA_BUS, LATCH, HIGH);
  PORTD = SetBit(SHIFT_REG_DATA_BUS, LATCH, LOW);
}

void clearShiftRegister() {
  PORTD = SetBit(SHIFT_REG_DATA_BUS, RESET, LOW);
  PORTD = SetBit(SHIFT_REG_DATA_BUS, LATCH, HIGH);
  PORTD = SetBit(SHIFT_REG_DATA_BUS, LATCH, LOW);
}

void sendDataToLED() {

}

void clearLED() {

}
