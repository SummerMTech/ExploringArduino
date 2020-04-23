 int tiempo=0;
 void setup() {
  for(int i=2; i<10; i++){
      pinMode(i,OUTPUT);
    }
}

void loop() {    
     for(int a=2;a<10;a++){
      digitalWrite(a-1,LOW);
      digitalWrite(a,HIGH);
      delay(tiempo);
    }  
   digitalWrite(9,LOW);    
}
