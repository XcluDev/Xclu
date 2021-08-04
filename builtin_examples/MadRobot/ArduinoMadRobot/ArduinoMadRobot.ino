byte mot1a = 14;
byte mot1b = 15;
byte mot2a = 16;
byte mot2b = 17;
byte gnd_mot = 18;

byte rob_pwm[4] = {2, 3, 4, 5};
byte rob1[4] = {22, 28, 23, 27};
byte rob2[4] = {24, 26, 25, 29};
//4 - not conn

void motor(byte pa, byte pb, int v) {
  if (v == 0) {
    digitalWrite(pa, 0);
    digitalWrite(pb, 0);
  }
  if (v == 1) {
    digitalWrite(pa, 1);
    digitalWrite(pb, 0);
  }
  if (v == -1) {
    digitalWrite(pa, 0);
    digitalWrite(pb, 1);
  }
}

void motor1(int v) {
  motor(mot1a, mot1b, v);
}

void motor2(int v) {
  motor(mot2a, mot2b, v);
}
void motors(int v1, int v2) {
  motor1(v1);
  motor2(v2);
}

void rob(int i, int v) {
  motor(rob1[i], rob2[i], v);
}

int times[6] = {600, 900, 500, 400, 500, 400};

void robshed(int i, int v) {
  rob(i, v);
  if (v == 1) delay(times[i * 2]);
  if (v == -1) delay(times[i * 2 + 1]);
  rob(i, 0);
}

void robtime(int i, int v, int vtime) {
  rob(i, v);
  delay(vtime);
  rob(i, 0);
}
void robtime2(int i, int i2, int v, int v2, int vtime) {
  rob(i, v);
  rob(i2, v2);
  delay(abs(vtime));
  rob(i, 0);
  rob(i2, 0);
}


void setup() {
  Serial.begin(9600);
  Serial.println("MadRobot 03, keys wxads-motors, 123456-hand, 0 - pick up");


  pinMode(mot1a, OUTPUT);
  pinMode(mot1b, OUTPUT);
  pinMode(mot2a, OUTPUT);
  pinMode(mot2b, OUTPUT);
  pinMode(gnd_mot, OUTPUT);
  digitalWrite(gnd_mot, 0);

  for (byte i = 0; i < 4; i++) {
    pinMode(rob_pwm[i], OUTPUT);
    analogWrite(rob_pwm[i], 255 / 4); //12 to 3 V
    pinMode(rob1[i], OUTPUT);
    pinMode(rob2[i], OUTPUT);
  }
  delay(2000);

}

long long int time0_ = 0;    //time of last comand - disable motors if no command

void loop() {
  //rob(3,1);
  if (Serial.available() > 0) {
    time0_ = millis();

    while (Serial.available() > 0) {
      int key = Serial.read();
      if (key == 'w') motors(1, 1);
      if (key == 'x') motors(-1, -1);
      if (key == 'a') {
        motors(-1, 1);
        delay(300);
        motors(0, 0);
        delay(10);
      }
      if (key == 'd') { 
        motors(1, -1);
        delay(300);
        motors(0,0);
        delay(10);
      }
      
      if (key == 's') motors(0, 0);
      if (key == '1') robshed(0, -1);
      if (key == '2') robshed(0, 1);
      if (key == '3') robshed(1, -1);
      if (key == '4') robshed(1, 1);
      if (key == '5') robshed(2, -1);
      if (key == '6') robshed(2, 1);
      if (key == '0') {
        //pickup
        motors(0, 0); //stop
        delay(300);

        robtime(1, -1, 1000);//1500);
        //      robtime2(1,2,-2500);
        robshed(0, -1);
        delay(500);
        robtime(1, 1, 1700);

        //robtime2(1, 2, 1, 1, 3000);
        robtime(1, 1, 2500);
        robtime(2, 1, 2500);

        robshed(0, 1);
        delay(1000);

        //rotate
        if (random(10)<5) motors(-1, 1);
        else motors(1,-1);
        delay(5000);
        motors(0, 0);
        delay(10);
      
        
        robtime(2, -1, 2500);
        robtime(1, -1, 2300);

      }
    }  //while
  } //if available>0
  else {
    if (millis() > time0_ + 2000) {
      //Stop
      motors(0, 0);
      time0_ = millis();
      Serial.println("Stop");
    }

  }
  delay(10);

}
