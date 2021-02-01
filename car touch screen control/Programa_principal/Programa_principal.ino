#include <Keypad.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>
#include <stdint.h>

SoftwareSerial portOne(50,51);// Rx,TX //bluetooth
//SoftwareSerial portTwo(52,53);// Rx,Tx //Biometrico
#define portTwo Serial3
Adafruit_Fingerprint biometrico=Adafruit_Fingerprint(&portTwo);
UTFTGLUE myGLCD(0x9481, A2, A1, A3, A4, A0);
//Definir pines para controlar la pantalla
#define XP 9   //Pin de control digital
#define YP A2  //Pin análogo de control
#define XM A3  //Pin análogo de control
#define YM 8   //Pin digital de control

// Definir los niveles de presión mínima y máxima
#define MINPRESSURE 10
#define MAXPRESSURE 1000

//Definir los valores para calibrar la pantalla táctil
#define X_STPT  75    // Valor de X inicial
#define X_ENPT  905    // Valor de X final
#define Y_STPT  145    // Valor de Y inicial
#define Y_ENPT  880    // Valor de Y final

TouchScreen myTouch = TouchScreen(XP, YP, XM, YM, 300);

//Definir códigos de los colores más utilizados
#define NEGRO   0x0000
#define AZUL    0x001F
#define ROJO     0xF800
#define VERDE   0x07E0
#define CIAN    0x07FF
#define MAGENTA 0xF81F
#define AMARILLO  0xFFE0
#define BLANCO   0xFFFF

//Define el ancho y largo de la pantalla en pixeles
int bluetooth;
int x_size = 480; int y_size = 320;
bool settscrsize(int w, int h) {
  if ((w <= 0) || (h <= 0)) return false;
  x_size = w; y_size = h;
  return true;
}
bool estado_bloqueo=1;
int x, y;  //Variables para obtener las coordenadas X y Y donde se presiona la pantalla
String oculto="";
String asterisco="*";
int  pass_ref[6]={1,2,3,4,5,6};
int pass[9]={};
int indice=0;
int const encender=39;
int const seguro=41;
int fingerprintID = 0;
const byte filas=4;
const byte columnas=4;
byte pinesF[filas]={23,25,27,29};
byte pinesC[4]={31,33,35,37};

byte teclas[filas][columnas]={
  {10,11,12,13},
  {14 ,9,8,7},
  {15,6,5,4},
  {16,3,2,1}  
   };

  Keypad teclado = Keypad(makeKeymap(teclas),pinesF, pinesC, filas,columnas);

void setup() {
  pinMode(encender,OUTPUT);
  pinMode(seguro,OUTPUT);
  myGLCD.InitLCD(1);  //Inicia en modo horizontal
  myGLCD.clrScr();
  digitalWrite(seguro,0);
  digitalWrite(encender,0);
  Serial.begin(9600);
  portOne.begin(9600);
  biometrico.begin(57600);
  if (biometrico.verifyPassword()) {
    Serial.println("biometrico_detectado");
  } else {
    Serial.println("biometrico_no_detectado :(");
    
  }
  myGLCD.setColor(NEGRO);
  myGLCD.fillRect(0,0,480,320);
  myGLCD.setTextColor(AMARILLO);
  myGLCD.setTextSize(3);
  myGLCD.print("Iniciando Programa...", 30, 130);
  delay(3000);
  myGLCD.setColor(NEGRO);
  myGLCD.fillRect(0,0,480,320);
  myGLCD.setTextColor(ROJO);
  myGLCD.setTextSize(4);
  myGLCD.print("Coche bloqueado...", 40, 110);
  myGLCD.print("Ingrese clave para", 30, 150);
  myGLCD.print("Desbloquear!", 55, 190);
  delay(4000);
  myGLCD.setColor(NEGRO);
  myGLCD.fillRect(0,0,480,320);
  
  iniciar();  
}

