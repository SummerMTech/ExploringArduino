int const encender=2;
int const puertas=3;
int const vent1_a=11;
int const vent1_b=10;
int const vent2_a=9;
int const vent2_b=8;
int const vent3_a=7;
int const vent3_b=6;
int const vent4_a=5;
int const vent4_b=4;
int const sirena=12;
int const sirena_real=A0;
int const sirena_sensor=A2;
bool sensado_vibracion=0;
int estado_vent=0;
char dato;
void setup() {
  Serial.begin(9600);
  for (int i=2;i<12;i++){
    pinMode(i,OUTPUT);
    }
   pinMode(sirena,OUTPUT);
   pinMode(sirena_real,OUTPUT);
   pinMode(sirena_sensor,INPUT);
   digitalWrite(encender,1);
   digitalWrite(puertas,1);
   digitalWrite(vent1_a,1);
   digitalWrite(vent1_b,1);
   digitalWrite(vent2_a,1);
   digitalWrite(vent2_b,1);
   digitalWrite(vent3_a,1);
   digitalWrite(vent3_b,1);
   digitalWrite(vent4_a,1);
   digitalWrite(vent4_b,1);
   digitalWrite(sirena,1);
   digitalWrite(sirena_real,1);
   
}

void loop() {
   if (Serial.available()){
      dato=Serial.read();
      switch (dato){
        case '1':
          delay(100);
          digitalWrite(vent1_a,!digitalRead(vent1_a));
          digitalWrite(vent1_b,1);
          
          
        break;
        case '2':
          delay(100);
          digitalWrite(vent1_a,1);
          digitalWrite(vent1_b,!digitalRead(vent1_b));
          
         
        break;
        case '3':
          delay(100);
          digitalWrite(vent2_a,!digitalRead(vent2_a));
          digitalWrite(vent2_b,1);
         
        break;
        case '4':
          delay(100);
          digitalWrite(vent2_a,1);
          digitalWrite(vent2_b,!digitalRead(vent2_b));
          
    
        break;
        case '5':
          delay(100);
          digitalWrite(vent3_a,!digitalRead(vent3_a));
          digitalWrite(vent3_b,1);
          
        break;
        case '6':
          delay(100);
          digitalWrite(vent3_a,1);
          digitalWrite(vent3_b,!digitalRead(vent3_b));
         
        break;
        case '7':
        delay(100);
          digitalWrite(vent4_a,!digitalRead(vent4_a));
          digitalWrite(vent4_b,1);
          
        break;
        case '8':
          delay(100);
          digitalWrite(vent4_a,1);
          digitalWrite(vent4_b,!digitalRead(vent4_b));
          
        break;
        case 'p':
          digitalWrite(puertas,!estado_vent);
          digitalWrite(sirena,estado_vent);
          delay(100);
          digitalWrite(puertas,1);
          digitalWrite(sirena,1);
          estado_vent=!estado_vent;
        break;
        case 'e':
          digitalWrite(encender,0);
          delay(2000);
          digitalWrite(encender,1);
        break;
        case 's':
          delay(500);
          sensado_vibracion=!sensado_vibracion;
        break;
        }
    }
    delay(50);
    if(sensado_vibracion){
        if(digitalRead(sirena_sensor)==0){
            digitalWrite(sirena_real,0);
          }
         
      }else{
            digitalWrite(sirena_real,1);
          }
}
