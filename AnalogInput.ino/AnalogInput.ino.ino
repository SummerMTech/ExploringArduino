 int tiempo;
 void setup() {
  pinMode(13,INPUT);
  for(int i=2; i<10; i++){
      pinMode(i,OUTPUT);
    }
}

void loop() {
  iniciar:
  for(int i=2; i<10; i++){
      digitalWrite(i,0);
    }
  int button=digitalRead(13);
  if(button){
    delay(300);
   while(1) {
    for(int a=2;a<10;a++){
      tiempo=analogRead(A0);
      button=digitalRead(13);
      if(button){delay(200); goto iniciar;}
      digitalWrite(a-1,LOW);
      digitalWrite(a,HIGH);
      delay(tiempo);
    }  
   digitalWrite(9,LOW);    
  }
}
}
