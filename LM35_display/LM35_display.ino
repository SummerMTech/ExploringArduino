float temp;
int grados=9;
int decimal=10;
int unidad=11;
int decena=12;
//volatile array temper[];
byte numero[11][8] =
{ { 1, 1, 1, 1, 1, 1, 0, 0 }, // 0
  { 1, 1, 0, 0, 0, 0, 0, 0 }, // 1
  { 1, 0, 1, 1, 0, 1, 1, 0 }, // 2
  { 1, 1, 1, 0, 0, 1, 1, 0 }, // 3
  { 1, 1, 0, 0, 1, 0, 1, 0 }, // 4
  { 0, 1, 1, 0, 1, 1, 1, 0 }, // 5
  { 0, 1, 1, 1, 1, 1, 1, 0 }, // 6
  { 1, 1, 0, 0, 0, 1, 0, 0 }, // 7
  { 1, 1, 1, 1, 1, 1, 1, 0 }, // 8
  { 1, 1, 1, 0, 1, 1, 1, 0 }, // 9
  { 0, 0, 1, 1, 0, 0, 1, 0 }  // C
};


void setup(){
    for(int i=2; i<=13;i++){
        pinMode(i,OUTPUT);
    }
    Serial.begin(9600);
}
void loop(){
    float dat=analogRead(A0);
    float volt=dat*5/1024;
    temp=volt/0.01;
    temp= temp*10;
    int t=int(temp);
    int c=t%10;
    int aux1=t/10;
    int b=aux1%10;
    int a=aux1/10;
    Serial.println(temp);
    mostrar(10,a,b,c);
    
    //delay(1000);
}
void mostrar(int letra,int a, int b, int c){
  
 
  int temper[]={a,b,c,letra};
  
  for(int z=0; z<30;z++){
    for(int i=9; i<=12; i++){
        
        if (i==10){
            digitalWrite(13,1);
          }
        else{
            digitalWrite(13,0);
          }
          digitalWrite(i-1,0);
        digitalWrite(i,1);
        for (int d=0; d<=6;d++){
         digitalWrite(d+2,numero[temper[i-9]][d]); 
         //digitalWrite(d+2,numero[0][d]);
          
        }
        delay(5);
    }
    digitalWrite(12,0);
  }
    return;
}
