 void setup() {
  pinMode(13,INPUT);
  for(int i=2; i<10; i++){
      pinMode(i,OUTPUT);
    }
}

void loop() {
  boolean pulsador=digitalRead(13);
  if(pulsador){      
          for(int a=2;a<10;a++){
              digitalWrite(a-1,LOW);
              digitalWrite(a,HIGH);
              delay(100);
          }  
           digitalWrite(9,LOW);    
    }
}
