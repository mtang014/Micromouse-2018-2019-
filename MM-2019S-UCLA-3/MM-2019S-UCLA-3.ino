int Debug_LED_13 = 13; // pin 13, debug LED

int LeftMotor_Enable_18 = 18; // pin D18/A6, motor left, enable
int LeftMotor_Forward_22 = 22; // pin 22, motor left forward, digital out
int LeftMotor_Reverse_23 = 23; // pin 23, motor left reverse, digital out

int LeftEncoder_A_3 = 3; // pin 3, PWM
int LeftEncoder_B_4 = 4; // pin 4, PWM
volatile int LeftCounter = 0;

int RightMotor_Enable_19 = 19; // pin D19/A7, motor right, enable
int RightMotor_Forward_21 = 21; // pin 21, motor right forward, digital out
int RightMotor_Reverse_20 = 20; // pin 20, motor right reverse, digital out

int RightEncoder_A_5 = 5; // pin 5, PWM
int RightEncoder_B_6 = 6; // pin 6, PWM
volatile int RightCounter = 0;

int IR1_14 = 14;
int IR2_15 = 15;
int IR3_16 = 16;
int IR4_17 = 17;

int IR_Read1_14 = 0;
int IR_Read2_15 = 0;
int IR_Read3_16 = 0;
int IR_Read4_17 = 0;

bool start = false;
bool ready = false;
bool emptyStart = false;
bool rightWall = false;
int timer = 0;
int rotateTimer = 0;

int irPower_12 = 12;


void blinkLED() {
  digitalWrite(Debug_LED_13, HIGH);
  delay(500);
  digitalWrite(Debug_LED_13, LOW);
  delay(500);  
}

void halt(int i){
  digitalWrite(LeftMotor_Enable_18, LOW);
  digitalWrite(RightMotor_Enable_19, LOW);
  analogWrite(LeftMotor_Forward_22, LOW);
  analogWrite(LeftMotor_Reverse_23, LOW);
  analogWrite(RightMotor_Forward_21, LOW);
  analogWrite(RightMotor_Reverse_20, LOW);
  delay(i);
  }

void forwardLeft(int i) {
  digitalWrite(LeftMotor_Enable_18, HIGH);
  analogWrite(LeftMotor_Forward_22, i);
  analogWrite(LeftMotor_Reverse_23, 0);
}

void forwardRight(int i) {
  digitalWrite(RightMotor_Enable_19, HIGH);
  analogWrite(RightMotor_Forward_21, i);
  analogWrite(RightMotor_Reverse_20, 0);
}

void reverseLeft(int i) {
  digitalWrite(LeftMotor_Enable_18, HIGH);
  analogWrite(LeftMotor_Forward_22, 0);
  analogWrite(LeftMotor_Reverse_23, i);
}

void reverseRight(int i) {
  digitalWrite(RightMotor_Enable_19, HIGH);
  analogWrite(RightMotor_Forward_21, 0);
  analogWrite(RightMotor_Reverse_20, i);
}

void rotateLeft(int i) {
  digitalWrite(LeftMotor_Enable_18, HIGH);
  digitalWrite(RightMotor_Enable_19, HIGH);
  analogWrite(LeftMotor_Reverse_23, i);
  analogWrite(RightMotor_Forward_21, i);  
}

void rotateRight(int i) {
  digitalWrite(LeftMotor_Enable_18, HIGH);
  digitalWrite(RightMotor_Enable_19, HIGH);
  analogWrite(LeftMotor_Forward_22, i);
  analogWrite(RightMotor_Reverse_20, i);
}

void turnRight(double i) {
  digitalWrite(LeftMotor_Enable_18, HIGH);
  digitalWrite(RightMotor_Enable_19, HIGH);
  if(LeftCounter * i < RightCounter) {
    analogWrite(LeftMotor_Forward_22, 127);
    analogWrite(RightMotor_Forward_21, 0);
    Serial.println("<");
  }
  else {
    analogWrite(LeftMotor_Forward_22, 127);
    analogWrite(RightMotor_Forward_21, 47);
    Serial.println(">=");
  }
}

