#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SaIoTDeviceLib.h>
//Falta: ajustar envios, pegar hora, definir o TYPE e testar
//Parametros da conexão

WiFiClient espClient;
#define timeout 5
#define SENSOR_PIN A0


//Variaveis sensor
long val,sensorMax=1025,sensorMin=0;
unsigned long int lastTime;
//Funções conexão
void calibracao();
void callback(char* topic, byte* payload, unsigned int length);
//Parametros do device
SaIoTDeviceLib deviceLuz("dLuz","zzzz555424","ricardodev@email.com");
String senha = "12345678910";
//Sensor
SaIoTSensor sLuminosidade("sLum","SensorLDR","Lumens","number");

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  lastTime = millis();
  Serial.begin(115200);
  deviceLuz.addSensor(sLuminosidade);
  deviceLuz.preSetCom(espClient,callback);
  deviceLuz.startDefault(senha);
  //calibracao();  
}

void loop() {
    if((((millis() - lastTime)/1000) >= timeout) ){
        val = analogRead(SENSOR_PIN);
        Serial.print("Valor sensor: ");
        val = map(val,1,sensorMax,0,100);
        //Serial.println(constrain(val,0,100));
        //Serial.println(val);
        sLuminosidade.sendData(val); //saveData
        Serial.println(analogRead(SENSOR_PIN)/1024.0);
        lastTime = millis();
    } 
    deviceLuz.handleLoop();
}

void calibracao(){
    int cont=0;
    while ((millis()-lastTime) < 3000) {
        //Serial.println('.');
        cont++;
        val = analogRead(SENSOR_PIN);
        // registre o máximo valor do sensor
        if (val > sensorMax) {
        sensorMax = val;
        }

        // registre o mínimo do sensor
        if (val < sensorMin) {
        sensorMin = val;
        }
  }
  Serial.println(cont);
}

void callback(char* topic, byte* payload, unsigned int length){
  String payloadS;
  Serial.print("Topic: ");
  Serial.println(topic);
  for (unsigned int i=0;i<length;i++) {
    payloadS += (char)payload[i];
  }
  if(strcmp(topic,deviceLuz.getSerial().c_str()) == 0){
    Serial.println("SerialLog: " + payloadS);
  }

}