void loop() {
if(estado_bloqueo==1){
    int  tecla_presionada=teclado.getKey();
      if (tecla_presionada!=0){
        if (tecla_presionada!=10){
          Serial.println(tecla_presionada);
          pass[indice]=tecla_presionada;
          indice++;
          mostrar_clave();}
         if(tecla_presionada==10) enter();
        }
      portOne.listen();
      if (portOne.available()>0){
        int bluetooth=portOne.read();
        Serial.println(bluetooth);
        if(bluetooth==15){
            if(estado_bloqueo){
                portOne.write('b');
              }else{
                portOne.write('c');
                }
          }
        if (bluetooth>0&&bluetooth<10){     
          pass[indice]=bluetooth;
          indice++;
          mostrar_clave();
        }
        if((bluetooth)<=0){
            enter();
          }
        if((bluetooth)==10){
            for(int i=0; i<50;i++){
              fingerprintID = getFingerprintID();
              delay(10);
              if (fingerprintID==3){
                  digitalWrite(seguro,!digitalRead(seguro));
                  Serial.println("huella correcta");
                  delay(2000);
                  
                  break;
                }
              }
          }
        }
      
      TSPoint p;
      if (checktouch(&myTouch, &p))
      {
        x = p.x; y = p.y;
        if (x >= 30 && x <= 100 && y >= 177 && y <= 235 )
        {
          delay(300);
          enter(); //Muestra el boton Enter
        }
    
        if (x >= 110 && x <= 180 && y >= 180 && y <= 235 )
        {
           delay(300);
           pass[indice]=1;
           indice++;
           mostrar_clave();
        }
    
        if (x >= 190 && x <= 260 && y >= 180 && y <= 235 )
        {
           //Muestra el numero 2
           delay(300);
           pass[indice]=2;
           indice++;
           mostrar_clave();
        }
    
        if (x >= 270 && x <= 340 && y >= 180 && y <= 235 )
        {
           //Muestra el numero 3
           delay(300);
           pass[indice]=3;
           indice++;
           mostrar_clave();
        }
    
        if (x >= 350 && x <= 420 && y >= 180 && y <= 235 )
        {
           //Muestra el numero 4
           delay(300);
           pass[indice]=4;
           indice++;
           mostrar_clave();
        }
    
        if (x >= 30 && x <= 100 && y >= 245 && y <= 300 )
        {
           //Muestra el numero 5
           delay(300);
           pass[indice]=5;
           indice++;
           mostrar_clave();
        }
    
        if (x >= 110 && x <= 180 && y >= 245 && y <= 300 )
        {
           //Muestra el numero 6
           delay(300);
           pass[indice]=6;
           indice++;
           mostrar_clave();
        }
    
        if (x >= 190 && x <= 260 && y >= 245 && y <= 300 )
        {
          //Muestra el numero 7
          delay(300);
          pass[indice]=7;
           indice++;
           mostrar_clave();
        }
        if (x >= 270 && x <= 340 && y >= 245 && y <= 300 )
        {
           //Muestra el numero 8
           delay(300);
           pass[indice]=8;
           indice++;
           mostrar_clave();
        }
    
        if (x >= 350 && x <= 420 && y >= 245 && y <= 300 )
        {
           //Muestra el numero 9
           delay(300);
           pass[indice]=9;
           indice++;
           mostrar_clave();
        }
      }
  }else{
      //portOne.write('c');
      TSPoint p;
      if (checktouch(&myTouch, &p))
      {
          x = p.x; y = p.y;
        if (x >= 180 && x <= 360 && y >= 140 && y <= 180 )
        {//30, 177, 100, 235   180,140,300,180
          delay(100);
          estado_bloqueo=1;
          digitalWrite(encender,0);
           myGLCD.setColor(NEGRO);
           myGLCD.fillRect(0,0,480,320);
           myGLCD.setTextColor(ROJO);
          myGLCD.setTextSize(4);
          myGLCD.print("Vehiculo ha!!", 50, 90);
          myGLCD.print("Sido bloqueado..", 50, 155);
          delay(3000);
          myGLCD.setColor(NEGRO);
          myGLCD.fillRect(0,0,480,320);
          portOne.write('b');
          iniciar();
          }
        
        }
      portOne.listen();
      if (portOne.available()>0){
        bluetooth=portOne.read();
        Serial.println(bluetooth);
        if(bluetooth==15){
            if(estado_bloqueo){
                portOne.write('b');
              }else{
                portOne.write('c');
                }
          }
        if((bluetooth)==10){
            for(int i=0; i<50;i++){
              fingerprintID = getFingerprintID();
              delay(10);
              if (fingerprintID==2){
                  //digitalWrite(seguro,!digitalRead(seguro));
                  Serial.println("huella correcta");
                  digitalWrite(seguro,!digitalRead(seguro));
                  break;
               }
              }
          
              }
           if(bluetooth==14){ 
              delay(100);
            estado_bloqueo=1;
            digitalWrite(encender,0);
             myGLCD.setColor(NEGRO);
             myGLCD.fillRect(0,0,480,320);
             myGLCD.setTextColor(ROJO);
            myGLCD.setTextSize(4);
            myGLCD.print("Vehiculo ha!!", 50, 90);
            myGLCD.print("Sido bloqueado..", 50, 155);
            delay(3000);
            myGLCD.setColor(NEGRO);
            myGLCD.fillRect(0,0,480,320);
            portOne.write('b');
            iniciar();
            }
  }
 }
 
}
void enter(void){
    if (indice<7&&pass[0]==pass_ref[0]&&pass[1]==pass_ref[1]&&pass[2]==pass_ref[2]&&pass[3]==pass_ref[3]&&pass[4]==pass_ref[4]){
        indice=0;
        pass[9]={};
        oculto="";
        myGLCD.setColor(NEGRO);
        myGLCD.fillRect(0,0,480,320);
        myGLCD.setTextColor(VERDE);
        myGLCD.setTextSize(4);
        myGLCD.print("Clave Correcta!!", 30, 90);
        myGLCD.print("Encendiendo coche..", 10, 155);
        myGLCD.print(":)", 200, 220);
        portOne.write('c');
        digitalWrite(encender,1);
        delay(2000);
        delay(3000);
        myGLCD.setColor(NEGRO);
        myGLCD.fillRect(0,0,480,320);
        estado_bloqueo=0;
        desbloqueado();
      }else{
        indice=0;
        pass[9]={};
        oculto="";
        myGLCD.setColor(NEGRO);
        myGLCD.fillRect(0,0,480,320);
        myGLCD.setTextColor(ROJO);
        myGLCD.setTextSize(4);
        myGLCD.print("Clave incorrecta!", 30, 90);
        myGLCD.print("intenta otra vez..", 10, 155);
        myGLCD.print(":(", 200, 220);
        portOne.write('i');
        delay(5000);
        myGLCD.setColor(NEGRO);
        myGLCD.fillRect(0,0,480,320);
        iniciar();
        }
       return ;
 }

