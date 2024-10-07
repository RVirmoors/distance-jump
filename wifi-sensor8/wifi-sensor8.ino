#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>  
#include <OSCMessage.h>
#include "ipconfig.h"

const int TRIG_PIN = 12;       // D6
const int ECHO_PIN = 13;       // D7

long duration;
int prevDist;
int distance;
int timer;

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
OSCErrorCode error;
const unsigned int outPort = HOST_PORT;
const unsigned int localPort = 8800;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(115200);
  
  Serial.print("Connecting to ");
  Serial.println(SSID_name);
  WiFi.begin(SSID_name, passw);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
#ifdef ESP32
  Serial.println(localPort);
#else
  Serial.println(Udp.localPort());
#endif

}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.017;
  Serial.println(distance);

  if (distance - prevDist < -10) {
//    digitalWrite(LED_BUILTIN, HIGH); 
    timer = 0;
//    OSCMessage msg("/trigger");
//    msg.add(1);
//    Udp.beginPacket(outIp, outPort);
//    msg.send(Udp); // send the bytes to the SLIP stream
//    Udp.endPacket(); // mark the end of the OSC Packet
//    msg.empty(); // free space occupied by message
  } else {
    timer++;
  }

  if (timer > 20) {
    digitalWrite(LED_BUILTIN, LOW);
  }

  OSCMessage msg("/distance");
  msg.add(distance);
  Udp.beginPacket(HOST_IP, outPort);
  msg.send(Udp); // send the bytes to the SLIP stream
  Udp.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message

  prevDist = duration;
  delay(20);
}
