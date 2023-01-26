#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include <TimeLib.h>
#include <LittleFS.h>

#include <iostream>
#include <string.h>
#include <array>

#include "credentials.cpp"
#include "define_LED_grid.cpp"

// Setup NetworkTimeProtocol Client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "de.pool.ntp.org");

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
String header;

// Setup FastLED
#define NUM_LEDS 105
#define CHIPSET WS2812B
#define COLOR_ORDER GRB
#define LED_PIN 1
CRGB leds[NUM_LEDS];
byte brightn = 100;
int16_t color = 0;
int16_t saturation = 180;
uint8_t fadeSpeed = 15;
byte RainbowOn = 0;



byte zeroT;
byte oneT;
byte twoT;
byte threeT;
byte fourT;
byte fiveT;
byte sixT;
byte sevenT;
byte eightT;
byte nineT;

int Hour;
int minu;
int sec;
int L;
int LM;
int RM;
int R;

// Date
bool isLastSundayOver(int weekday, int day)
{
  int daysToSunday = 7 - weekday;
  int daysLeft = 31 - day;
  if (daysLeft > 6)
  {
    return false;
  }
  else if ((day + daysToSunday) > 31)
  {
    return true;
  }
  else if ((day == 31) && (weekday == 6))
  {
    return true;
  }
  else
  {
    return false;
  }
}

int getTimeOffset()
{
  int dateMonth = month(timeClient.getEpochTime());
  int dateDay = day(timeClient.getEpochTime());
  int weekday = timeClient.getDay();
  if ((dateMonth > 3) && (dateMonth < 10))
  {
    return 7200;
  }
  else if ((dateMonth == 3) && isLastSundayOver(weekday, dateDay))
  {
    return 7200;
  }
  else if (dateMonth == 10 && !isLastSundayOver(weekday, dateDay))
  {
    return 7200;
  }
  else if (dateMonth == 10 && isLastSundayOver(weekday, dateDay))
  {
    return 3600;
  }
  else
  {
    return 3600;
  }
}

// Functions
void instantOn(byte NumberGrid[], byte Number[])
{
  int len = Number[0];
  for (int i = 1; i < len; i++)
  {
    leds[NumberGrid[Number[i]]] = CHSV(color, saturation, brightn);
  }
}

/*void fadeIn(byte NumberGrid[], byte Number[])
{
  int len = Number[0];
  for (int b = 15; b <= brightn; b++)
  {
    for (int i = 1; i < len; i++)
    {
      leds[NumberGrid[Number[i]]] = CHSV(color, saturation,b);
    }
    FastLED.show();
    delay(5);
  }
}*/


/*void fadeOut(byte NumberGrid[], byte Number[])
{
  int len = Number[0];
  for (int f = brightn; f >= 15; f--)
  {
    for (int i = 1; i < len; i++)
    {
      leds[NumberGrid[Number[i]]] = CHSV(color, saturation, f);
    }
    FastLED.show();
    delay(5);
  }
  for (int i = 1; i < len; i++)
  {
    leds[NumberGrid[Number[i]]] = CHSV(color, saturation, 0);
  }
}*/



void gridTest()
{
  for (int r = 0; r < 7; r++)
  {
    for (int c = 0; c < 15; c++)
    {
      leds[grid[r][c]] = CRGB::RosyBrown;
      FastLED.show();
      delay(50);
      FastLED.clear();
    }
  }
}

void setTime(byte gridTime[], int timePiece)
{
  switch (timePiece)
  {
  case 0:
    instantOn(gridTime, Zero);
    break;

  case 1:
    instantOn(gridTime, One);
    break;

  case 2:
    instantOn(gridTime, Two);
    break;

  case 3:
    instantOn(gridTime, Three);
    break;

  case 4:
    instantOn(gridTime, Four);
    break;

  case 5:
    instantOn(gridTime, Five);
    break;

  case 6:
    instantOn(gridTime, Six);
    break;

  case 7:
    instantOn(gridTime, Seven);
    break;

  case 8:
    instantOn(gridTime, Eight);
    break;

  case 9:
    instantOn(gridTime, Nine);
    break;
  }
}