void findRight() {
  if(emptyStart == true) {
    timer++;
  }
  if(timer >= 5) {
    emptyStart = false;
    timer = 0;
    LeftCounter = 0;
    RightCounter = 0;
  }
  Serial.print("timer: ");
  Serial.println(timer);
}

void incrementLeft() {
  LeftCounter++;
}

void incrementRight() {
  RightCounter++;
}

void interrupt(){
  attachInterrupt(digitalPinToInterrupt(LeftEncoder_A_3), incrementLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(LeftEncoder_B_4), incrementLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RightEncoder_A_5), incrementRight, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RightEncoder_B_6), incrementRight, CHANGE);
}

void readIR() {
  IR_Read1_14 = analogRead(IR1_14);
  IR_Read2_15 = analogRead(IR2_15);
  IR_Read3_16 = analogRead(IR3_16);
  IR_Read4_17 = analogRead(IR4_17);
}

void printIR() {
  Serial.print("IR1: ");
  Serial.println(IR_Read1_14);
  Serial.print("IR2: ");
  Serial.println(IR_Read2_15);
  Serial.print("IR3: ");
  Serial.println(IR_Read3_16);
  Serial.print("IR4: ");
  Serial.println(IR_Read4_17);
}

void emptyWall(){
   if(IR_Read1_14 < 250 && RightCounter > 0){ //Empty Wall AND moving!
    emptyStart = true;
    LeftCounter = 0;
    RightCounter = 0;
  }
  else{
    emptyStart = false;
  }
}
void standby() {
  if(IR_Read1_14 > 290) { //IR_Read2_15 > 127 && IR_Read3_16 > 127) {
    ready = true;
  }
  if(ready == true && IR_Read1_14 < 290) { //IR_Read2_15 < 127 && IR_Read3_16 < 127) {
    start = true;
  }
}

void setup() {
  // put your setup code here, to run once:
  // setup LED
  pinMode(irPower_12,OUTPUT);
  pinMode(Debug_LED_13, OUTPUT);

  // setup Left motor
  pinMode(LeftMotor_Enable_18, OUTPUT);
  digitalWrite(LeftMotor_Enable_18, LOW);
  
  pinMode(LeftMotor_Forward_22, OUTPUT);
  analogWrite(LeftMotor_Forward_22, 0);
  
  pinMode(LeftMotor_Reverse_23, OUTPUT);
  analogWrite(LeftMotor_Reverse_23, 0);

  // setup Right motor
  pinMode(RightMotor_Enable_19, OUTPUT);
  digitalWrite(RightMotor_Enable_19, LOW);
  
  pinMode(RightMotor_Forward_21, OUTPUT);
  analogWrite(RightMotor_Forward_21, 0);
  
  pinMode(RightMotor_Reverse_20, OUTPUT);
  analogWrite(RightMotor_Reverse_20, 0);

  pinMode(IR1_14, INPUT);
  pinMode(IR2_15, INPUT);
  pinMode(IR3_16, INPUT);
  pinMode(IR4_17, INPUT);
  Serial.begin(9600);
  IR_Read1_14 = 0;
  IR_Read2_15 = 0;
  IR_Read3_16 = 0;
  IR_Read4_17 = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  blinkLED();
  readIR();
  printIR();
  Serial.print("LeftCounter: ");
  Serial.println(LeftCounter);
  Serial.print("RightCOunter: ");
  Serial.println(RightCounter);
  ///*
  if(start == true) {
    rotateTimer++;
    if(rotateTimer >= 20){
      rotateRight(127);
      if(rotateTimer >= 25){
        rotateTimer = 0;
      }
    }
    forwardLeft(127);
    forwardRight(127);
    //halt(); //Works!
    if(emptyStart == false) {
      emptyWall();
    }
    else if(emptyStart == true){
      /*
      halt(500);
      turnRight(50);
      delay(500);
      */
      Serial.println("emptyStart == true");
      turnRight(2.7);
      findRight();
    }
    else{
      
    }
    //reverseLeft(127);
    //reverseRight(127);
    //turnLeft(127);
    //turnRight(127);
    interrupt();
  }

  else {
    standby();
  }
  //*/
}
