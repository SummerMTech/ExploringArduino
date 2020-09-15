#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
byte espera_1[] = {
  B00001,
  B00010,
  B00010,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000
};
byte espera_2[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000
};
byte espera_3[] = {
  B10000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001
};
int aux=0;
byte espera_4[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};
void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  lcd.createChar(0, espera_1);
  lcd.createChar(1, espera_2);
  lcd.createChar(2, espera_3);
  lcd.createChar(3, espera_4);
  lcd.cursor();
  lcd.blink();
  for(int j=0;j<4;j++){  
    for(int i=0;i<4;i++){
        lcd.setCursor(4,0);
        lcd.print("WELCOME!!");
        lcd.setCursor(2,1);
        lcd.print("LOADING.....");
        lcd.write(i);
        delay(500);
        lcd.clear();
      }
  }
  delay(5000);
  lcd.clear();
  
}

void loop() {
  if(Serial.available()){
   delay(10);
   while(Serial.available()>0){ 
    aux++;
    if(aux==16){lcd.setCursor(0,1);}
    if(aux==32){lcd.clear();lcd.setCursor(0,0);aux=0;}
    lcd.write(Serial.read());
    }  
  }
}
