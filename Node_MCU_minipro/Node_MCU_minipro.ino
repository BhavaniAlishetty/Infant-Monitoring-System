 String data,url2,temp,humid,moist,edge=" ";
#include <SoftwareSerial.h>   
SoftwareSerial mySerial(D2,D3);

/////////////////////// i added

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
//const char* ssid = "Try to connect.";
//const char* password = "connected.";
const char* ssid = "bavvi210";
const char* password = "12345678";
#define ORG "ttuhz3"
#define DEVICE_TYPE "MiniPro"
#define DEVICE_ID "87654321"
#define TOKEN "xs-K73F?yy_1S+5&oN"
//-------- Customise the above values --------
 
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/data/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
float t,h,m;
WiFiClient wifiClient;
PubSubClient client(server, 1883,wifiClient);

//////////////////////////////

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
 ////////////////// i added
 Serial.print(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 
 Serial.print("WiFi connected, IP address: ");
 Serial.println(WiFi.localIP());

 //////////////////////////////
 
  while (!mySerial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() { // run over and over

  if (mySerial.find(","))
{
  url2=mySerial.readStringUntil('!');
  Serial.println(url2);
  edge = getValue1(url2, ',', 0);
  temp = getValue1(url2, ',', 1);
  humid = getValue1(url2, ',', 2);
  moist = getValue1(url2, ',', 3);
}
t = temp.toFloat();
h = humid.toFloat();
m = moist.toFloat();
PublishData(edge,t,h,m);

delay(1000);
 
}

void PublishData(String edge,float temp, float humid,float moist){
 if (!!!client.connected()) {
 Serial.print("Reconnecting client to ");
 Serial.println(server);
 while (!!!client.connect(clientId, authMethod, token)) {
 Serial.print(".");
 delay(500);
 }
 Serial.println();
 }
  String payload = "{\"d\":{\"temperature\":";
  payload += temp;
  payload+="," "\"humidity\":";
  payload += humid;
  payload+="," "\"moisture\":";
  payload += moist;
  payload+="," "\"edge\":";
  payload += "\""+edge+"\"";
  payload += "}}";
 Serial.print("Sending payload: ");
 Serial.println(payload);
  
 if (client.publish(topic, (char*) payload.c_str())) {
 Serial.println((char*) payload.c_str());
 Serial.println("Publish ok");
 } else {
 Serial.println("Publish failed");
 }
}

String getValue1(String data, char separator, int index){
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
        
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
