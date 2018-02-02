#include <M5Stack.h>
#include "Free_Fonts.h"

M5Gauge gauge;
M5ProgressBar pb;
M5BarGraph bar;
M5LineGraph lg;

float myValue, prev0 = 62.0, prev1 = 48.0;
int barHeight = 100, barWidth = 20;
uint16_t lineCount = 0;

void defineBounds() {
  gauge.setBounds(200, 125, 80, 80);
  bar.setBounds(290, 125, barWidth, barHeight);
  pb.setBounds(200, 210, 80, 22);
  lg.setBounds(0, 0, 320, 120);
  lg.setLineColor(0, TFT_RED);
  lg.setLineColor(1, TFT_BLUE);
  lg.setAutoClear(true);
  lg.setLineCount(2);
  myValue = 0.0;
  gauge.setValue(0.0);
  bar.setValue(0.0);
  pb.setValue(0.0);
}

void setup() {
  Serial.begin(115200);
  M5.begin();
  // Lcd display
  M5.Lcd.setTextColor(TFT_BLACK, TFT_WHITE);
  M5.Lcd.fillScreen(TFT_WHITE);
  pb.setColor(BACKGROUND, TFT_WHITE);
  pb.setColor(FRAME, TFT_BLACK);
  pb.setColor(CONTENT, TFT_ORANGE);
  pb.setColor(FOREGROUND, 0x02DF); // Inverse of TFT_ORANGE
  // see http://www.rinkydinkelectronics.com/calc_rgb565.php
  pb.setFont(FSSB9);
  bar.setFont(FSSB9);
  gauge.setFont(FF33);
  gauge.setColor(FOREGROUND, TFT_LIGHTGREY);
  bar.setColor(FOREGROUND, TFT_BLUE);
  bar.setColor(ACTIVATED, TFT_BLUE);
  bar.setColor(BACKGROUND, TFT_WHITE);
  bar.setColor(FRAME, TFT_BLACK);
  bar.setColor(CONTENT, TFT_ORANGE);

  defineBounds();
  gauge.setRange(0.0F, 3.3F);
  pb.setRange(0.0F, 3.3F);
  bar.setRange(0.0F, 3.3F);
  lg.setRange(0, 330);
  gauge.draw();
  pb.draw();
  bar.draw();
  lg.draw();
  randomSeed(analogRead(0));
  prev0 = random(330);
  prev1 = random(330);
}

void loop() {
  myValue += 0.1;
  lineCount++;
  if (myValue > 3.3) {
    gauge.undraw();
    pb.undraw();
    bar.undraw();
    myValue = 0.0;
    gauge.setValue(0.0);
    bar.setValue(0.0);
    pb.setValue(0.0);
    gauge.draw();
    pb.draw();
    bar.draw();
  }
  if (lineCount > 318) {
    lg.clear();
    lg.undraw();
    lg.draw();
    lineCount = 0;
    prev0 = random(330);
    prev1 = random(330);
  }
  gauge.setValue(myValue);
  gauge.draw();
  pb.setValue(myValue);
  pb.draw();
  bar.setValue(myValue);
  bar.draw();
  float values[2];
  if (lineCount % 30 == 0) {
    values[0] = random(prev0 * .75, prev0 * 1.25);
    values[1] = random(prev1 * .75, prev1 * 1.25);
  } else {
    values[0] = random(prev0 * .95, prev0 * 1.05);
    values[1] = random(prev1 * .95, prev1 * 1.05);
  }
  lg.addValues(values);
  Serial.print("Adding values: ");
  Serial.print(values[0]);
  Serial.print(", ");
  Serial.println(values[1]);
  prev0 = values[0];
  prev1 = values[1];
  delay(100);
}
