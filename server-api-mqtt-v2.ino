#include <PubSubClient.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
#include "DHT.h"
#include <ThingSpeak.h>
#include "FirebaseESP8266.h"
#define DHTTYPE DHT11 // DHT 11


const char *mqtt_server = "ioticos.org";
const int mqtt_port = 1883;
const char *mqtt_user = "7smjvxoNrqpsizT";
const char *mqtt_pass = "L8deH0Ef7BzQQVe";
const char *root_topic_subscribe = "t3GQncnL0ObphtZ/input";
const char *root_topic_publish_general = "t3GQncnL0ObphtZ/general";
const char *root_topic_subscribe_temperatura = "t3GQncnL0ObphtZ/modificar-temperatura";
const char *root_topic_publish_temperatura = "t3GQncnL0ObphtZ/temperatura";
const char *root_topic_subscribe_humedad = "t3GQncnL0ObphtZ/modificar-humedad";
const char *root_topic_publish_humedad = "t3GQncnL0ObphtZ/humedad";
const char *root_topic_subscribe_puerta = "t3GQncnL0ObphtZ/puerta";


//**************************************
//*********** WIFICONFIG ***************
//**************************************
const char* ssid = "Varelas grajales";
const char* password = "F4m1l14V4r3l4";
const char* host = "maker.ifttt.com";

//*************************************
//************CONFIG GRAPH*************
//*************************************
unsigned long channelID = 1406939;
const char* WriteAPIKey = "SCDCXYFGDYS3WJVV";

//*************************************
//************CONFIG FIREBASE**********
//*************************************
#define FIREBASE_HOST "iott-fdf67-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "rGIvKbezquXi4SZSSD1veFzR4aA8DCtQj7ikRrAc"

//*************************************
//************CONFIG EMAIL*************
//*************************************
String apiKey = "cIHL21wmXS7-MsB2fXc-t-"; //"YOUR_IFTTT_API_KEY";
String eventName = "send_email";
String value1, value2, value3;
String request;

//**************************************
//*********** GLOBALES   ***************
//**************************************
WiFiClient espClient;
PubSubClient client(espClient);
const int DHTPin = 5;
const int cooler = 4;
const int sv = 0;
const int PINR = 14;
const int PINB = 12;
const int SMovimiento = 2;
DHT dht(DHTPin, DHTTYPE);
Servo servo1;
FirebaseData firebaseData;

//**************************************
//*********** VARIABLES  ***************
//**************************************
float t, h = 0;
float lastT, lastH = 0;
float tempLimit = 30.0;
bool stateServo = false;
String strpublicar, strtemp, strhum;
char msg[85], msgtemp[30], msghum[30];
String top;
String mens = "";
int EstadoMovimiento;
String path = "/AmbienteBodega";

//timers
const unsigned long publeshTemp = 25000;
unsigned long lastPubleshTemp;

const unsigned long publeshHum = 25000;
unsigned long lastPubleshHum;


void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void setup_wifi();
void printResult(FirebaseData &data);
void CausaError(void);
void InforSetTemperatura(void);
void InforGetTemperatura(void);
void InforSetHumedad(void);
void InforGetHumedad(void);*/

bool event = false;

void myTestCall() {
  event = true;
}

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  ThingSpeak.begin(espClient);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  
  //SENSORES
  pinMode(DHTPin, INPUT);
  pinMode(cooler, OUTPUT);
  pinMode(PINR, OUTPUT);
  pinMode(PINB, OUTPUT);
  pinMode(SMovimiento, INPUT);
  servo1.attach(0);
  servo1.write(0);
  dht.begin();
  myTestCall();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  if (client.connected()) {
    lastT = dht.readTemperature();
    h = dht.readHumidity();
    detectarMovimeinto();
    if (!isnan(lastT)) {
      t = lastT;
    }
    ThingSpeak.setField(1,t);
    ThingSpeak.setField(2,h);
    
    strpublicar = "Temperatura: " + String(t) + "°C  " + "Humedad: " + String(h) + "%" + "Temperatura limite: " + tempLimit + " Estado de puerta: " + stateServo;
    strpublicar.toCharArray(msg, 85);
    client.publish(root_topic_publish_general, msg);
    delay(200);

    unsigned long topLoop1 = millis();
    if (topLoop1 - lastPubleshTemp >= publeshTemp) {
      lastPubleshTemp = topLoop1;
      strtemp = "Temperatura: " + String(t) + "°C";
      strtemp.toCharArray(msgtemp, 30);
      client.publish(root_topic_publish_temperatura, msgtemp);
      delay(200);
    }
    unsigned long topLoop2 = millis();
    if (topLoop2 - lastPubleshHum >= publeshHum) {
      lastPubleshHum = topLoop2;
      strhum = "Humedad: " + String(h) + "%";
      strhum.toCharArray(msghum, 30);
      client.publish(root_topic_publish_humedad, msghum);
      delay(200);
    }
    delay(3000);
  }
  client.loop();
 //refri();
  leerSubscripcion();
  ThingSpeak.writeFields(channelID,WriteAPIKey);
  Serial.print("Datos enviados");
  dataBase();
  delay(30000);
  
}

