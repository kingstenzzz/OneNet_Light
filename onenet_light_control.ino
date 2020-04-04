#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "time.h"



#define  Btn_light 2  
#define  People_io 3


 // Update these with values suitable for your network.

 const char* ssid = "kingsten";//WIFI名
 const char* password = "23622033";//密码
 const char* mqtt_server = "183.230.40.39";//onenet服务器
 const char* DEV_ID = "590574850"; //设备ID
 const char* DEV_PRO_ID = "315799"; //产品ID
 const char* DEV_KEY = "IDePEtsFhXPK4FHqrZ9T7FbNo6s="; //API KEY
 IPAddress staticIP(192,168,2,107);//固定IP地址
IPAddress gateway(192,168,2,1);//网关地址
IPAddress subnet(255,255,255,0);//子网掩码地址

 WiFiClient espClient;
 PubSubClient client(espClient);
 long lastMsg = 0;
 char msg[50];
 int value = 0;
 char tmp[50];
 char d[3];
int light_flag=0;




//wifi初始化
 void setup_wifi() {

   delay(10);
   // We start by connecting to a WiFi network
   Serial.println();
   Serial.print("Connecting to ");
   Serial.println(ssid);

    //WiFi.config(staticIP,gateway,subnet);
   WiFi.begin(ssid, password);

   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
   }

   randomSeed(micros());

   Serial.println("");
   Serial.println("WiFi connected");
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
 }

 
void public_data(){
      snprintf(tmp,sizeof(tmp),"{\"light\":%d}",light_flag); //snprintf(tmp,sizeof(tmp),"{\"数据流ID1\":%d ,\"数据流ID2\":%d}",val_1,val_2);
                 uint16_t streamLen= strlen(tmp);
          
                 d[0]='\x03';
                 d[1] = (streamLen >> 8);
                 d[2] = (streamLen & 0xFF);
                 snprintf(msg,sizeof(msg),"%c%c%c%s",d[0],d[1],d[2],tmp);
                 client.publish("$dp", (uint8_t*)msg,streamLen+3,false);
          
    }


 void callback(char* topic, byte* payload, unsigned int length) {
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
   for (int i = 0; i < length; i++) {
     Serial.print((char)payload[i]);
   }
   Serial.println();

  
   if ((char)payload[0] == '1') {
     Serial.println("ON: ");
     light_flag=1;
     digitalWrite(Btn_light, LOW);   // Turn the LED on (Note that LOW is the voltage level
   } else {
     Serial.println("OFF: ");
     light_flag=0;
     digitalWrite(Btn_light, HIGH);  // Turn the LED off by making the voltage HIGH
   }
   public_data();

 }

 void reconnect() {
   // Loop until we're reconnected
   while (!client.connected()) {
     Serial.print("Attempting MQTT connection...");
     if (client.connect(DEV_ID,DEV_PRO_ID,DEV_KEY)) {
       Serial.println("connected");
     } else {
       Serial.print("failed, rc=");
       Serial.print(client.state());
       Serial.println(" try again in 5 seconds");
       // Wait 5 seconds before retrying
       delay(5000);
     }
   }
 }

 void setup() {

  
  
   Serial.begin(115200);
      Serial.print("start");
    Serial.print("failed, rc=");
        pinMode(People_io, INPUT);
     pinMode(Btn_light, OUTPUT);     // Initialize the Btn_light pin as an output
      digitalWrite(Btn_light, HIGH);  
 //  dht.begin();
   setup_wifi();
   client.setServer(mqtt_server, 6002);
   client.connect(DEV_ID,DEV_PRO_ID,DEV_KEY);
   client.setCallback(callback);
 }

 void loop() {
  int hour;
  
   if (!client.connected()) {
     reconnect();
   }
   client.loop();
   
     delay(1000);
     hour=Get_Time();
     Serial.println(Get_Time(),DEC);
     Serial.println("connected");
     if(hour>=17&&hour<=23)
     {
     if(digitalRead(People_io))//有人高电平
     {
       digitalWrite(Btn_light, LOW);   // Turn the LED on (Note that LOW is the voltage level
        Serial.print("people");
      }
     }   

 }

