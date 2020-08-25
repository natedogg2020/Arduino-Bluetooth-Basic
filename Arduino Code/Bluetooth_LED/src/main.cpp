#include <Arduino.h>
#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino

BluetoothSerial ESP_BT; //Object for Bluetooth

char Incoming_value = 0;                //Variable for storing Incoming_value
void setup() 
{
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(13, OUTPUT);        //Sets digital pin 13 as output pin
  pinMode(12, OUTPUT);        //Sets digital pin 13 as output pin

  ESP_BT.begin("ESP32_LED_Control"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");
}

void controlLine(int pin, int level){
  String levelString = "";
  if(level == HIGH){
    levelString = "on";
  }else {
    levelString = "off";
  }
  if(digitalRead(pin) == level)
  {
    ESP_BT.println(("Pin "+ String(pin) +" is already " + levelString) );
    digitalWrite(pin, level);  //If value is 1 then LED turns ON 
  } else 
  {
    digitalWrite(pin, level);  //If value is 1 then LED turns ON 
    ESP_BT.println(("Pin "+ String(pin) +" is turned "+levelString));
  }
  
}

void loop()
{
  if(ESP_BT.available() > 0)  
  {
    Incoming_value = ESP_BT.read();      //Read the incoming data and store it into variable Incoming_value
    Serial.print(Incoming_value);        //Print Value of Incoming_value in Serial monitor
    Serial.print("\n");        //New line 
    if(Incoming_value == '1')            //Checks whether value of Incoming_value is equal to 1 
    {
      Serial.print("Received 1");
      controlLine(13, HIGH);
    }
    else if(Incoming_value == '0')       //Checks whether value of Incoming_value is equal to 0
    {
      Serial.print("Received 0");
      controlLine(13, LOW);   //If value is 0 then LED turns OFF
    }
    if(Incoming_value == '3')            //Checks whether value of Incoming_value is equal to 1 
    {
      Serial.print("Received 3");
      controlLine(12, HIGH);  //If value is 1 then LED turns ON
    }
    else if(Incoming_value == '2')       //Checks whether value of Incoming_value is equal to 0
    {
      Serial.print("Received 2");
      
      controlLine(12, LOW);   //If value is 0 then LED turns OFF
    }
  }                            
 
}                 