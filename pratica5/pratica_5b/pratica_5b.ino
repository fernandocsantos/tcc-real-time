#define T 1000

typedef struct{
  int gpio;
  bool state;
} led_t;

led_t led_red = {2, false};
led_t led_orange = {3, false};

void toggle(led_t * led);
void setup_led(led_t * led);

void setup() {
  led_setup(&led_red);
  led_setup(&led_orange);
}

void loop() {
  led_toggle(&led_red);
  delay(T/5);
  led_toggle(&led_orange);
  delay(3*T/10);
  led_toggle(&led_red);
  delay(T/10);
  led_toggle(&led_orange);
  delay(2*T/5);
}

void led_toggle(led_t * led){
  digitalWrite(led->gpio, (led->state = !led->state));
}

void led_setup(led_t * led){
  pinMode(led->gpio, OUTPUT); // configura o pino a ser usado pelo LED
  digitalWrite(led->gpio, led->state); //  aplica o estado inicial ao LED
}
