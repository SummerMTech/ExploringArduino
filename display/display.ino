char catodo_comun[10][7]={
    {1,1,1,1,1,1,0}, // 0 
    {0,1,1,0,0,0,0}, // 1
    {1,1,0,1,1,0,1},  // 2
    {1,1,1,1,0,0,1},  // 3
    {0,1,1,0,0,1,1},  // 4
    {1,0,1,1,0,1,1},  // 5 
    {1,0,1,1,1,1,1},  // 6
    {1,1,1,0,0,0,0},  // 7
    {1,1,1,1,1,1,1},  // 8
    {1,1,1,1,0,1,1},   //9
    };
int cont=0;
void setup() {
  for (int i=7;i<14;i++){pinMode(i,OUTPUT);}  
}
void loop() {
  for(int i=0;i<8;i++){
      digitalWrite(13-i,catodo_comun[cont][i]);
   }
  delay(1000);
  cont++;
  if(cont==10) cont=0;
}
