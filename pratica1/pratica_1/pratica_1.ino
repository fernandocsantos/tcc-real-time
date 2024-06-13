#define T 1000
void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(T/2);
  digitalWrite(2, LOW);
  delay(T/2);
}
