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
  uint8_t mode;
  void (*isr)(void);
  uint8_t isr_mode;
  bool event;
} button_t;

led_t led_red = {4, 1000, 0, 0.5, false};
led_t led_orange = {5, 750, -250, 0.6, false};
led_t led_green = {6, 0, 0, 0, false};

void (*timer1_callback)(void * data) = NULL;
void * timer1_data = NULL;

void button1_isr(void);

button_t button_1 = {2, INPUT_PULLUP, &button1_isr, RISING, false};

void led_toggle(led_t * led);
void led_setup(led_t * led);

void button_setup(button_t * button);

void leds(void * data);
led_t * leds_data[] = {&led_red, &led_orange};

void timer1_setup(void (*callback)(void *), void * data)

void setup() {
  led_setup(&led_red);
  led_setup(&led_orange);
  led_setup(&led_green);
  button_setup(&button_1);
  timer1_setup(leds, leds_data);
}

void loop() {

}

void led_toggle(led_t * led){
  digitalWrite(led->gpio, (led->state = !led->state));
}

void led_setup(led_t * led){
  pinMode(led->gpio, OUTPUT); // configura o pino a ser usado pelo LED
  digitalWrite(led->gpio, led->state); //  aplica o estado inicial ao LED
}

void button_setup(button_t * button){
  pinMode(button->gpio, button->mode);
  attachInterrupt(digitalPinToInterrupt(button->gpio), button->isr, button->isr_mode);
}

void timer1_setup(void (*callback)(void *), void * data){
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1<<WGM12)|(1<<CS10)|(1<<CS11);
  OCR1A = 250;

  timer1_callback = callback;
  timer1_data = data;
}

void button1_isr(void){
  static long long int last_int_time = 0;
  if (millis() - last_int_time > button_1.debounce_time)
    led_toggle(&led_green);
  last_int_time = millis();
}

void leds(void * data){
  // tarefa led vermelho
  if(led_red.phase >= 0 && led_red.phase < led_red.period * led_red.duty_cicle) digitalWrite(led_red.gpio, led_red.state = true);
  else if (led_red.phase >= led_red.period * led_red.duty_cicle) digitalWrite(led_red.gpio, led_red.state = false);

  led_red.phase++;
  led_red.phase %= led_red.period;

  // tarefa led laranja
  if(led_orange.phase >= 0 && led_orange.phase < led_orange.period * led_orange.duty_cicle) digitalWrite(led_orange.gpio, led_orange.state = true);
  else if (led_orange.phase >= led_orange.period * led_orange.duty_cicle) digitalWrite(led_orange.gpio, led_orange.state = false);

  led_orange.phase %= led_orange.period;
}

ISR(TIMER1_COMPA_vect)
{
  // TIMSK1 &= ~(1<<OCIE1A);
  
  if (timer1_callback) timer1_callback(timer1_data);
  
}