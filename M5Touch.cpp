#include "M5Stack.h"
#include "M5Touch.h"

M5Touch::M5Touch() {
  sys_menucolor=TFT_BLUE;
  sys_windowcolor=TFT_LIGHTGREY;
  sys_menutextcolor=TFT_WHITE;
  menuDisplayed=false;
  M5.Lcd.setBrightness(100);
  this->brightness=100;
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
  if(M5.BtnA.wasPressed()) _touchAFunction();
  if(M5.BtnB.wasPressed()) _touchBFunction();
  if(M5.BtnC.wasPressed()) _touchCFunction();
}

bool M5Touch::visible() {
  return (this->menuDisplayed);
}

void M5Touch::drawMenu(String inmenutxt, String inbtnatxt, String inbtnbtxt, String inbtnctxt) {
  if(menuDisplayed) return;
  // Save both area in the save0/1 buffers for later redrawing
  // readRect(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h, uint16_t *data);
  M5.Lcd.readRect(0, 0, 320, 28, this->save0);
  M5.Lcd.readRect(0, 240 - 28, 320, 28, this->save1);

  M5.Lcd.fillRect(0, 240 - 28, 320, 28, sys_windowcolor);
  M5.Lcd.fillRoundRect(31, 240 - 28, 60, 28, 3, sys_menucolor); // BtnA
  M5.Lcd.fillRoundRect(126, 240 - 28, 60, 28, 3, sys_menucolor); // BtnB
  M5.Lcd.fillRoundRect(221, 240 - 28, 60, 28, 3, sys_menucolor); // BtnC
  M5.Lcd.fillRoundRect(0, 0, 320, 28, 3, sys_menucolor);
  M5.Lcd.setTextColor(sys_menutextcolor);
  M5.Lcd.drawCentreString(inmenutxt, 320 / 2, 6, 2);
  M5.Lcd.drawCentreString(inbtnatxt, 31 + 30, 240 - 28 + 6, 2);
  M5.Lcd.drawCentreString(inbtnbtxt, 126 + 30, 240 - 28 + 6, 2);
  M5.Lcd.drawCentreString(inbtnctxt, 221 + 30, 240 - 28 + 6, 2);
  menuDisplayed=true;
}

void M5Touch::eraseMenu() {
  if(!menuDisplayed) return;
  M5.Lcd.pushRect(0, 0, 320, 28, this->save0);
  M5.Lcd.pushRect(0, 240 - 28, 320, 28, this->save1);
  menuDisplayed=false;
}

void M5Touch::increaseBacklight(uint8_t howmuch) {
  if(this->brightness+howmuch>99) howmuch=100-this->brightness;
  this->brightness+=howmuch;
  M5.lcd.setBrightness(this->brightness);
}

void M5Touch::decreaseBacklight(uint8_t howmuch) {
  if(this->brightness<howmuch) howmuch=this->brightness;
  this->brightness-=howmuch;
  M5.lcd.setBrightness(this->brightness);
}
