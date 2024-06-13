#define T 1000

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
  uint8_t last_state;
} button_t;

led_t led_red = {2, 1000, 0, 0.5, false};
led_t led_orange = {3, 750, -250, 0.6, false};
led_t led_green = {4, 0, 0, 0, false};

button_t button_1 = {8, 1, 1};

void led_toggle(led_t * led);
void led_setup(led_t * led);

void button_setup(button_t * button);

void setup() {
  led_setup(&led_red);
  led_setup(&led_orange);
  led_setup(&led_green);
  button_setup(&button_1);
}

void loop() {
  // garante que a contagem de tempo inicia em 0 para o loop
  static unsigned long start_time = millis();
  unsigned long long SYSTICK = millis() - start_time;

  // tarefa led vermelho
  if(led_red.phase >= 0 && led_red.phase < led_red.period * led_red.duty_cicle) digitalWrite(led_red.gpio, led_red.state = true);
  else if (led_red.phase >= led_red.period * led_red.duty_cicle) digitalWrite(led_red.gpio, led_red.state = false);

  led_red.phase = 0xFFFF & (SYSTICK % led_red.period);

  // tarefa led laranja
  if(led_orange.phase >= 0 && led_orange.phase < led_orange.period * led_orange.duty_cicle) digitalWrite(led_orange.gpio, led_orange.state = true);
  else if (led_orange.phase >= led_orange.period * led_orange.duty_cicle) digitalWrite(led_orange.gpio, led_orange.state = false);

  led_orange.phase = 0xFFFF & (SYSTICK % led_orange.period);

  //tarefa led verde
  
  button_1.state = digitalRead(button_1.gpio);
  if(button_1.state == 0 && button_1.last_state == 1) led_toggle(&led_green);
  button_1.last_state = button_1.state;
 }

void led_toggle(led_t * led){
  digitalWrite(led->gpio, (led->state = !led->state));
}

void led_setup(led_t * led){
  pinMode(led->gpio, OUTPUT); // configura o pino a ser usado pelo LED
  digitalWrite(led->gpio, led->state); //  aplica o estado inicial ao LED
}

void button_setup(button_t * button){
  pinMode(button->gpio, INPUT_PULLUP);
}