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

// Setup NetworkTimeProtocol Client
const char *ssid = "Baba";
const char *password = "6;H*AB6WDPek:C74";
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

// Setup for different grids on 7x15 board
byte grid[7][15] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
    {29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15},
    {30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44},
    {59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45},
    {60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74},
    {89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75},
    {90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104}};

byte border[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104};

byte gridL[] = {
    29, 28, 27,
    30, 31, 32,
    59, 58, 57,
    60, 61, 62,
    89, 88, 87};

byte gridLM[] = {
    25,
    24,
    23,
    34,
    35,
    36,
    55,
    54,
    53,
    64,
    65,
    66,
    85,
    84,
    83,
};

byte gridRM[] = {
    21,
    20,
    19,
    38,
    39,
    40,
    51,
    50,
    49,
    68,
    69,
    70,
    81,
    80,
    79,
};

byte gridR[] = {
    17, 16, 15,
    42, 43, 44,
    47, 46, 45,
    72, 73, 74,
    77, 76, 75};

// Setup Numbers for 5x3 Grids
byte Zero[] = {13, 0, 1, 2, 3, 6, 9, 12, 13, 14, 11, 8, 5};
byte One[] = {7, 2, 4, 5, 8, 11, 14};
byte Two[] = {12, 0, 1, 2, 5, 8, 7, 6, 9, 12, 13, 14};
byte Three[] = {12, 0, 1, 2, 5, 6, 7, 8, 11, 12, 13, 14};
byte Four[] = {10, 0, 3, 6, 7, 8, 11, 14, 2, 5};
byte Five[] = {12, 0, 1, 2, 3, 6, 7, 8, 11, 12, 13, 14};
byte Six[] = {12, 0, 3, 6, 9, 12, 13, 14, 11, 8, 7, 1};
byte Seven[] = {8, 0, 1, 2, 5, 8, 11, 14};
byte Eight[] = {14, 0, 1, 2, 3, 5, 6, 7, 8, 9, 11, 12, 13, 14};
byte Nine[] = {12, 0, 1, 2, 3, 5, 6, 7, 8, 11, 13, 14};

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

void fadeIn(byte NumberGrid[], byte Number[])
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
}

void fadeOut(byte NumberGrid[], byte Number[])
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
}

void borderTimer()
{
}

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