#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SocketIoClient.h>

const char *ssid = "WIFI_SSID";
const char *password = "WIFI_PASSWORD";

const char *socketServer = "SOCKET_SERVER_IP";
const int socketPort = 4200;

SocketIoClient socket;

void event(const char *payload, size_t length)
{
  Serial.printf("got message: %s\n", payload);
}

void IOTbroad(const char *payload, size_t length)
{
  Serial.printf("Broadcasting message: %s\n", payload);
  digitalWrite(4, LOW);
  delay(1000);
  digitalWrite(4, HIGH);
}

void setup()
{
  Serial.begin(115200);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  socket.on("event", event);
  socket.begin(socketServer, socketPort);
  socket.on("broad", IOTbroad);
}

void loop()
{
  socket.loop();
}
