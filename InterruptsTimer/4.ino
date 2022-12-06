#define sensor_pin A0

bool need_to_read = false;
long time = 0;


ISR(TIMER1_COMPA_vect){
  need_to_read = true;
}

void setup(){
  Serial.begin(9600);
  cli();

  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 3900;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);

  pinMode(sensor_pin, INPUT);
  sei();
}

void loop(){
  if (need_to_read){
    int data = analogRead(A0);
    Serial.print("Time between check: ");
    Serial.println(millis() - time);
    Serial.print("Analog pin data: ");
    Serial.println(data);
    Serial.println();
    time = millis();
    need_to_read = false;
  }
}