bool checktouch_core(TouchScreen *ts, TSPoint *pp, bool calflg) {
  // variables
  bool rlt = false;
  int rtry = 10;

  // Leer el sensor táctil de la pantalla
  delay(1);
  TSPoint p = ts->getPoint();
  if ((p.z < MINPRESSURE) || (p.z > MAXPRESSURE)) goto rsmpt;
  if (pp == 0) {
    rlt = true;
    goto rsmpt;
  }

  // Volver a leer el sensor táctil
  if (p.x < (X_STPT + 100)) {
    for (int i = 0 ; i < 2 ; i++) {
      delay(1);
      p = ts->getPoint();
      if (p.x > (X_STPT + 100)) break;
      if (p.x == 0) {
        if (rtry > 0) {
          rtry--;
          i = 0;
        }
      }
    }
  }
  if (p.x == 0) return false;

  // Obtener las coordenadas X y Y en donde se toca la pantalla
  if (pp != 0) {
#ifdef X_INVERSE
    p.x = 1100 - p.x;
#endif
    if (calflg) {
      pp->x = p.x; pp->y = p.y;
    } else {
      pp->x = ((long)(p.x - X_STPT) * (long)x_size) / (long)(X_ENPT - X_STPT);
      if (pp->x < 0) pp->x = 0;
      pp->y = ((long)(p.y - Y_STPT) * (long)y_size) / (long)(Y_ENPT - Y_STPT);
      if (pp->y < 0) pp->y = 0; if (pp->y >= y_size) pp->y = y_size - 1;
    }
    pp->z = p.z;
  }
  rlt = true;

  // Restaurar los pines para volver a ser utilizados para la función táctil
rsmpt:
  pinMode(XP, OUTPUT); pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT); pinMode(YM, OUTPUT);

  return rlt;
}

// Verificar el sensor touch para usarlo
bool checktouch(TouchScreen *ts, TSPoint *pp) {
  return checktouch_core(ts, pp, false);
}

void iniciar(void){
  //myGLCD.reset();
  //Rectangulos para los numeros 
  myGLCD.setColor(AZUL);
  myGLCD.drawRoundRect(30,30,440,80);
  myGLCD.setTextColor(AMARILLO);
  myGLCD.setTextSize(3);
  myGLCD.print("Ingrese Clave:", 130, 45);
  myGLCD.print("Ingrese Clave:", 130, 45);
  
  myGLCD.setColor(AMARILLO);
  myGLCD.drawRoundRect(30, 177, 100, 235);//0
  myGLCD.drawRoundRect(30, 245, 100, 300);//5
  myGLCD.drawRoundRect(110, 180, 180, 235);//1
  myGLCD.drawRoundRect(110, 245, 180, 300);//6
  myGLCD.drawRoundRect(190, 180, 260, 235);//2
  myGLCD.drawRoundRect(190, 245, 260, 300);//7
  myGLCD.drawRoundRect(270, 180, 340, 235);//3
  myGLCD.drawRoundRect(270, 245, 340, 300);//8
  myGLCD.drawRoundRect(350, 180, 420, 235);//4
  myGLCD.drawRoundRect(350, 245, 420, 300);//9

  //Números en los rectángulos 
  myGLCD.setTextColor(CIAN);
  myGLCD.setTextSize(2);
  myGLCD.print("Enter", 40, 197);
  myGLCD.setTextSize(2);
  myGLCD.print("1", 140, 200);
  myGLCD.print("2", 220, 200);
  myGLCD.print("3", 300, 200);
  myGLCD.print("4", 380, 200);
  myGLCD.print("5", 60, 265);
  myGLCD.print("6", 140, 265);
  myGLCD.print("7", 220, 265);
  myGLCD.print("8", 300, 265);
  myGLCD.print("9", 380, 265);
  }

void desbloqueado(void){
    myGLCD.setColor(VERDE); 
    myGLCD.fillRect(150,140,360,180);
    myGLCD.setColor(AMARILLO);
    myGLCD.drawRoundRect(150,140,360,180);
    myGLCD.setTextColor(NEGRO);
    myGLCD.setTextSize(3);
    myGLCD.print("BLOQUEAR", 170, 150);
  
  }

  void mostrar_clave(void){
       oculto=oculto+asterisco;//Muestra el numero 1
       myGLCD.setTextSize(2);
       myGLCD.print(oculto, 150, 111);
    }

 int getFingerprintID() {
  uint8_t p = biometrico.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = biometrico.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = biometrico.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  return biometrico.fingerID; 
}