void setup_wifi() {
  delay(10);
  // Nos conectamos a nuestra red Wifi
  Serial.println();
  Serial.print("Conectando a ssid: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado a red WiFi!");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}



//*****************************
//***    CONEXION MQTT      ***
//*****************************

void reconnect() {

  while (!client.connected()) {
    Serial.print("Intentando conexión Mqtt...");
    // Creamos un cliente ID
    String clientId = "IOTICOS_H_W_";
    clientId += String(random(0xffff), HEX);
    // Intentamos conectar
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.println("Conectado!");
      // Nos suscribimos
      if (client.subscribe(root_topic_subscribe)) {
        Serial.println("Suscripcion raíz");
      } else {
        Serial.println("falló Suscripción raíz");
      }
      if (client.subscribe(root_topic_subscribe_temperatura)) {
        Serial.println("Suscripcion temperatura");
      } else {
        Serial.println("falló Suscripción temperatura");
      }
      if (client.subscribe(root_topic_subscribe_humedad)) {
        Serial.println("Suscripcion humedad");
      } else {
        Serial.println("falló Suscripción humedad");
      }
      if (client.subscribe(root_topic_subscribe_puerta)) {
        Serial.println("Suscripcion puerta");
      } else {
        Serial.println("falló Suscripción puerta");
      }

    } else {
      Serial.print("falló :( con error -> ");
      Serial.print(client.state());
      Serial.println(" Intentamos de nuevo en 5 segundos");
      delay(5000);
    }
  }
}


//*****************************
//***       CALLBACK        ***
//*****************************

void callback(char* topic, byte* payload, unsigned int length) {
  String incoming = "";
  Serial.print("Mensaje recibido desde -> ");
  Serial.print(topic);
  Serial.println("");
  for (int i = 0; i < length; i++) {
    incoming += (char)payload[i];
  }
  incoming.trim();
  String readTopic = topic;
  top = readTopic.substring(16, 40);
  mens = incoming;
  Serial.println("Mensaje -> " + incoming);

}

void refri(float temp, float limite) {
  if (temp >= limite) {
    //Serial.println("Temperatura Excedida");
    digitalWrite(cooler, HIGH);
    value3 = "Encendido";
  }
  else {
    //Serial.println("Temperatura Normal");
    digitalWrite(cooler, LOW);
    value3 = "Encendido";
  }
}

void leerSubscripcion() {
  value1 = top;
  value2 = mens;
  
  if (top == "puerta") {
    Serial.println(mens);
    if (mens == "abrir"){ // && digitalRead(SMovimiento) == 1) 
      Serial.println(mens);
      servo1.write(85);
      digitalWrite(PINB,HIGH);
      digitalWrite(PINR,LOW);
      stateServo = true;
      top = "";
      Serial.print(stateServo);
      email();
    }
    else if (mens = "cerrar") {
      Serial.println(mens);
      servo1.write(0);
      digitalWrite(PINB,LOW);
      digitalWrite(PINR,HIGH);
      delay(10000);
      digitalWrite(PINR,LOW);
      stateServo = false;
      top = "";
      email();
    } else {
      Serial.println("Esta definición no existe");
      top = "";
      
    }
  } else if (top == "modificar-temperatura") {
    if (mens.toInt() > 0 && mens.toInt() <= 70) {
      tempLimit = mens.toInt();
      Serial.println(tempLimit);
      top = "";
      refri(t, tempLimit);
      email();
    } else {
      Serial.println("TEMPERATURA NO PERMITIDA");
      top = "";
    }
    
  }
  
  myTestCall();
}

