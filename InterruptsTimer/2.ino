long ms = 0;

ISR(TIMER1_COMPA_vect){
  ms++;
}

long my_millis(){
  return ms;
}

void setup(){
  Serial.begin(9600);
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 16000;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

void loop(){
  Serial.print("Difference between my and default millis: ");
  Serial.println(int(millis() - my_millis()));
  Serial.println();  
}