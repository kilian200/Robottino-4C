#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 8
// Set up a new SoftwareSerial object
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

String check4answer(){
    String str = "";
    while (mySerial.available() > 0) {
        char c = mySerial.read();
        Serial.print(c);
        str += String(c);
    }
    return str;
}


String esp01cmd(String cmd) {
  Serial.println("sending: " + cmd);
  mySerial.println(cmd);
  delay(10);
  String risposta = check4answer();
  return risposta;
}

void setup()  {
    // Define pin modes for TX and RX
    // pinMode(rxPin, INPUT);
    // pinMode(txPin, OUTPUT);
    
    // Set the baud rate for the SoftwareSerial object
    mySerial.begin(115200);
    Serial.begin(9600);
    delay(1000);
    esp01cmd("AT");  //attention
    delay(1000);
    esp01cmd("AT+CWMODE=2");//Set the wifi mode of Client/Station/AP
    delay(1000);
    esp01cmd("AT+CWSAP=\"robottino\",\"robottino\",1,4"); //Set the configuration of an ESP32 SoftAP, impost the SSID and Password
    delay(1000);
    esp01cmd("AT+CIFSR"); //show AP IP address
    esp01cmd("AT+CIPMUX=1"); //allow up to 1 connections at the time
    
    
    Serial.println("ESP-01 Configuration Completed");
}

void loop() {
    Serial.println("loop...");
    //AT+CWLIF obtain Client IP of the Wifi module
    while(esp01cmd("AT+CWLIF").substring(11,18) != "192.168") { //when the client is connected it will appear its IP address
      Serial.println("no connections so far... still waiting"); //it will continue until somehome its connected
      delay(1000);
    }

    Serial.println("Connection from remote device was Established!!!");
    //Socket ID: 3
    //accept packets from any IP address/devices
    //Listen to local port 4567
    //outgoing packets could go to any remote host without restrictions...
    esp01cmd("AT+CIPSTART=3,\"UDP\",\"0.0.0.0\",0,4567,2"); //starting UDP Socket Server (Application)
    
//    String str = ;    
//    Serial.println("received: "+esp01cmd("AT+CWLIF").substring(11,18));
    delay(3000);
    while(true) {
      String str = mySerial.readString();
      if(str != "") {
        int startOfSTR = str.indexOf(":",10)+1;
        Serial.println("Received: "+str.substring(startOfSTR));
        //Serial.println("Received: "+str);
        //Serial.println(startOfSTR);
      }
    }

}
