#include <WiFi.h>
#include <WebServer.h>


// ---------------- PIN DEFINITIONS ----------------
#define MQ05_PIN 34


// ---------------- OBJECT CREATION ----------------

WebServer server(80);

// ---------------- WIFI CREDENTIALS ----------------
const char* ssid = "iPhone";
const char* password = "sarahnida";



// ---------------- WEBPAGE HANDLER ----------------
void handleRoot() {

 
  int mqValue = analogRead(MQ05_PIN);
  

  String page = "<!DOCTYPE html><html><head>";
  page += "<meta http-equiv='refresh' content='5'>";
  page += "<title>ESP32 Air Monitor</title>";
  page += "</head><body style='font-family:Arial;'>";

  page += "<h1>ESP32 Air Quality Monitor</h1>";

  page += "<h2>Environment Data</h2>";
  
  page += "<h2>Gas Sensor</h2>";
  page += "<p>MQ05 Raw Value: " + String(mqValue) + "</p>";

  page += "<p>(Auto refresh every 5 seconds)</p>";
  page += "</body></html>";

  server.send(200, "text/html", page);
}

// ---------------- SETUP ----------------
void setup() {

  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("Open this IP in browser: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.status());

  server.on("/", handleRoot);
  server.begin();
}

// ---------------- LOOP ----------------
void loop() {
  server.handleClient();
}
