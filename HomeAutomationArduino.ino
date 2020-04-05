#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Servo.h>


//  Database connection defining, Firebase Host and auth are taken by firebase
#define FIREBASE_HOST "***"
#define FIREBASE_AUTH "***"

//internet connection defining
#define WIFI_SSID "alp"
#define WIFI_PASSWORD "alperen123"

#include "DHTesp.h"
DHTesp dht;

Servo servo_motor;

void setup() {
  Serial.begin(9600);
 
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //firebase connection 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  dht.setup(D4, DHTesp::DHT11); //DHT11 temperature and humidity sensor
  pinMode(D7, OUTPUT);      //for Role1 which for lamp
  digitalWrite(D7, LOW);   
  servo_motor.attach(D0);   //garage_door_connected to D0
  servo_motor.write(10);
  pinMode(D5, OUTPUT);      //relay2
  digitalWrite(D5, LOW);
  pinMode(buzzerPin, OUTPUT);  //buzzer
  digitalWrite(D6, LOW);
  pinMode(D3,OUTPUT); //motordriver in1
  pinMode(D2,OUTPUT); //motordriver in2
  pinMode(D1,OUTPUT); //motordriver in3
  pinMode(D8,OUTPUT); //motordriver in4
  pinMode(A0,INPUT_PULLUP); // Magnetic Door Switch 
  //pinMode(A0,OUTPUT);
}

void loop() {
  
  int humidity = dht.getHumidity();
  int temperature = dht.getTemperature();

  if (humidity<200)
  {
    Firebase.setInt("humidity",humidity/4);
    Serial.print("hum: "); Serial.println(humidity/4);
    Serial.print("tem: "); Serial.println(temperature);
  }
 
  //set humidity
  if (Firebase.failed()) {
      Serial.print("humidity could not change ");
      Serial.println(Firebase.error());  
      return;
  }

  if(temperature<200)
  {
    Firebase.setInt("temperature",temperature); //set temperature
  }

  

  if (Firebase.failed()) {
      Serial.print("temperature could not change ");
      Serial.println(Firebase.error());  
      return;
  }
  String status_of_lamp = Firebase.getString("light");
  Serial.print("status of lamp is = ");
  Serial.println(status_of_lamp);

  if(status_of_lamp == "\"on\"")
  {
    digitalWrite(D7, HIGH);
    Serial.println("lamba aciliyor");

  }
  else if(status_of_lamp == "\"off\"")
  {
     digitalWrite(D7, LOW);
     Serial.println("lamba kapaniyor");

  }

   String status_of_garage_door = Firebase.getString("garage_door");
  Serial.print("status of garage door is = ");
  Serial.println(status_of_garage_door);

  if(status_of_garage_door == "\"on\"")
  {

    Serial.println("kapi aciliyor");
    servo_motor.write(95);
  }
  else if(status_of_garage_door == "\"off\"")
  {

     Serial.println("kapi kapaniyor");
     servo_motor.write(10);
  }

 String status_of_priz = Firebase.getString("priz");
  Serial.print("status of priz is = ");
  Serial.println(status_of_priz);

  if(status_of_priz == "\"on\"")
  {
    digitalWrite(D5, HIGH);
    Serial.println("priz aciliyor");

  }
  else if(status_of_priz == "\"off\"")
  {
     digitalWrite(D5, LOW);
     Serial.println("priz kapaniyor");

  }

 String status_of_heater = Firebase.getString("heater");

  Serial.print("status of heater is = ");
  Serial.println(status_of_heater);
  
  if(status_of_heater == "\"on\"")
  {
    digitalWrite(D1, HIGH);
    digitalWrite(D8, LOW);

 
  
    Serial.println("isitici aciliyor");

  }
  else if(status_of_heater == "\"off\"")
  {

    digitalWrite(D1, LOW);
    digitalWrite(D8, LOW);
    Serial.println("isitici kapaniyor");

  }

  String status_of_cooler = Firebase.getString("cooler");
  Serial.print("status of cooler is = ");
  Serial.println(status_of_cooler);

  if(status_of_cooler == "\"on\"")
  {
    digitalWrite(D3, HIGH);
    digitalWrite(D2, LOW);

    Serial.println("soğutucu aciliyor");

  }
  else if(status_of_cooler == "\"off\"")
  {
    
    digitalWrite(D3, LOW);
    digitalWrite(D2, LOW);
    Serial.println("soğutucu kapaniyor");

  }

  
  int button_state_door = analogRead(A0);
  String status_of_alarm = Firebase.getString("alarm");
  Serial.print("status_of_alarm is = ");
  Serial.println(status_of_alarm);
  Serial.println(button_state_door);
  if((status_of_alarm == "\"on\"") & (button_state_door > 300))
  {

    digitalWrite(buzzerPin, HIGH);
    Serial.println("alarm caliyor");

  }
  else if(status_of_alarm == "\"off\"")
  {
 
     digitalWrite(buzzerPin, LOW);
     Serial.println("alarm kapali");

  }
  else if(status_of_alarm == "\"on\"")
  {
   
     digitalWrite(buzzerPin, LOW);
     Serial.println("alarm kapali");

  }    
}
