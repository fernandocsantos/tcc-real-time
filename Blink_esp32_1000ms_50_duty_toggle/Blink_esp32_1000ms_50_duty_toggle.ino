#include "soc/soc.h"
#define T 1000
#define pushButton_pin   23


void IRAM_ATTR toggleLED()
{
  static bool status = true;
  status?REG_WRITE(GPIO_OUT_W1TS_REG, BIT19):REG_WRITE(GPIO_OUT_W1TC_REG, BIT19);
  status = !status;
}

void toggleLed();

void setup() {
  // Enable GPIO2 gpio
  
  pinMode(pushButton_pin, INPUT_PULLUP);
  attachInterrupt(pushButton_pin, toggleLED, RISING);

  REG_WRITE(GPIO_ENABLE_REG, BIT19 | BIT21);
  
}

// the loop function runs over and over again forever
void loop() {
  toggleLed();
  delay(T/2);
}

void toggleLed(){
  static bool status = true;
  status?REG_WRITE(GPIO_OUT_W1TS_REG, BIT21):REG_WRITE(GPIO_OUT_W1TC_REG, BIT21);
  status = !status;
  
}



