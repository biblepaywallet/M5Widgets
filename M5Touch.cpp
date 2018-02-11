#include "M5Touch.h"
#include "M5Stack.h"

M5Touch::M5Touch() {
  sys_menucolor = TFT_DARKGREY;
  sys_windowcolor = TFT_LIGHTGREY;
  sys_menutextcolor = TFT_WHITE;
  menuDisplayed = false;
  M5.Lcd.setBrightness(100);
  this->brightness = 100;
  tm.setInterval(200, std::bind(&M5Touch::checkOnButtons, this));
  tm.run();
}

void M5Touch::setTouchFunctionA(void (*upFunction)(void)) {
  _touchAFunction = upFunction;
}

void M5Touch::setTouchFunctionB(void (*upFunction)(void)) {
  _touchBFunction = upFunction;
}

void M5Touch::setTouchFunctionC(void (*upFunction)(void)) {
  _touchCFunction = upFunction;
}

void M5Touch::checkOnButtons() {
  M5.update();
  if (M5.BtnA.wasPressed()) _touchAFunction();
  if (M5.BtnB.wasPressed()) _touchBFunction();
  if (M5.BtnC.wasPressed()) _touchCFunction();
}

bool M5Touch::visible() {
  return (this->menuDisplayed);
}

void M5Touch::logAnswer(const char *who, const char *what) {
  Serial.print("Error in ["); Serial.print(who); Serial.print("]: "); Serial.println(what);
}

void M5Touch::readRect(uint32_t px, uint32_t py, uint32_t w, uint32_t h, uint16_t *data) {
  if (w == 0) {
    logAnswer("M5Touch::readRect", "width = 0");
    return;
  }
  if (h == 0) {
    logAnswer("M5Touch::readRect", "height = 0");
    return;
  }
  if (px + w > 320) {
    logAnswer("M5Touch::readRect", "x + width out of bounds");
    return;
  }
  if (py + h > 240) {
    logAnswer("M5Touch::readRect", "y + height out of bounds");
    return;
  }
  Serial.print("readRect["); Serial.print(px); Serial.print("::"); Serial.print(py);
  Serial.print("]["); Serial.print(w); Serial.print("::"); Serial.print(h); Serial.print("]\n");
  for (uint16_t j = 0; j < h; j++) {
    for (uint16_t i = 0; i < w; i++) {
      uint16_t position = j * w + i;
      data[position] = M5.Lcd.readPixel(px + i, py + j);
    }
  }
}

void M5Touch::drawMenu(String inmenutxt, String inbtnatxt, String inbtnbtxt, String inbtnctxt) {
  if (menuDisplayed) {
    Serial.println("No need to display the menu...");
    return;
  }
  // Save top bar and button areas in the save0/1/2/3 buffers for later redrawing
  // Uses less memory than saving two bars of 320 x 28
  // readRect(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h, uint16_t *data);
  readRect(0, 0, 320, 28, this->save0);
  for (uint8_t j = 0; j < 28; j++) {
    Serial.print("\n[" + String(j) + "]: ");
    for (uint8_t i = 0; i < 40; i++) {
      Serial.write('['); Serial.print(this->save0[j * 320 + i], HEX); Serial.write(']');
    }
  } Serial.write('\n');
  readRect(31, 240 - 28, 60, 28, this->save1);
  for (uint8_t j = 0; j < 28; j++) {
    Serial.print("\n[" + String(j) + "]: ");
    for (uint8_t i = 0; i < 16; i++) {
      Serial.write('['); Serial.print(this->save1[j * 60 + i], HEX); Serial.write(']');
    }
  } Serial.write('\n');
  readRect(126, 240 - 28, 60, 28, this->save2);
  for (uint8_t j = 0; j < 28; j++) {
    Serial.print("\n[" + String(j) + "]: ");
    for (uint8_t i = 0; i < 16; i++) {
      Serial.write('['); Serial.print(this->save2[j * 60 + i], HEX); Serial.write(']');
    }
  } Serial.write('\n');
  readRect(221, 240 - 28, 60, 28, this->save3);
  for (uint8_t j = 0; j < 28; j++) {
    Serial.print("\n[" + String(j) + "]: ");
    for (uint8_t i = 0; i < 16; i++) {
      Serial.write('['); Serial.print(this->save3[j * 60 + i], HEX); Serial.write(']');
    }
  } Serial.write('\n');

  //M5.Lcd.fillRect(0, 240 - 28, 320, 28, sys_windowcolor);
  M5.Lcd.fillRoundRect(31, 240 - 28, 60, 28, 3, sys_menucolor); // BtnA
  M5.Lcd.fillRoundRect(126, 240 - 28, 60, 28, 3, sys_menucolor); // BtnB
  M5.Lcd.fillRoundRect(221, 240 - 28, 60, 28, 3, sys_menucolor); // BtnC
  M5.Lcd.fillRect(0, 0, 320, 28, sys_menucolor);
  M5.Lcd.setTextColor(sys_menutextcolor);
  M5.Lcd.drawCentreString(inmenutxt, 320 / 2, 6, 2);
  M5.Lcd.drawCentreString(inbtnatxt, 31 + 30, 240 - 28 + 6, 2);
  M5.Lcd.drawCentreString(inbtnbtxt, 126 + 30, 240 - 28 + 6, 2);
  M5.Lcd.drawCentreString(inbtnctxt, 221 + 30, 240 - 28 + 6, 2);
  menuDisplayed = true;
}

void M5Touch::eraseMenu() {
  if (!menuDisplayed) {
    Serial.println("No need to erase the menu...");
    return;
  }
  M5.Lcd.pushRect(0, 0, 320, 28, this->save0);
  M5.Lcd.pushRect(31, 240 - 28, 60, 28, this->save1);
  M5.Lcd.pushRect(126, 240 - 28, 60, 28, this->save2);
  M5.Lcd.pushRect(221, 240 - 28, 60, 28, this->save3);
  menuDisplayed = false;
}

void M5Touch::increaseBacklight(uint8_t howMuch) {
  if (this->brightness + howMuch > 99) howMuch = 100 - this->brightness;
  this->brightness += howMuch;
  M5.lcd.setBrightness(this->brightness);
}

void M5Touch::decreaseBacklight(uint8_t howMuch) {
  if (this->brightness < howMuch) howMuch = this->brightness;
  this->brightness -= howMuch;
  M5.lcd.setBrightness(this->brightness);
}

char M5Touch::getFeedback(void) {
  while (1) {
    M5.update();
    if (M5.BtnA.wasPressed()) return ('A');
    if (M5.BtnB.wasPressed()) return ('B');
    if (M5.BtnC.wasPressed()) return ('C');
  }
}
