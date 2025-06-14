#include <WebServer.h>
#include <AsyncTCP.h>
#include <stdio.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "SPIFFS.h"
#define LED 18  // Iebuvetais LED0
#define LED1 19 // Iebuvetais LED1

int brightness = 0; // LED Spilgtums
int fadeAmount = 5; // Cik LED spilgtumu mainit

// PWM mainigie
const int freq = 5000;
const int ledChannel = 0;
const int ledChannel1 = 1;
const int resolution = 10; // Resolution 8, 10, 12, 15

// Tagad Laiks
unsigned long currentTime = millis();
// Ieprieksejais laiks
unsigned long previousTime = 0;
// Timeout ms
const long timeoutTime = 2000;
// Mainigais HTTP requestiem
String header;

// WiFi Access Point Mainigie
const char *APssid = "ESP32-WROOM";
const char *APpassword = "";
IPAddress APlocal_IP(192, 168, 4, 1);
IPAddress APgateway(192, 168, 4, 1);
IPAddress APsubnet(255, 255, 255, 0);

// WiFi STAtion mainigie
const char *STAssid = "thai";          // Network to be joined as a station SSID
const char *STApassword = "123456789"; // Network to be joined as a station password
IPAddress STAlocal_IP(192, 168, 0, 27);
IPAddress STAgateway(192, 168, 0, 1);
IPAddress STAsubnet(255, 255, 255, 0);

// UDP Mainigie
unsigned int localUdpPort = 4210;
char incomingPacket[255];
char replyPacket[] = "..";
char command[4][4];
int commandInt[4];
char *commandPosition;

// UDP un WiFi Serveru bibloteku instance
WiFiUDP udp;
WebServer server(80);

int orangex;
int orangey;
int cyanx;
int cyany;
int power = 60;

void handleJSData()
{
  // Iegust X un Y no web joysticka
  orangex = server.arg(0).toInt();
  orangey = server.arg(1).toInt();
  cyanx = server.arg("x2").toInt();
  cyany = server.arg("y2").toInt();

  // Test mode change --Hieu
  if (server.hasArg("power"))
  {
    power = server.arg("power").toInt();
  }

  // Atgriez HTTP 200
  server.send(200, "text/plain", "");
}

void setup()
{
  Serial.begin(115200);
  delay(1000); // Chờ Serial sẵn sàng

  Serial.println("\n[ESP32 Khởi động hệ thống]");

  // === PWM LED Setup ===
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  ledcSetup(ledChannel, freq, resolution);
  ledcSetup(ledChannel1, freq, resolution);
  ledcAttachPin(LED, ledChannel);
  ledcAttachPin(LED1, ledChannel1);

  // === WiFi Dual Mode: AP + STA ===
  WiFi.mode(WIFI_AP_STA);

  // Kết nối đến WiFi router
  Serial.print("Đang kết nối đến WiFi STA: ");
  Serial.println(STAssid);
  WiFi.begin(STAssid, STApassword);

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 20)
  {
    delay(500);
    Serial.print(".");
    retry++;
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("\n[STA] Đã kết nối WiFi router!");
    Serial.print("[STA] IP: ");
    Serial.println(WiFi.localIP());
    delay(5000);
  }
  else
  {
    Serial.println("\n[STA] Kết nối WiFi thất bại!");
  }

  // === UDP ===
  Serial.println("\nBắt đầu UDP...");
  udp.begin(localUdpPort);
  Serial.print("UDP port: ");
  Serial.println(localUdpPort);

  // === SPIFFS ===
  if (!SPIFFS.begin(true))
  { // 'true' để format nếu lần đầu dùng
    Serial.println("SPIFFS khởi động thất bại!");
  }
  else
  {
    Serial.println("SPIFFS OK");
  }

  // === Web Server Setup ===
  server.serveStatic("/", SPIFFS, "/joystick.html");
  server.serveStatic("/virtualjoystick.js", SPIFFS, "/virtualjoystick.js");
  server.on("/jsData.html", handleJSData);
  server.begin();
  Serial.println("WebServer đã khởi động!");
}

void loop()
{
  server.handleClient();
  int brightness = map(orangey, -120, 120, 0, 1024);
  int brightness1 = map(cyany, -120, 120, 0, 1024);

  // Test mode change --Hieu
  brightness = brightness * power / 100;
  brightness1 = brightness1 * power / 100;

  ledcWrite(ledChannel, brightness);
  ledcWrite(ledChannel1, brightness1);
  Serial.printf("OX: %d OY: %d CX: %d CY: %d\n", orangex, orangey, cyanx, cyany);
}
