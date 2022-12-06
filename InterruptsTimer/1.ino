#define led_pin 7

bool led_pos = false;
bool old_pos = false;

ISR(TIMER2_OVF_vect){
  led_pos = !led_pos;
}

void setup(){
  Serial.begin(9600);
  cli();
  TCCR2A = 0;
  TCCR2B = 0;
  TCCR2B |= (1 << CS10);
  TCCR2B |= (1 << CS12);
  TIMSK2 = (1 << TOIE1);
  pinMode(led_pin, OUTPUT);
  sei();
}

void loop(){
  digitalWrite(led_pin, led_pos);
  if (led_pos != old_pos){
    old_pos = led_pos;
    Serial.println(millis());
  }
}