#include "M5QRCode.h"

M5QRCode::M5QRCode() {
  _version = 6;
  _thickness = 2;
  _center = false;
  _serial = false;
  _isDrawn = false;
  _text = "Welcome to M5Wdigets";
  xOffset = 0;
  yOffset = 0;
}

void M5QRCode::setValue(char *text) {
  _text = text;
}

void M5QRCode::setValue(const String &s) {
  int16_t len = s.length() + 2;
  char buf[len];
  s.toCharArray(buf, len);
  setValue(buf);
}

void M5QRCode::erase() {
  if(!_isDrawn) return;
  M5.Lcd.fillRect(xOffset, yOffset, _qrcode.size*_thickness, _qrcode.size*_thickness, color(BACKGROUND));
  _isDrawn = false;
}

void M5QRCode::update() {
  draw();
}

void M5QRCode::draw() {
  uint8_t qrcodeData[qrcode_getBufferSize(_version)];
  qrcode_initText(&_qrcode, qrcodeData, _version, 0, _text);
  M5.Lcd.fillRect(xOffset, yOffset, _qrcode.size*_thickness, _qrcode.size*_thickness, TFT_WHITE);
  uint16_t lineLength = _qrcode.size * _thickness;
  if(_center) {
    xOffset = (320 - (lineLength)) / 2;
    yOffset = (240 - (lineLength)) / 2;
  }
  if(_serial) Serial.println(_text);
  if(_serial) "===================================\n";
  for (uint8_t y = 0; y < _qrcode.size; y++) {
    // Left quiet zone
    if(_serial) Serial.print("        ");
    // Each horizontal module
    for (uint8_t x = 0; x < _qrcode.size; x++) {
      // Print each module (UTF-8 \u2588 is a solid block)
      bool q = qrcode_getModule(&_qrcode, x, y);
      if(_serial) Serial.print(q ? "\u2588\u2588" : "  ");
      if (q) {
        M5.Lcd.fillRect(x * _thickness + xOffset, y * _thickness + yOffset, _thickness, _thickness, TFT_BLACK);
      }
    }
    if(_serial) Serial.write('\n');
  }
  // Bottom quiet zone
  if(_serial) Serial.print("\n\n\n\n");
  _isDrawn = true;
}

void M5QRCode::centerDisplay(bool c = false) {
  _center = c;
}

void M5QRCode::consoleDisplay(bool c = false) {
  _serial = c;
}

uint8_t M5QRCode::version() {
  return _version;
}

void M5QRCode::setVersion(uint8_t v) {
  _version = v;
}
