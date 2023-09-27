#include <credentials.h>
#include <define_LED_grid.h>
#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include <TimeLib.h>
#include <LittleFS.h>
#include <AsyncElegantOTA.h>
#include <PubSubClient.h>
#include <ArduinoJSON.h>

#include <iostream>
#include <string.h>
#include <array>
#include <vector>

#include <define_LED_grid.h>
#include <text_logic.h>

using namespace std;

// string test = " FEUERBACHER FEUDAL ERFOLG SKALIERT ZUR ISS ";
String text = "TIMESTREAM 715";

// Setup NetworkTimeProtocol Client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "de.pool.ntp.org");

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

AsyncWebServer server(80);
AsyncWebSocket websocket("/ws");
String header;

// Setup FastLED
#define NUM_LEDS 105
#define CHIPSET WS2812B
#define COLOR_ORDER GRB
#define LED_PIN 1
CRGB leds[NUM_LEDS];
byte brightn = 150;
int16_t color = 0;
int16_t saturation = 180;
byte last_brightn = brightn;
int16_t last_color = color;
int16_t last_saturation = saturation;
uint8_t fadeSpeed = 30;
sint8_t slinverted = 70;
byte RainbowOn = 0;
byte mode = 0;

int Hour;
int minu;
int sec;
int val_L;
int val_LM;
int val_RM;
int val_R;

vector<byte> text_print_symbol;

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
void instantOn(vector<byte> symbol)
{
  int len = symbol.size();

  for (int i = 0; i < len; i++)
  {
    leds[symbol[i]] = CHSV(color, saturation, brightn);
  }
}

/* __________ code to display time __________ */

void setTime(int time_piece, vector<vector<byte>> grid_position)
{
  vector<byte> symbol;

  switch (time_piece)
  {
  case 0:
    symbol = drawer(null, grid_position);
    break;
  case 1:
    symbol = drawer(one, grid_position);
    break;
  case 2:
    symbol = drawer(two, grid_position);
    break;
  case 3:
    symbol = drawer(three, grid_position);
    break;
  case 4:
    symbol = drawer(four, grid_position);
    break;
  case 5:
    symbol = drawer(five, grid_position);
    break;
  case 6:
    symbol = drawer(six, grid_position);
    break;
  case 7:
    symbol = drawer(seven, grid_position);
    break;
  case 8:
    symbol = drawer(eight, grid_position);
    break;
  case 9:
    symbol = drawer(nine, grid_position);
    break;
  }
  instantOn(symbol);
}

