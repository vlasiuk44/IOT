#define check_time 2000
#define led_pin 10
#define btn_pin 2
boolean button  = true;
boolean ledEnabled = false;      
boolean press_flag = false;
boolean long_press_flag = false;
unsigned long last_press = 0;  

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);
}
 
void loop() {
   button = digitalRead(btn_pin);
   
   //Вывод состояния кнопки
   //Serial.println(button);
   if (button == false  && press_flag == false && millis() - last_press > 20) {
     press_flag = !press_flag;
     last_press = millis(); 
   }
   if (button == false && press_flag == true && millis() - last_press > 1000) {
     long_press_flag = !long_press_flag;
     last_press = millis();
     for(int i=255;i>0;i--){
       analogWrite(led_pin,i);
       delay(1);
     }
     digitalWrite(led_pin, HIGH);
   }

   if (button == true && press_flag == true && long_press_flag == true) {
     press_flag = !press_flag;            
     long_press_flag = !long_press_flag;  
   }

   if (button == true && press_flag == true && long_press_flag == false) {
     press_flag = !press_flag;  
     ledEnabled = !ledEnabled;
     digitalWrite(led_pin, ledEnabled);
   }

}