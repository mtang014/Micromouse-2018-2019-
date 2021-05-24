int motorEn = 7;
int MotorLogic1 = 6;
int MotorLogic2 = 5;
int motorSpeed = 127; //255 = 100%, 127 = 50%, 0 = 0%

void forward(){
  digitalWrite(motorEn, HIGH);
  analogWrite(MotorLogic1, motorSpeed);
  digitalWrite(MotorLogic2, LOW); 
  // delay(1000); smaller the number, the shorter the time the wheel, too big might not range.
}

void reverse(){
  digitalWrite(motorEn, HIGH);
  digitalWrite(MotorLogic1, LOW);
  analogWrite(MotorLogic2, motorSpeed);
  //delay(2000);
}
void setup() {
  // running the motor.
  pinMode(motorEn, OUTPUT);
  pinMode(MotorLogic1, OUTPUT);
  pinMode(MotorLogic2, OUTPUT);
  digitalWrite(motorEn, LOW);
}

void halt(){
  digitalWrite(motorEn, HIGH);
  digitalWrite(MotorLogic1, HIGH);
  digitalWrite(MotorLogic2, HIGH);
  
}
void loop() {
  // put your main code here, to run repeatedly:
  forward();
  delay(1000);  
  
  reverse();
  delay(1000);
  //halt();
}
