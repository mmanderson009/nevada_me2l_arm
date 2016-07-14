void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
  pinMode(0, INPUT); //on/of button
  pinMode(2, INPUT); //wrist button
  pinMode(4, INPUT); //claw button
}

void loop() {
  // put your main code here, to run repeatedly:
   int onOFF = digitalRead(0);
   int wristRead = digitalRead(2);
   int gripperRead = digitalRead(4);

     Serial.print(onOFF);
  Serial.println();
       Serial.print(gripperRead);
  Serial.println();
       Serial.print(wristRead);
  Serial.println();
   
}
