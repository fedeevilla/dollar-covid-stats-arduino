#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "SH1106Wire.h"
#include "images.h"
#include "functions.h"

SH1106Wire display(0x3c, D2, D1);
const char *ssid = "ssid";
const char *password = "password";

void setup()
{
  display.init();
  display.flipScreenVertically();

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    display.clear();
    display.setFont(Roboto_Bold_16);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
    display.display();
  }
}

void loop()
{
  String dolar = "";
  String btc = "";
  String eth = "";
  int i = 0;

  if (WiFi.status() == WL_CONNECTED)
  {
    dolar = getDolar();
    btc = getBTC();
    eth = getETH();

    while (i < 4)
    {

      display.clear();
      display.setTextAlignment(TEXT_ALIGN_CENTER);
      display.setFont(Roboto_Bold_16);
      display.drawString(62, 0, "DOLAR");
      display.setFont(DejaVu_Sans_12);
      display.drawString(62, 22, dolar);
      display.display();
      delay(5000);

      display.clear();
      display.setTextAlignment(TEXT_ALIGN_CENTER);
      display.setFont(Roboto_Bold_16);
      display.drawString(62, 0, "BITCOIN");
      display.setFont(DejaVu_Sans_14);
      display.drawString(62, 30, btc);
      display.display();
      delay(5000);

      display.clear();
      display.setTextAlignment(TEXT_ALIGN_CENTER);
      display.setFont(Roboto_Bold_16);
      display.drawString(62, 0, "ETHEREUM");
      display.setFont(DejaVu_Sans_14);
      display.drawString(62, 30, eth);
      display.display();
      delay(5000);

      i++;
    }
  }
}
