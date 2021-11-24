#include <SoftwareSerial.h>

//contar el tiempo
  unsigned long tiempo1=0;
  unsigned long tiempo2=0;
  unsigned long tiemposegundos=0;
  int LeerSensor;
  float tensionSensor;
  float presion1;
  float presion2;
  float presion_sinatmosferica;
  float caudal;
  float FEV1;
  float suma_caudales;
  float LeerSensor2;
  float tensionSensor2;
  SoftwareSerial miBT(2,3); // RX, TX
  void setup (){
    Serial.begin (9600); //velocidad de datos (9600 baudios), Inicializamos  el puerto serie  
    tiempo1=millis ();
    miBT.begin(38400);
  }


void loop() {
  LeerSensor= analogRead(A1); //leer el voltaje del sensor en el pin A1
  LeerSensor2= analogRead(A2); //leer el voltaje del sensor en el pin A2
  tensionSensor=0.00478*LeerSensor; //convertir unidades a voltios (0.0049 aprox)
  tensionSensor2=0.00478*LeerSensor2;
  presion1=3.8371*tensionSensor; // Para un sensor diferencial de presión MPX2010, la relación que convierte el voltaje medido con la presión existente en kpa
  presion2=3.8371*tensionSensor2;
  presion_sinatmosferica=101.971*(presion1-presion2); //se resta la atmosferica;
  tiempo2= millis();
  
  if (presion_sinatmosferica>0){
    //convertir la presión en caudal
    caudal= presion_sinatmosferica*100/(8*11*1.8); //Calcular el caudal
    
    //contar tiempo
   
    if (tiempo2>(tiempo1+1000)){  //si ha pasado un segundo se atualiza el tiempo
      tiempo1=millis();//Actualiza al tiempo actual
      tiemposegundos=tiempo1/1000;
      //calcular el caudal prom
      if(tiemposegundos<60){
        suma_caudales=caudal+suma_caudales;
      }
      //convertir caudal V/minutos
      if(tiemposegundos==60){
        FEV1=suma_caudales;
        Serial.print("FEV1:");//paso para enviar la entrada del FEV1 por bluetooth
        Serial.print (FEV1);
        Serial.println ("L");
        miBT.println(FEV1;
      }
      Serial.print("FEM:"); //paso para enviar la entrada caudal por bluetooth
      Serial.print(caudal);
      Serial.println("L/minutos");
    }
  }
}
