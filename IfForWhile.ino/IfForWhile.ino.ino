 void setup() {
  pinMode(13,INPUT);
  for(int i=3; i<9; i++){
      pinMode(i,OUTPUT);
    }
}

void loop() {
  boolean pulsador=digitalRead(13);
  if(pulsador){
      while(pulsador==true){
          for(int a=3;a<9;a++){
              digitalWrite(a-1,LOW);
              digitalWrite(a,HIGH);
              delay(100);
          }  
           digitalWrite(8,LOW);
      }       
    }
}
