#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#define led 2

const char* ssid = "DZ";
const char* password = "0011223344";

WebServer server(80);



void handleManualON() {
  digitalWrite(led, HIGH );
  server.send(200, "text/plain", "turn motor on!");
  //digitalWrite(led, 0);
}

void handleManualOFF() {
  digitalWrite(led, LOW );
  server.send(200, "text/plain", "turn motor off!");
  //digitalWrite(led, 0);
}

void handleAUTO() {
  for(int i=0;i<20;i++){   
  server.send(200, "text/plain", "write code to condition motor depending on water level!");
  digitalWrite(led, HIGH);
  delay(2000);
  digitalWrite(led, LOW);
  delay(1000);
  //digitalWrite(led, 0);
  }
}


void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/OFF", handleManualOFF);
  server.on("/ON", handleManualON);
  server.on("/AUTO", handleAUTO);

//  server.on("/inline", []() {
//    server.send(200, "text/plain", "this works as well");
//  });

//  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