void print_time()
{
  timeClient.update();

  Hour = timeClient.getHours();
  minu = timeClient.getMinutes();
  sec = timeClient.getSeconds();

  val_L = Hour / 10;
  setTime(val_L, gridL);

  val_LM = Hour % 10;
  setTime(val_LM, gridLM);

  val_RM = minu / 10;
  setTime(val_RM, gridRM);

  val_R = minu % 10;
  setTime(val_R, gridR);
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

/* __________ code to display text __________ */

void handleWSData(String cutData)
{
  Serial.println(cutData);
  String idcp = "col;";
  String idsl = "sl;";
  String idpw = "pw;";
  String idro = "R;o";
  String idft = "ft;";
  String idmo = "md;";

  bool testcp = strstr(cutData.c_str(), idcp.c_str());
  bool testsl = strstr(cutData.c_str(), idsl.c_str());
  bool testpw = strstr(cutData.c_str(), idpw.c_str());
  bool testro = strstr(cutData.c_str(), idro.c_str());
  bool testft = strstr(cutData.c_str(), idft.c_str());
  bool testmo = strstr(cutData.c_str(), idmo.c_str());

  // user control LED Panel
  // color picker
  if (testcp)
  {
    cutData = cutData.substring(8);
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

      color = map(HSV[0].toInt(), 0, 360, 0, 255);
      saturation = map(HSV[1].toInt(), 0, 100, 0, 255);
      brightn = map(HSV[2].toInt(), 0, 100, 0, 255);
    }
  }

  // rainbow fade slider
  else if (testsl)
  {
    String sl = cutData.substring(3);
    slinverted = sl.toInt();
    fadeSpeed = map(slinverted, 0, 100, 100, 0);
  }

  // Power control
  else if (testpw)
  {
    if (brightn > 0)
    {
      brightn = 0;
    }
    else
    {
      brightn = 150;
    }
  }

  // Rainbow on/off
  else if (testro)
  {
    String ro = cutData.substring(2);
    if (ro == "off")
    {
      RainbowOn = 69;
    }
    else
    {
      RainbowOn = 1;
    }
  }

  // Flowtext
  else if (testft)
  {
    text = cutData.substring(3);
  }

  // Switch mode
  else if (testmo)
  {
    if (mode == 1)
    {
      mode = 0;
    }
    else
    {
      mode = 1;
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

void mqtt_publish_state()
{
  StaticJsonDocument<96> doc;

  doc["brightness"] = brightn;

  if (brightn == 0)
  {
    doc["state"] = "OFF";
  }
  else
  {
    doc["state"] = "ON";
  }

  JsonObject hs = doc.createNestedObject("hs");
  hs["h"] = map(color, 0, 255, 0, 360);
  hs["s"] = map(saturation, 0, 255, 0, 100);

  char output[256];
  serializeJson(doc, output);
  mqttClient.publish("clock/light", output);
}

void mqtt_update_state()
{
  if (last_brightn != brightn ||
      last_color != color ||
      last_saturation != saturation)
  {
    mqtt_publish_state();
  }
  last_brightn = brightn;
  last_color = color;
  last_saturation = saturation;
}

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
  DynamicJsonDocument doc(8192);
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // analyzes and reacts to payload
  if (doc["state"] == "OFF")
  {
    FastLED.clear();
    brightn = 0;
    FastLED.show();
  }
  else if (doc["state"] == "ON")
  {
    brightn = 150;
  }
  float temp_color = doc["color"]["h"] | float(map(color, 0, 255, 0, 360));
  float temp_saturation = doc["color"]["s"] | float(map(saturation, 0, 255, 0, 100));

  brightn = doc["brightness"] | brightn;
  color = map(temp_color, 0, 360, 0, 255);
  saturation = map(temp_saturation, 0, 100, 0, 255);

  // flowtext
  text = doc["flowtext"] | text;
  if (doc["effect"] == "Uhrzeit")
  {
    mode = 0;
  }
  else if (doc["effect"] == "Fließtext")
  {
    mode = 1;
  }
  else if (doc["effect"] == "Bild"){
    mode = 2;
    FastLED.clear();
    // Picture
    uint8_t led_index = 0;
    JsonArray picture = doc["picture"].as<JsonArray>();
    for (JsonObject picture_item : picture) {
      uint8_t picture_item_H = picture_item["H"];
      uint8_t picture_item_S = picture_item["S"];
      uint8_t picture_item_V = picture_item["V"];
      leds[led_index] = CHSV(picture_item_H,picture_item_S,picture_item_V);
      Serial.println(picture_item_H);
      led_index ++;
    }
    FastLED.show();
    FastLED.clear();
  }

  // rainbow effect
  else if (doc["effect"] == "Farbwechsel")
  {
    if (RainbowOn == 1)
    {
      RainbowOn = 0;
    }
    else
    {
      RainbowOn = 1;
    }
  }
  float temp_slinverted = doc["changespeed"] | float(slinverted);
  fadeSpeed = uint8_t(map(temp_slinverted, 0, 100, 100, 0));
}


void mqtt_update(){
  mqttClient.loop();
  mqtt_update_state();
}


void connect_mqtt(){
  bool feedback = mqttClient.setBufferSize(8192);
  Serial.print("could reserve buffer size: ");
  Serial.println(feedback ? "true" : "false");
  mqttClient.setServer(MQTT_BROKER, MQTT_port);
  mqttClient.setCallback(mqtt_callback);

  while (!mqttClient.connected())
  {
    String client_id = "cock";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (mqttClient.connect(client_id.c_str(), MQTT_username, MQTT_password))
    {
      Serial.println("Public emqx mqtt broker connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(mqttClient.state());
      delay(2000);
    }
  }

  StaticJsonDocument<384> doc;

  doc["schema"] = "json";
  doc["name"] = "clock";
  doc["state_topic"] = "clock/light";
  doc["command_topic"] = "clock/light/set";
  doc["color_mode"] = true;
  doc["supported_color_modes"][0] = "hs";
  doc["brightness"] = true;
  doc["icon"] = "mdi:clock-digital";
  doc["effect"] = true;

  JsonArray effect_list = doc.createNestedArray("effect_list");
  effect_list.add("Farbwechsel");
  effect_list.add("Fließtext");
  effect_list.add("Uhrzeit");
  char output[384];
  serializeJson(doc, output, 384);

  mqttClient.publish("homeassistant/light/clock/config", output);
  mqttClient.subscribe("clock/light/set");
}


void setup()
{
  Serial.begin(9600);
  LittleFS.begin();
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);

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

  connect_mqtt();

  websocket.onEvent(onWsEvent);
  server.addHandler(&websocket);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/index.html", String(), false, processor); });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/style.css", "text/css"); });

  AsyncElegantOTA.begin(&server);
  server.begin();

  timeClient.begin();
  timeClient.setTimeOffset(7200);
}

void loop()
{
  mqtt_update();
  if (mqttClient.state() != 0){
    connect_mqtt();
  }

  if (mode == 0)
  { // display time mode
    timeClient.setTimeOffset(getTimeOffset());
    timeClient.update();
    print_time();
    rainbow();
    FastLED.show();
    delay(fadeSpeed);
    FastLED.clear();
    delay(fadeSpeed);
  }
  else if (mode == 1)
  { // display text mode
    text_print_symbol = disassemble(text,rainbow,mqtt_update);
  }
}