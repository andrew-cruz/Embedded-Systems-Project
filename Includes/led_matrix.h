#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__

  //Macros

  //For ghost coloring
  #define RED 0x01
  #define BLUE 0x02
  #define CYAN 0x05
  #define MAGENTA 0x06

  unsigned char PLAYER_POS[2] = {3 , 4}; //{i,j}
  unsigned char ENEMY_POS[4][3] = { {7,0,CYAN}, {7,7,MAGENTA}, {0,0,BLUE}, {0,7,RED} };
  unsigned char PELLET[2] = {2,3};
  unsigned char NUM_ENEMIES = 4;

  void ShiftData(uint8_t data);
  void ShiftDataEnable();
  void SendPlayerToLED();
  void SendEnemiesToLED();
  void SendPelletToLED();
  void LEDOff(unsigned int i);
  void LEDPaused(unsigned int i);
  void LEDGameOver(unsigned int i);
  void CheckCollisionPellet();
  void CheckCollisionEnemy();
  void LEDResetComponents();

  unsigned char RandomNum();
#endif
