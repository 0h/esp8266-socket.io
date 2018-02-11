#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SocketIoClient.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";

const char* socketServer = "SERVER_ID";
const int socketPort = 4200;

SocketIoClient socket;

void event(const char * payload, size_t length) {
  Serial.printf("got message: %s\n", payload);
}

void connect(const char * payload, size_t length) {
  socket.emit("join", "Hello from IOT");
}

void broad(const char * payload, size_t length) {
  Serial.printf("reset broad message received %s", payload);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for(uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  socket.on("event", event);
  socket.begin(socketServer, socketPort);
  socket.on("connect", connect);
  socket.on("broad", broad);
}

void loop() {
    socket.loop();
}
