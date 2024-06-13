#define T 1000
#define SYSTICK 25

typedef struct{
  uint8_t gpio;
  int period;
  int phase;
  float duty_cicle;
  uint8_t state;
} led_t;

typedef struct{
  uint8_t gpio;
  uint8_t state;
} button_t;

led_t led_red = {2, 1000, 0, 0.5, 0};
led_t led_orange = {3, 750, -250, 0.6, 0};

button_t button_1 = {8, 1};

void toggle(led_t * led);
void led_setup(led_t * led);

void setup() {
  led_setup(&led_red);
  led_setup(&led_orange);
}

void loop() {
  
  // tarefa led vermelho
  if(led_red.phase >= 0 && led_red.phase < led_red.period * led_red.duty_cicle) digitalWrite(led_red.gpio, led_red.state = true);
  else if (led_red.phase >= led_red.period * led_red.duty_cicle) digitalWrite(led_red.gpio, led_red.state = false);

  led_red.phase += SYSTICK;
  led_red.phase %= led_red.period;


  // tarefa led laranja
  if(led_orange.phase >= 0 && led_orange.phase < led_orange.period * led_orange.duty_cicle) digitalWrite(led_orange.gpio, led_orange.state = true);
  else if (led_orange.phase >= led_orange.period * led_orange.duty_cicle) digitalWrite(led_orange.gpio, led_orange.state = false);

  led_orange.phase += SYSTICK;
  led_orange.phase %= led_orange.period;
  
  delay(SYSTICK);
}

void led_toggle(led_t * led){
  digitalWrite(led->gpio, (led->state = !led->state));
}

void led_setup(led_t * led){
  pinMode(led->gpio, OUTPUT); // configura o pino a ser usado pelo LED
  digitalWrite(led->gpio, led->state); //  aplica o estado inicial ao LED
}