void getTime()
{
  timeClient.update();

  Hour = timeClient.getHours();
  minu = timeClient.getMinutes();
  sec = timeClient.getSeconds();

  L = Hour / 10;
  LM = Hour % 10;
  RM = minu / 10;
  R = minu % 10;

  setTime(gridL, L);
  setTime(gridLM, LM);
  setTime(gridRM, RM);
  setTime(gridR, R);
}

void rainbow()
{
  if (RainbowOn == 1)
  {
    if (color == 255)
    {
      color = 0;
    }
    color = color + 1;
  }
}

void handleWSData(String cutData)
{
  String idcp = "col";
  String idsl = "sl";
  String idpw = "pw";
  String idro = "Ro";

  bool testcp = strstr(cutData.c_str(), idcp.c_str());
  bool testsl = strstr(cutData.c_str(), idsl.c_str());
  bool testpw = strstr(cutData.c_str(), idpw.c_str());
  bool testro = strstr(cutData.c_str(), idro.c_str());

  // user control LED Panel
  // color picker
  if (testcp == 1)
  {
    cutData = cutData.substring(7);
    Serial.println(cutData);
    byte del0;
    byte del1;
    byte del2;
    String HSV[3] = {};
    for (int delLoop = 0; delLoop <= 2; delLoop++)
    {
      del0 = cutData.indexOf(':');
      cutData = cutData.substring(del0);
      del0 = cutData.indexOf(':');
      del1 = cutData.indexOf(',');
      del2 = cutData.indexOf('}');

      if (delLoop < 2)
      {
        HSV[delLoop] = cutData.substring(del0 + 1, del1);
        cutData = cutData.substring(del1);
      }
      else
      {
        HSV[delLoop] = cutData.substring(del0 + 1, del2);
      }
      Serial.println(HSV[0]);
      Serial.println(HSV[1]);
      Serial.println(HSV[2]);

      color = map(HSV[0].toInt(), 0, 360, 0, 255);
      saturation = map(HSV[1].toInt(), 0, 100, 0, 255);
      brightn = map(HSV[2].toInt(), 0, 100, 0, 255);
      
    }
  }

  // rainbow fade slider
  else if (testsl == 1)
  {
    String sl = cutData.substring(2);
    Serial.println(sl);
    sint8_t slinverted = sl.toInt() - 100;
    slinverted = -1 * slinverted;
    Serial.println(slinverted);
    fadeSpeed = slinverted;
  }

  // Power control
  else if (testpw == 1)
  {
    String pw = cutData.substring(2);
    Serial.println(pw);
    if (pw == "0")
    {
      brightn = 0;
    }
    else
    {
      brightn = 100;
    }
  }

  // Rainbow on/off
  else if (testro == 1)
  {
    String ro = cutData.substring(1);
    Serial.println(ro);
    if (ro == "off")
    {
      RainbowOn = 69;
    }
    else
    {
      RainbowOn = 1;
    }
  }
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
  if (type == WS_EVT_CONNECT)
  {
    Serial.println("Websocket client connection received");
    client->text("Hello from ESP32 Server");
  }
  else if (type == WS_EVT_DISCONNECT)
  {
    Serial.println("Client disconnected");
  }
  else if (type == WS_EVT_DATA)
  {
    data[len] = 0;

    String cutData = (char *)data;
    handleWSData(cutData);
  }
}

String processor(const String &var)
{
  if (brightn != 0)
  {
    return "An";
  }
  return "Aus";
}

void setup()
{
  LittleFS.begin();
  Serial.begin(115200);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/index.html", String(), false, processor); });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/style.css", "text/css"); });

  server.begin();

  timeClient.begin();
  timeClient.setTimeOffset(7200);
}

void loop()
{
  // put your main code here, to run repeatedly:
  timeClient.setTimeOffset(getTimeOffset());
  timeClient.update();
  getTime();
  rainbow();

  FastLED.show();
  delay(fadeSpeed);
  FastLED.clear();
  delay(fadeSpeed);
}