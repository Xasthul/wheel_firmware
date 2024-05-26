#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define INT2POINTER(a) ((char *)(intptr_t)(a))

void drawCentreString(const char *buf, uint8_t textSize, int cursorX, int cursorY)
{
  int16_t x1, y1;
  uint16_t w, h;

  display.setTextSize(textSize); // 6x8
  display.getTextBounds(buf, cursorX, cursorY, &x1, &y1, &w, &h);
  display.setCursor((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2);
  display.print(buf);
}

void setup()
{
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
}

void loop()
{
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  drawCentreString("200", 5, 0, 0);

  display.display();
}