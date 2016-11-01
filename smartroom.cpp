(Follow coding standards and include appropriate comments)
#include<SPI.h>
#include<Ethernet.h>
byte mac[]={0*DE,0*AD,0*BE,O*EF,O*ED};


int sensorPin = A0; // select the input pin for ldr
int sensorValue = 0; // variable to store the value coming from the sensor
int pir=3;
int pirstate=0;
int ledpin=11;


char server[]="http://puru.esy.es"
IPAddress ip(10,1,106,69);
EthernetClient client;


void setup() {
Serial.begin(9600); //sets serial port for communication
while(!Serial){
  ;
}
 if(Ethernet.begin(mac)==0){
  Ethernet.begin(mac.ip);
  
 }
delay(1000);
Serial.println("connecting....");
if(client.connect(server,80)){
  Serial.println("connected");
  client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
}
else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
pinMode(ledpin,OUTPUT);


}




boolean PIR()
{
  boolean clos= false ;
  int val= digitalRead(pir);
  if( val == HIGH )
  {
    clos = true;
    if(pirstate==LOW)
    {
      Serial.println("Motion Detected");
      pirstate=HIGH;
     }
   }
   else
   {
    if(pirstate==HIGH)
    {
      pirstate=LOW;
      Serial.println("Motion ended");
      clos = false;
    }
    clos=false;
    }
    return clos;
}


void loop() {
boolean x;
sensorValue = analogRead(sensorPin); // read the value from the sensor
Serial.println(sensorValue); //prints the values coming from the sensor on the screen
x=PIR();
if((x==HIGH&&(sensorValue<400)))
{
  Serial.print("inside ldr");
  digitalWrite(ledpin,HIGH);
}
else
{
  digitalWrite(ledpin,LOW);
}


if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }


  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();


    // do nothing forevermore:
    while (true);
  }
}




