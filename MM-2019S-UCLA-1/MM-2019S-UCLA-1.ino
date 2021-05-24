int Debug_LED_13 = 13; // pin 13, debug LED

int LeftMotor_Enable_18 = 18; // pin D18/A6, motor left, enable
int LeftMotor_Forward_22 = 22; // pin 22, motor left forward, digital out
int LeftMotor_Reverse_23 = 23; // pin 23, motor left reverse, digital out

int RightMotor_Enable_19 = 19; // pin D19/A7, motor right, enable
int RightMotor_Forward_21 = 21; // pin 21, motor right forward, digital out
int RightMotor_Reverse_20 = 20; // pin 20, motor right reverse, digital out

//int LeftMotor_Aout_0 = 0; // pin D0, motor left, Aout
//int LeftMotor_Bout_1 = 1; // pin D1, motor left, Bout

int IR1_14 = 14;
int IR2_15 = 15;
int IR3_16 = 16;
int IR4_17 = 17;

int IR_Read1_14 = 0;
int IR_Read2_15 = 0;
int IR_Read3_16 = 0;
int IR_Read4_17 = 0;

void blinkLED() {
  digitalWrite(Debug_LED_13, HIGH);
  delay(500);
  digitalWrite(Debug_LED_13, LOW);
  delay(500);  
}

void forwardLeft(int i) {
  digitalWrite(LeftMotor_Enable_18, HIGH);
  analogWrite(LeftMotor_Forward_22, i);
  analogWrite(LeftMotor_Reverse_23, 0);
}

void forwardRight(int i) {
  digitalWrite(RightMotor_Enable_19, HIGH);
  analogWrite(RightMotor_Forward_21, 128);
  analogWrite(RightMotor_Reverse_20, 0);
}

void reverseLeft() {
  digitalWrite(LeftMotor_Enable_18, HIGH);
  analogWrite(LeftMotor_Forward_22, 0);
  analogWrite(LeftMotor_Reverse_23, 128);
}

void reverseRight() {
  digitalWrite(RightMotor_Enable_19, HIGH);
  analogWrite(RightMotor_Forward_21, 0);
  analogWrite(RightMotor_Reverse_20, 128);
}

void turnLeft() {
  digitalWrite(LeftMotor_Enable_18, HIGH);
  digitalWrite(RightMotor_Enable_19, HIGH);
  analogWrite(LeftMotor_Reverse_23, 128);
  analogWrite(RightMotor_Forward_21, 128);  
}

void turnRight() {
  digitalWrite(LeftMotor_Enable_18, HIGH);
  digitalWrite(RightMotor_Enable_19, HIGH);
  analogWrite(LeftMotor_Forward_22, 128);
  analogWrite(RightMotor_Reverse_20, 128);
}

void readIR() {
  IR_Read1_14 = analogRead(IR1_14);
  IR_Read2_15 = analogRead(IR2_15);
  IR_Read3_16 = analogRead(IR3_16);
  IR_Read4_17 = analogRead(IR4_17);
}

void setup() {
  // put your setup code here, to run once:
  // setup LED
  pinMode(Debug_LED_13, OUTPUT);

  // setup Left motor
  pinMode(LeftMotor_Enable_18, OUTPUT);
  digitalWrite(LeftMotor_Enable_18, LOW);
  
  pinMode(LeftMotor_Forward_23, OUTPUT);
  analogWrite(LeftMotor_Forward_23, 0);
  
  pinMode(LeftMotor_Reverse_22, OUTPUT);
  analogWrite(LeftMotor_Reverse_22, 0);

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
}

void loop() {
  // put your main code here, to run repeatedly:
  blinkLED();

  forwardLeft();
  forwardRight();
  //reverseLeft();
  //reverseRight();
  //turnLeft();
  //turnRight();
  readIR();
  Serial.print("IR1: ");
  Serial.println(IR_Read1_14);
  Serial.print("IR2: ");
  Serial.println(IR_Read2_15);
  Serial.print("IR3: ");
  Serial.println(IR_Read3_16);
  Serial.print("IR4: ");
  Serial.println(IR_Read4_17);
}
