#defide door_pin 10
bool unlocked = false
bool coin = get_coin();
bool push = get_push();
bool uodate_state(){
  bool coin = get_coin();
  bool push = get_push();
  if(coin){
    unlocked = true;
  }
  if(push){
    unlocked = false;
  }
}

void do_action(){
  if(unlocked){
    digitalWrite(door_pin,HIGH);
  }
  else{
    digitalWrite(door_pin,LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(door_pin,OUTPUT);
}

void loop() {
  update_state();
  do_action();
}