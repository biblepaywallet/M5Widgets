#include <M5Stack.h>
#include "Free_Fonts.h"
#include "Seeed_BMP280.h"

M5Touch touch;

M5Gauge tempGauge;
M5ProgressBar tempPB;
M5BarGraph bar;
M5LineGraph lg;
M5QRCode qr;

float myValue0, myValue1;
int barHeight = 100, barWidth = 20;
uint16_t lineCount = 0;
BMP280 bmp280;
double t0, t1, interval = 10000;

void setup() {
  M5.begin();
  Serial.begin(115200);
  delay(2000);
  Serial.println("\n\n\n\nM5.begin()");
  // Lcd display
  M5.Lcd.setTextColor(TFT_BLACK, TFT_WHITE);
  M5.Lcd.fillScreen(TFT_WHITE);
  Serial.print(F("BMP280 init "));
  if (!bmp280.init()) {
    Serial.println("Device error!");
    while (1);
  }
  Serial.println(F("succeeded."));

  bar.setBounds(290, 125, barWidth, barHeight);
  bar.setColor(ACTIVATED, TFT_BLUE);
  bar.setColor(BACKGROUND, TFT_WHITE);
  bar.setColor(CONTENT, TFT_ORANGE);
  bar.setColor(FOREGROUND, TFT_BLUE);
  bar.setColor(FRAME, TFT_BLACK);
  bar.setFont(FSSB9);
  bar.setRange(600, 1500);

  lg.setAutoClear(true);
  lg.setBounds(0, 0, 320, 120);
  lg.setLineColor(0, TFT_BLUE);
  lg.setLineCount(1);

  tempGauge.setBounds(200, 125, 80, 80);
  tempGauge.setColor(FOREGROUND, TFT_LIGHTGREY);
  tempGauge.setFont(FF33);

  tempPB.setBounds(200, 210, 80, 22);
  tempPB.setColor(BACKGROUND, TFT_WHITE);
  tempPB.setColor(CONTENT, TFT_ORANGE);
  uint16_t c = calculateRGB565(0xFF, 0xA5, 0x00);
  Serial.print("(RGB) 0xFFA500 = (565) 0x");
  Serial.println(c);
  c = calculateRGB565(0x00, 0x5A, 0xFF);
  Serial.print("(RGB) 0x005AFF = (565) 0x");
  Serial.println(c);
  tempPB.setColor(FOREGROUND, c);
  // Inverse of TFT_ORANGE
  // adapted from http://www.rinkydinkelectronics.com/calc_rgb565.php
  tempPB.setColor(FRAME, TFT_BLACK);
  tempPB.setFont(FSSB9);

  myValue0 = bmp280.getTemperature();
  tempGauge.setRange(myValue0 / 2.0, myValue0 * 2);
  tempPB.setRange(myValue0 / 2.0, myValue0 * 2);
  lg.setRange(myValue0 / 2.0, myValue0 * 2);

  tempPB.setValue(myValue0);
  tempGauge.setValue(myValue0);
  bar.setValue(bmp280.getPressure() / 100.0);

  tempGauge.draw();
  tempPB.draw();
  bar.draw();
  lg.draw();

  touch.setTouchFunctionA(btnAFunc0);
  touch.setTouchFunctionB(btnBFunc0);
  touch.setTouchFunctionC(btnCFunc0);

  qr.yOffset = 135;
  qr.xOffset = 10;
  // Let's try the default text.
  qr.draw();
  delay(2000);
  String s = String(myValue0) + "°C";
  qr.erase();
  qr.setValue(s);
  qr.draw();

  t0 = millis();
}

void loop() {
  touch.tm.run();
  t1 = millis() - t0;
  if (t1 < interval) return;
  myValue0 = bmp280.getTemperature();
  myValue1 = bmp280.getPressure() / 100.0;
  lineCount++;
  if (lineCount > 318) {
    lg.clear();
    lg.undraw();
    lg.draw();
    lineCount = 0;
  }
  tempGauge.setValue(myValue0);
  tempGauge.draw();
  tempPB.setValue(myValue0);
  tempPB.draw();
  bar.setValue(myValue1);
  bar.draw();
  lg.addValue(myValue0);
  lg.draw();
  String s = "Temp: " + String(myValue0) + "C. Pressure: " + String(myValue1 / 100.0) + " HPa";
  qr.erase();
  qr.setValue(s);
  qr.draw();
  t0 = millis();
}

static void btnAFunc0() {
  Serial.println("Button A was pressed");
  if (touch.visible()) {
    touch.increaseBacklight(10);
    Serial.println("increase backlight");
  }
}

static void btnBFunc0() {
  Serial.println("Button B was pressed");
  if (touch.visible()) touch.eraseMenu();
  else {
    touch.drawMenu(F("BACKLIGHT"), F("+"), F("OK"), F("-"));
    while (touch.visible()) {
      // Waiting for the user to do something else
      touch.tm.run();
    }
  }
}

static void btnCFunc0() {
  Serial.println("Button C was pressed");
  if (touch.visible()) {
    touch.decreaseBacklight(10);
    Serial.println("decrease backlight");
  }
}


