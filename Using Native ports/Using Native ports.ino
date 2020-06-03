int a=B000001;
void setup() {
  // put your setup code here, to run once:
  DDRB=B111111;
  PORTB=a;
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
    PORTB=a<<1;
    a=PORTB;
    delay(1000);
    if(PINB==0b100000){a=B000001;PORTB=a;delay(1000);}
}
