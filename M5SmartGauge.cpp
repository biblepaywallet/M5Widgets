#include "M5SmartGauge.h"

M5SmartGauge::M5SmartGauge() {
  _index = 0;
}

void M5SmartGauge::attach(M5BMP280 sup) {
  this->wd = sup;
  Serial.print(sup.name());
  Serial.print(" attached to M5SmartGauge.");
}

void M5SmartGauge::setDataIndex(uint8_t ix) {
  _index = ix;
}

void M5SmartGauge::setRange(float minimum, float maximum) {
  _minimum = minimum;
  _maximum = maximum;
  _value = _valueReq;
  invalidate();
}

void M5SmartGauge::update() {
  unsigned long iv = this->wd.getInterval();
  Serial.println("getInterval() = "+String(iv));
  if (iv > 0) {
    unsigned long t1 = millis() - this->wd.getLastCheck();
    if (t1 < iv) return;
  } //else Serial.println("time's up, updating!");
  this->wd.updateValues();
  _valueReq = this->wd.dataPoint(_index);
  if (_value == _valueReq) {
    return;
  }
  // Draw changes in the needle pointer (avoids having to draw the entire background)
  drawPointer(color(FOREGROUND));
  _value = _valueReq;
  drawPointer(color(CONTENT));
  M5.Lcd.drawCircle(x + width / 2, y + width / 2, width * 0.5 - 1, color(CONTENT));
  if (iv > 0) this->wd.setLastCheck(millis());
}

void M5SmartGauge::draw() {
  // Draw the gauge background circle
  int radius = width * 0.5;
  M5.Lcd.fillCircle(x + width / 2, y + width / 2, radius, color(FRAME));
  M5.Lcd.fillCircle(x + width / 2, y + width / 2, radius - 1, color(FOREGROUND));
  // Draw the pointer and background of value label field
  _value = _valueReq;
  drawPointer(color(CONTENT));
  // Draw the tick lines
  int tickCount = 11;
  for (int i = 0; i < tickCount; i++) {
    drawTickLine(radius - 2, radius - 8, (float) i /  (float) (tickCount - 1), color(CONTENT));
  }
  M5.Lcd.drawCircle(x + width / 2, y + width / 2, radius - 1, color(CONTENT));
  M5.Lcd.setFont(this->myFont);
  String s = this->wd.dataPointName(_index);
  uint16_t tw=M5.Lcd.textWidth(s);
  uint16_t px = (x + width / 2) - (tw / 2);
  M5.Lcd.fillRect(px - 4, y + height + 6, tw + 8, M5.Lcd.fontHeight(1)+4, this->color(FOREGROUND));
  M5.Lcd.setTextColor(this->color(BACKGROUND), this->color(FOREGROUND));
  M5.Lcd.drawString(s, px, y + height + 10, 1);
}

void M5SmartGauge::drawLineAngle(int x, int y, int r1, int r2, float angle, uint16_t color) {
  float a_sin = sin(angle);
  float a_cos = cos(angle);
  M5.Lcd.drawLine(x + r1 * a_cos, y + r1 * a_sin, x + r2 * a_cos, y + r2 * a_sin, color);
}

void M5SmartGauge::drawPointer(uint16_t color, bool fillBg) {
  // Draw the line pointer
  float ang = (float) (_value - _minimum) / (float) (_maximum - _minimum);
  drawTickLine(0, 0.5 * width - 9, ang, color);
  // Draw the text
  int txt_h = 0.162 * width + (height - width);
  int txt_w = 0.73 * width + 2;
  int txt_x = x + (width - txt_w) / 2 + 1;
  int txt_y = y + height - txt_h + 1;
  if (fillBg) {
    M5.Lcd.fillRect(txt_x, txt_y, txt_w, txt_h, this->color(FOREGROUND));
    M5.Lcd.drawRect(txt_x, txt_y, txt_w, txt_h, this->color(FRAME));
    M5.Lcd.drawRect(txt_x + 1, txt_y, txt_w - 2, txt_h - 1, this->color(CONTENT));
  }
  char text[8];
  dtostrf(_value, 4, 2, text);
  M5.Lcd.setTextColor(this->color(FOREGROUND), this->color(BACKGROUND));
  drawStringMiddle(txt_x + 2, txt_y + 1, txt_w - 4, txt_h - 2, text, this->myFont, this->color(BACKGROUND), this->color(FOREGROUND));
}

void M5SmartGauge::drawTickLine(int r1, int r2, float ang, uint16_t color) {
  drawLineAngle(x + 0.5 * width, y + 0.5 * width, r1, r2, PI * (1.5 * ang - 1.25), color);
}
