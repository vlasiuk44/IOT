#define forward 10
#define backward 11

void move(int frw, int bcw) {
  analogWrite(forward, frw);
  analogWrite(backward, bcw);
}

void move_to(char d, int max_speed) {
    switch (d) {
      case 'f':
        move(max_speed, 0);
        break;
      case 'b':
        move(0, max_speed);
        break;
      case 's':
        move(0, 0);
        break;
    }
}

void setup() {
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    move_to(c, 255);
  }
}
