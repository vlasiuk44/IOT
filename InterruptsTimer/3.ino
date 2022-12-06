#define led1_pin 11
#define led2_pin 12
#define led3_pin 13

bool led1_pos = false;
bool led2_pos = false;
bool led3_pos = false;

bool use2 = false;
bool use3 = false;

ISR(TIMER1_COMPA_vect){
  led1_pos = !led1_pos;
  led2_pos = use2?!led2_pos:false;
  led3_pos = use3?!led3_pos:false;
}

void setup(){
  Serial.begin(9600);
  cli();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 62500;
  TCCR1B = TCCR1B | (1 << WGM12);
  TCCR1B = TCCR1B | (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);

  pinMode(led1_pin, OUTPUT);
  pinMode(led2_pin, OUTPUT);
  pinMode(led3_pin, OUTPUT);

  sei();
}

void loop(){
  digitalWrite(led1_pin, led1_pos);
  digitalWrite(led2_pin, led2_pos);
  digitalWrite(led3_pin, led3_pos);
  
  if (Serial.available() >= 1){
    int pin = Serial.read();
    if (pin == '2'){
      use2 = !use2;
    }
    if (pin == '3'){
      use3 = !use3;
    }
  }
}