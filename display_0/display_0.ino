void setup() {
  for (int i=7;i<14;i++){pinMode(i,OUTPUT);}
}

void loop() {
  digitalWrite(13,1);
  digitalWrite(12,1);
  digitalWrite(11,1);
  digitalWrite(10,1);
  digitalWrite(9,1);
  digitalWrite(8,1);
  digitalWrite(7,0);
  delay(1000);
  digitalWrite(13,0);
  digitalWrite(12,1);
  digitalWrite(11,1);
  digitalWrite(10,0);
  digitalWrite(9,0);
  digitalWrite(8,0);
  digitalWrite(7,0);
  delay(1000);
  digitalWrite(13,1);
  digitalWrite(12,1);
  digitalWrite(11,0);
  digitalWrite(10,1);
  digitalWrite(9,1);
  digitalWrite(8,0);
  digitalWrite(7,1);
  delay(1000);
  digitalWrite(13,1);
  digitalWrite(12,1);
  digitalWrite(11,1);
  digitalWrite(10,1);
  digitalWrite(9,0);
  digitalWrite(8,0);
  digitalWrite(7,1);
  delay(1000); 
}
