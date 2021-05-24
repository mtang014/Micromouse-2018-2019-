int ir1 = 14;
int ir2 = 15;
int ir3 = 16;
int ir4 = 17;

 
void setup() {
  // put your setup code here, to run once:
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);
  pinMode(ir4,INPUT);

   
}

void loop() {
  // put your main code here, to run repeatedly:
  int IR_Read1 = analogRead(ir1);
  int IR_Read2 = analogRead(ir2);
  int IR_Read3 = analogRead(ir3);
  int IR_Read4 = analogRead(ir4);

  Serial.print("IR1: ");
  Serial.println(IR_Read1);
  Serial.print("IR2: ");
  Serial.println(IR_Read2);
  Serial.print("IR3: ");
  Serial.println(IR_Read3);
  Serial.print("IR4: ");
  Serial.println(IR_Read4);
}
