#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth

void setup() {
  int LeerSensor;
  float tensionSensor;
  float presion;
  float caudal;
  float FEV1;
  float caudal_prom_60primerosseg;
  float suma_caudales;
  void setup (){
    Serial.begin (9600); //velocidad de datos (9600 baudios), Inicializamos  el puerto serie  
    tiempo1=millis ();
    BT.begin(9600);       // Inicializamos el puerto serie BT que hemos creado 
  }
  //contar el tiempo
  unsigned long tiempo1=0;
  unsigned long tiempo2=0;
  unsigned long tiemposegundos=0;
}

void loop() {
  LeerSensor= analogRead(A1); //leer el voltaje del sensor en el pin A1
  tensionSensor=0.00478*LeerSensor; //convertir unidades a voltios (0.0049 aprox)
  presion=3.8371*101.971*tensioSensor; // Para un sensor diferencial de presión MPX2010, la relación que convierte el voltaje medido con la presión existente en mmH2O
  
  if (presion>0){
    //convertir la presión en caudal
    caudal= presion*100000000/(8*11*1.8); //CALCULAR EL CAUDAL
    
    //contar tiempo
    tiempo2= millis();
    if (tiempo2>(tiempo1+1000)){  //si ha pasado un segundo se atualiza el tiempo
      tiempo1=millis();//Actualiza al tiempo actual
      tiempoSegundos=tiempo1/1000;
      //calcular el caudal prom
      if(tiempo1<60){
        suma_caudales=caudal+suma_caudales;
      }
    }
    //convertir caudal V/minutos
    if(tiempo1=60){
      caudal_prom_60primerosseg=suma_caudales/60;
      FEV1=caudal_prom_60primerosseg*60;
      //paso para enviar la entrada del FEV1 por bluetooth
    }
    //paso para enviar la entrada caudal por bluetooth
  }
}
