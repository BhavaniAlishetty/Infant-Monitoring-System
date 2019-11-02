// the setup function runs once when you press reset or power the board

#include <SoftwareSerial.h>
#define buzzerPin 6 
#define trigPin 8 
#define echoPin 9
//serial communication
SoftwareSerial myserial(2,3);// rx,tx

//DHT sensor header files
#include "DHT.h"
#define DHTPIN A0     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

//moisture sensor
int m_in = A1;
int m_out;


void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.print("Ultrasonic Sensor Starting!!!");
   Serial.begin(115200);
   myserial.begin(115200);
   dht.begin();
}
// the loop function runs over and over again forever
void loop()  
{
  String data;
  int duration,distance;
  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance =(duration/2) * 0.0343;// D = time * speed of sound(0.0343cm/microsec)
  Serial.print("Distance:");
  Serial.print(distance);
  Serial.println(" cm");  
  if(distance<10)
  {
   data=",Alert";
  }
  else data=",Safe";
 
  delay(5000);
  
  //humidity
  float h = dht.readHumidity();
  
  //temperature as Celsius
  float t = dht.readTemperature();
  
  //analog output of moisture
   m_out= analogRead(m_in);
   //mapping the moisture value to numerical value
   m_out = map(m_out,550,0,0,100);
   
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else if(isnan(m_out))
  {
    Serial.println("Failed to read from Moisture sensor!");
    return;
  }
  if((t<16||t>30)||(h>20))
   {
    analogWrite(buzzerPin,128);
   }
   else
   {
    analogWrite(buzzerPin,0);
   }
  Serial.print("\nHumidity: ");
  Serial.print(h);
  Serial.print("\nTemperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.println("\nMoisture : ");
  Serial.print(100+m_out);
  data+= ","+String(t)+","+String(h)+","+String(100+m_out)+"!";
  myserial.println(data);
  Serial.println("\nData Collected: "+data); 
}

















