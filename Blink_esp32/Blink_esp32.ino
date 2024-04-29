#include "soc/soc.h"
#define T 1000


void setup() {
  // Enable GPIO2 gpio
  REG_WRITE(GPIO_ENABLE_REG, BIT2);
}

// the loop function runs over and over again forever
void loop() {
  REG_WRITE(GPIO_OUT_W1TS_REG, BIT2);//GPIO2 HIGH (set)
        delay(T/2);
  REG_WRITE(GPIO_OUT_W1TC_REG, BIT2);//GPIO2 LOW (clear)
        delay(T/2);
}
