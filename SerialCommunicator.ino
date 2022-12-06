#define sensor_pin A0

void setup() {
  Serial.begin(9600);
}

uint32_t CRC(String str) {
  uint32_t h = 0;
  for (int i = 0; i < str.length(); i++) {
  	int highorder = h & 0xf8000000;
    h = h << 5;
    h = h ^ (highorder >> 27);
    h = h ^ str[i];
  }
  return h;
}

boolean thr = false;
int analog_pin = 0;

void loop() {
  
  String cmds[] = {
    "data",
    "thrd",
    "stop",
    "geta",
    "digw",
    "digr"
  };
  
  while (Serial.available() > 0) {
    Serial.println("Please wait.");
  	String cmd = Serial.readString();
    uint32_t hashed_cmd = CRC(String(cmd));
    
    if (hashed_cmd == CRC(cmds[0])) {
    	int val = analogRead(sensor_pin);
      	Serial.println(val);
      	thr = false;
    }
    else if (hashed_cmd == CRC(cmds[1])) {
      	thr = true;
    }
    else if (hashed_cmd == CRC(cmds[2])) {
    	thr = false;
    }
    else if (hashed_cmd == CRC(cmds[3])) {
      	Serial.println("Enter analog pin:");
      	analog_pin = Serial.parseInt();
      	int val = analogRead(analog_pin);
      	Serial.println(val);
      	thr = false;
    }
    else if (hashed_cmd == CRC(cmds[4])) {
		Serial.println("Enter 0 or 1:");
      	int val = Serial.parseInt();
      	for (int pin = 2; pin < 14; pin++) {
			digitalWrite(pin, val);
      	}
      	Serial.println("Done");
    }
    else if (hashed_cmd == CRC(cmds[5])) {
    	for (int pin = 2; pin < 14; pin++) {
			int val = digitalRead(pin);
          	Serial.print("Pin ");
          	Serial.print(pin);
          	Serial.print(": ");
          	Serial.println(val);
      	}
    }
    else {
    	Serial.println("No such command");
    }
    
  }
  if (thr) {	
  	int val = analogRead(analog_pin);
    Serial.println(val);
  }    
}