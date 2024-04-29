#include "soc/soc.h"
#define T 1000

void toggleLed();

void setup() {
  // Enable GPIO2 gpio
  REG_WRITE(GPIO_ENABLE_REG, BIT2);
}

// the loop function runs over and over again forever
void loop() {
  toggleLed();
  delay(T/2);
}

void toggleLed(){
  static bool status = true;
  status?REG_WRITE(GPIO_OUT_W1TS_REG, BIT2):REG_WRITE(GPIO_OUT_W1TC_REG, BIT2);
  status = !status;
  
}

