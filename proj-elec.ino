#include <SoftwareSerial.h>
SoftwareSerial bt(1, 0); // RX, TX
#include <Servo.h>
#include <DHT.h>
#define Fan A5 // Arduino pin connected to relay which connected to fan //Low level will activate the relay ON and HIGH level will deactivate it
#define DHTPIN 12           // Arduino pin connected to relay which connected to DHT sensor
#define DHTTYPE DHT11
#define HighTemp  28 // upper threshold of temperature, change to your desire value
#define LowTemp  27 // lower threshold of temperature, change to your desire value
Servo Servo1; 
DHT dht(DHTPIN, DHTTYPE);
char Incoming_value = 0;
float temp;    // temperature in Celsius
float hum;

void setup()
{
  pinMode (4, INPUT); //IR PIN
  pinMode (9, OUTPUT); // entrance white led
  pinMode (8, OUTPUT); //blue led
  pinMode (10, OUTPUT); //door white led
  pinMode (11, OUTPUT); //Warning led
  pinMode(Fan, OUTPUT); // initialize digital pin as an output
  digitalWrite(Fan, HIGH); // Fan not connected at start
  Serial.begin(9600); // initialize serial
  dht.begin();        // initialize the sensor
  
  Servo1.attach(3);



  
}

void loop()
{
   Relay();
 // DoorOpener();
   //Alarm();
  // WinAlarm();
 bt.print(temp); //send distance to MIT App
 bt.print(";");
 bt.print(hum); //send distance to MIT App 
 bt.println(";");

}
void Alarm(){
   if (temp>35){ 
         digitalWrite(11, HIGH); // LED HIGH
       delay(500);
       digitalWrite(11, LOW); // LED HIGH
       delay(500);
        }
}

void DoorOpener(){
    int IR = digitalRead(4);
  //Serial.println(IR);
   Servo1.write(0); 
  if (IR == 0){ // Sensor detect 
   digitalWrite(10, HIGH); 
   digitalWrite(9, HIGH); 
   //Servo1.write(150);
   delay (1000);
  
  }
  else
  {
    digitalWrite(10, LOW);
    
  }
}

void Relay(){
  delay(1000);
   hum = dht.readHumidity();   // read Humidity %
  temp = dht.readTemperature();  // read temperature in Celsius
    //Serial.println("Temp is:"); Serial.println(temp);
    // Serial.println("Humidity :"); Serial.println(hum);

  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    if(temp > HighTemp){
    // Serial.println("The fan is turned on");
    // Serial.println("Temp is:"); Serial.println(temp);
    // Serial.println("Humidity :"); Serial.println(hum);
      digitalWrite(Fan, LOW); // turn on
       digitalWrite (8, HIGH);
    } else if(temp < LowTemp){
     //Serial.println("The fan is turned off");
      //Serial.println("Temp is:"); Serial.println(temp);
      //Serial.println("Humidity :"); Serial.println(hum);
      digitalWrite(Fan, HIGH); // turn off
        digitalWrite(8, LOW);
    }
   
  }

  
}
void WinAlarm(){
 // read the input on analog pin 0
  int sensorValue = analogRead(A0);  

  // print out the value you read:
  //Serial.println("sensorValue: ");
  //Serial.println(sensorValue);
if ( sensorValue >= 100){ // Sensor detect 
   
      digitalWrite(11, HIGH); // LED HIGH
       delay(500);
       digitalWrite(11, LOW); // LED HIGH
       delay(500);
  }
  else
  {
  digitalWrite(11, LOW); 
  }

}
