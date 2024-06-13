#define T 1000

typedef struct{
  int gpio;
  bool state;
} led_t;

led_t red_led = {2, false};

void setup() {
  pinMode(red_led.gpio, OUTPUT);
}

void toggle();

void loop() {
  toggle();
  delay(T/2);
}

void toggle(){
  digitalWrite(red_led.gpio, (red_led.state = !red_led.state));
}
