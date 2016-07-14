int ANA[2];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ANA[1] = 2;
  ANA[0] = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  int x,y;
  x = analogRead(ANA[0]);
  y = analogRead(ANA[1]);

  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.println(y);

}
