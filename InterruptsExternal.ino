unsigned long int timerLED1;
unsigned long int timePreview = 0;
bool LEDOn = 0;
 
ISR (TIMER0_COMPA_vect) //функция, вызываемая таймером-счетчиком T0
{
    timerLED1++;
    if(timerLED1 - timePreview >= 1000)
    {                             
      timePreview = timerLED1;         
      digitalWrite(13, (LEDOn = !LEDOn));  
    }  
}
void setup() 
{
  pinMode(13, OUTPUT);
  TCCR0A |= (1 << WGM01);              //сброс при совпадении | регистр управления A
  OCR0A = 0xF9;                        //начало отсчета до переполнения (249) | регистр сравнения A (16 бит)
  TIMSK0 |= (1 << OCIE0A);             //разрешить прерывание при совпадении с регистром А | регистр маски прерываний для таймера/счетчика T0
  TCCR0B |= (1 << CS01) | (1 << CS00); //установить делитель частоты на 64 | регистр управления B
  sei();                               //разрешить прерывания
}
void loop() 
{
  
}