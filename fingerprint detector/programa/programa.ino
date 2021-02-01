#include <DFPlayer_Mini_Mp3.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>
SoftwareSerial miSerial(2,3);
Adafruit_Fingerprint dedo=Adafruit_Fingerprint(&miSerial);
LiquidCrystal lcd(7,8,9,10,11,12);
int fingerprintID = 0;
int const boton=5;
int const contacto_1=A0;
int const contacto_2=A1;
int const contacto_3=A2;
int const interruptor=A3;
int const sensor_vib=4;
int contacto=0;
int auto_estado=0;
void setup() { 
  pinMode(boton,INPUT);
  pinMode(sensor_vib,INPUT);
  pinMode(interruptor,INPUT);
  pinMode(contacto_1,OUTPUT);
  pinMode(contacto_2,OUTPUT);
  pinMode(contacto_3,OUTPUT);

  pinMode(13,OUTPUT);
  Serial.begin(9600);
  mp3_set_serial(Serial);  //configuramos la comunicación serial Arduino-mp3
  mp3_set_volume(25); 
  dedo.begin(57600);
  lcd.begin(16,2);
  digitalWrite(contacto_1,1);
  digitalWrite(contacto_2,1);
  digitalWrite(contacto_3,1);
  digitalWrite(13,1);
  verificar:
  if (dedo.verifyPassword()) {
    lcd.print("Biometrico");
    lcd.setCursor(0,1);
    lcd.print("detectado!  :)");
    Serial.println("biometrico_detectado");
  } else {
    lcd.print("Biometrico no");
    lcd.setCursor(0,1);
    lcd.print("detectado :(");
    Serial.println("biometrico_no_detectado :(");
    delay(50);
    lcd.clear();
    goto verificar;
  }
  delay(3000);
  lcd.clear();
  delay(1000);
  
}

void loop() {
  if(digitalRead(interruptor)){
      if(digitalRead(sensor_vib)){
          digitalWrite(13,0);
        }
    }else{
        digitalWrite(13,1);
      }
  if(contacto==0){ 
    lcd.println("presione boton");
    lcd.setCursor(0,1);
    lcd.print("para contacto 1");
    Serial.println("presione boton para contacto 1");
    digitalWrite(contacto_1,1);
    digitalWrite(contacto_2,1);
    digitalWrite(contacto_3,1);
   }
  if(contacto==1){ 
    
    lcd.print("presione boton");
    lcd.setCursor(0,1);
    lcd.print("para contacto 2");
    Serial.println("presione boton para contacto 2");
    }
  if(contacto==2){
     
      lcd.print("COLOQUE el dedo");
      lcd.setCursor(0,1);
      lcd.print("para analisis");
      Serial.println("Coloque dedo");
      int contador=0;
      for(int i=0; i<100;i++){
        //contacto=0;
        Serial.println(contador);
        fingerprintID = getFingerprintID();
        contador++;
        delay(30);
        if (fingerprintID==1){
          lcd.print("Huella correcta!");
          Serial.println("huella correcta");
          delay(2000);
          lcd.clear();
          lcd.print("Bienvenido señor");
          lcd.setCursor(0,1);
          lcd.print("Daniel...   :)");
          delay(1000);
          digitalWrite(contacto_3,0);
          delay(3000);
          digitalWrite(contacto_3,1);
          lcd.clear();
          auto_estado=1;
          break;
        }
        
      }
      lcd.clear();
      if(auto_estado==1){
            lcd.print("Auto Activo!");
            Serial.println("auto activo");
            while(1){
                lcd.print("Auto Activo!");
                delay(100); lcd.clear();
              }
          }else{
            lcd.print("NO detectado..");
            lcd.setCursor(0,1);
            lcd.print("intente otra vez");
            Serial.println("Error intente nuevamente!");
            delay(5000);
            lcd.clear();
            
            }
      
      }
  if(digitalRead(boton)){
      contacto++;
      if(contacto==3) contacto=2;
      if(contacto==1){
        delay(1000);
        digitalWrite(contacto_1,0);
        delay(1000);
        //digitalWrite(contacto_1,1);
      }
      if(contacto==2){
        delay(1000);
        digitalWrite(contacto_2,0);
        delay(1000);
        //digitalWrite(contacto_2,1);
      }
     }
    delay(50);
    lcd.clear();
  

}

int getFingerprintID() {
  uint8_t p = dedo.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = dedo.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = dedo.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  //Serial.print("Found ID #"); Serial.print(dedo.fingerID); 
  //Serial.print(" with confidence of "); Serial.println(dedo.confidence);
  return dedo.fingerID; 
}
