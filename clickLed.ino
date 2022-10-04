#define btn_pin 4
#define check_time 20
#define check_time2 2000
#define led_pin 3
long preValue=0;
bool status = 0;
void setup() {
  Serial.begin(9600);
  pinMode(btn_pin, INPUT);
}

void loop() {
  //Serial.println(millis()-preValue<check_time2+millis());
  int val = digitalRead(btn_pin);
  if(val==0){
    
    
     if((millis()-preValue>check_time)&&(millis()-preValue<check_time2)){
         status = !status;
     }
     if(millis()-preValue<check_time2){
      Serial.println(millis()-preValue);
        for(int i=0;i<255;i++){
          analogWrite(led_pin,i);
        delay(5);
     }
      for(int i=255;i>0;i--){
        analogWrite(led_pin,i);
        delay(5);
      }
     }
  preValue=millis(); 
  }

  if (status) {
    digitalWrite(led_pin, HIGH);
  }
  else {
    digitalWrite(led_pin,LOW);
  }
  //Serial.println(status);
}
