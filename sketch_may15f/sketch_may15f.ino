#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

// Cấu hình kết nối Wifi (laptop hotspot)
const char* ssid     = "LAPTOP-JLEPEVHC 0010";
const char* password = "12345678";

ESP8266WebServer server(80);
SoftwareSerial unoSerial(D5, D6);  // D5=TX→UNO Rx, D6=RX←UNO Tx

void handlePump() {
  if (!server.hasArg("volume")) {
    server.send(400, "text/plain", "Missing volume");
    return;
  }
  String vol = server.arg("volume");
  unoSerial.println(vol);
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  unoSerial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());

  server.on("/pump", HTTP_GET, handlePump);
  server.begin();
}

void loop() {
  server.handleClient();
}