void email() {
  if (event) {
    request = "GET /trigger/" + eventName + "/with/key/" + apiKey + "/?value1="+value1+"&value2="+value2+"&value3="+value3;
    Serial.print("connecting to ");
    Serial.println(host);

    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }

    Serial.print("Requesting: ");
    Serial.println(request);
    client.print(request + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n"   +
                 "Connection: close\r\n"    +
                 "\r\n" );
    event = false; // ensure request once
  }
}

void detectarMovimeinto(){
  EstadoMovimiento = digitalRead(SMovimiento);
  Serial.println(EstadoMovimiento);
  if (EstadoMovimiento == HIGH) {
    Serial.println("Motion detected!");
    }
  else {
    Serial.println("No Motion detected!");
    }

delay(5000);
}
  void dataBase(){
  Serial.println("------------------------------------");
  Serial.println("  ACTUALIZAR EL ESTADO DE LA TEMPERATURA");
  //Also can use Firebase.set instead of Firebase.setDouble
  if (Firebase.setInt(firebaseData, path + "/Temperatura/Bodega", t)){InforSetTemperatura();}else{CausaError();} 
  Serial.println("------------------------------------");
  Serial.println("  ACTUALIZAR EL ESTADO DE LA HUMEDAD");
  //Also can use Firebase.set instead of Firebase.setDouble
  if (Firebase.setInt(firebaseData, path + "/Humedad/Bodega", h)){InforSetHumedad();}else{CausaError();}
  Serial.println("------------------------------------");
  Serial.println("  LEER  EL  ESTADO  DE  LA TEMPERATURA");
  if (Firebase.getInt(firebaseData, path + "/Temperatura/Bodega" )){InforGetTemperatura(); }else{CausaError(); }
  Serial.println("------------------------------------");
  Serial.println("  LEER  EL  ESTADO  DE  LA HUMEDAD");
  if (Firebase.getInt(firebaseData, path + "/Humedad/Bodega" )){InforGetHumedad(); }else{CausaError(); }
}
void InforGetTemperatura(void)
{
  Serial.println("Aprobado");
  Serial.println("Ruta: " + firebaseData.dataPath());
  Serial.println("Tipo: " + firebaseData.dataType());
  Serial.println("ETag: " + firebaseData.ETag());
  Serial.print("Valor: ");
  printResult(firebaseData);
  Serial.println("------------------------------------");
  Serial.println(); 
}

void InforSetTemperatura(void)
{
  Serial.println("Aprobado");
  Serial.println("Ruta: " + firebaseData.dataPath());
  Serial.println("Tipo: " + firebaseData.dataType());
  Serial.println("ETag: " + firebaseData.ETag());
  Serial.print("Valor: ");
  printResult(firebaseData);
  Serial.println("------------------------------------");
  Serial.println(); 
}
void InforGetHumedad(void)
{
  Serial.println("Aprobado");
  Serial.println("Ruta: " + firebaseData.dataPath());
  Serial.println("Tipo: " + firebaseData.dataType());
  Serial.println("ETag: " + firebaseData.ETag());
  Serial.print("Valor: ");
  printResult(firebaseData);
  Serial.println("------------------------------------");
  Serial.println(); 
}

void InforSetHumedad(void)
{
  Serial.println("Aprobado");
  Serial.println("Ruta: " + firebaseData.dataPath());
  Serial.println("Tipo: " + firebaseData.dataType());
  Serial.println("ETag: " + firebaseData.ETag());
  Serial.print("Valor: ");
  printResult(firebaseData);
  Serial.println("------------------------------------");
  Serial.println(); 
}
void CausaError(void)
{
  Serial.println("ERROR");
  Serial.println("RAZON: " + firebaseData.errorReason());
  Serial.println("------------------------------------");
  Serial.println();
}

void printResult(FirebaseData &data)
{
    if (data.dataType() == "int")
        Serial.println(data.intData());
    else if (data.dataType() == "float")
        Serial.println(data.floatData(), 5);
    else if (data.dataType() == "double")
        printf("%.9lf\n", data.doubleData());
    else if (data.dataType() == "boolean")
        Serial.println(data.boolData() == 1 ? "true" : "false");
    else if (data.dataType() == "string")
        Serial.println(data.stringData());
}
