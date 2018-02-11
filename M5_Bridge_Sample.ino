#include <M5Stack.h>
#include "Free_Fonts.h"

#define HEADERHEIGHT 30
#define FOOTERHEIGHT 28

M5Touch touch;
M5StaticMenu sm;
M5Bridge m5bridge;
uint16_t centerTop, centerHeight, centerDrawTop;
String cenTerTitle = "Bridge";
uint32_t leftChoices[] = { 9600, 19200, 57600, 115200 };
uint32_t rightChoices[] = { 433, 434, 435, 436 };
uint8_t nRC = 4, nLC = 4; // number of choices
uint8_t lChoice = 3, rChoice = 0;
uint32_t speed0 = 115200, myBand = 433E6;

void setupBridge() {
  m5bridge.setIOFunction(tSERIAL0, tLoRa);
  m5bridge.setLoRaBand(myBand);
  m5bridge.setLoRaUUID("This is M5Stack!");
}

void setup() {
  Serial.begin(speed0);
  Serial.println("\n\n\nStart...");
  M5.begin();
  Serial.println("\n\n\n\nM5.begin()");
  centerTop = HEADERHEIGHT + 7;
  centerHeight = 240 - (HEADERHEIGHT + FOOTERHEIGHT);
  centerDrawTop = centerTop + HEADERHEIGHT;
  // Lcd display
  M5.Lcd.setTextColor(TFT_BLACK, TFT_WHITE);
  M5.Lcd.fillScreen(TFT_BLACK);
  sm.setDrawHeader(drawHeader);
  sm.setDrawCenter(drawCenter);
  sm.setDrawFooter(drawMainFooter);
  sm.draw();
  setupBridge();
}

void loop() {
  if (m5bridge.isActive()) m5bridge.run();
  touch.tm.run();
}

void drawPill(uint16_t c) {
  M5.Lcd.fillRoundRect(290, 2, 12, HEADERHEIGHT - 4, 4, c);
  M5.Lcd.drawRoundRect(290, 2, 12, HEADERHEIGHT - 4, 4, TFT_WHITE);
  M5.Lcd.drawRoundRect(291, 3, 10, HEADERHEIGHT - 6, 4, TFT_BLACK);
}

void drawHeader() {
  M5.Lcd.fillRect(0, 0, 320, HEADERHEIGHT, TFT_NAVY);
  M5.Lcd.setFont(FF21);
  M5.Lcd.setTextColor(TFT_CYAN);
  M5.Lcd.drawString("BRIDGE", 1, HEADERHEIGHT - 14, 1);
  M5.Lcd.setFont(FF17);
  M5.Lcd.drawString("multi", 1, 0, 1);
  drawPill(TFT_RED);
}

void drawCenter() {
  M5.Lcd.fillRoundRect(3, centerTop, 314, centerHeight - 14, 4, TFT_WHITE);
  M5.Lcd.fillRoundRect(3, centerTop, 314, HEADERHEIGHT, 4, TFT_CYAN);
  M5.Lcd.fillRect(3, centerTop + HEADERHEIGHT - 4, 314, 4, TFT_WHITE);
  M5.Lcd.setFont(FF26);
  uint16_t tw = M5.Lcd.textWidth(cenTerTitle);
  uint16_t px = (M5.Lcd.width() / 2) - (tw / 2);
  M5.Lcd.setTextColor(TFT_NAVY);
  M5.Lcd.drawString(cenTerTitle, px, HEADERHEIGHT + 9, 1);

  String s;
  M5.Lcd.setFont(FF22);
  M5.Lcd.setTextColor(TFT_OLIVE);
  M5.Lcd.drawString(F("Pipe 0"), 16, centerDrawTop + 6, 1);
  s = "Pipe 1";
  tw = M5.Lcd.textWidth(s, 1);
  M5.Lcd.drawString(s, 320 - tw - 40, centerDrawTop + 6, 1);
  M5.Lcd.setFont(FF27);
  s = String(leftChoices[lChoice]);
  tw = M5.Lcd.textWidth(s, 1);
  M5.Lcd.drawString(s, 10, centerDrawTop + 60 , 1);
  M5.Lcd.drawString(s, 11, centerDrawTop + 61 , 1);

  M5.Lcd.setTextColor(TFT_LIGHTGREY);
  uint8_t ix = lChoice + 1;
  if (ix == nLC) ix = 0;
  M5.Lcd.setFont(FF26);
  s = String(leftChoices[ix]);
  uint16_t tw1 = M5.Lcd.textWidth(s, 1);
  M5.Lcd.drawString(s, 10 + (tw - tw1) / 2, centerDrawTop + 90 , 1);
  M5.Lcd.drawString(s, 11 + (tw - tw1) / 2, centerDrawTop + 91 , 1);
  if (lChoice == 0) ix = nLC - 1;
  else ix = lChoice - 1;
  s = String(leftChoices[ix]);
  tw1 = M5.Lcd.textWidth(s, 1);
  M5.Lcd.drawString(s, 10 + (tw - tw1) / 2, centerDrawTop + 40 , 1);
  M5.Lcd.drawString(s, 11 + (tw - tw1) / 2, centerDrawTop + 41 , 1);

  M5.Lcd.setFont(FF27);
  M5.Lcd.setTextColor(TFT_OLIVE);
  s = String(rightChoices[rChoice]) + "MHz";
  tw = M5.Lcd.textWidth(s, 1);
  M5.Lcd.drawString(s, 320 - tw - 16, centerDrawTop + 60 , 1);
  M5.Lcd.drawString(s, 320 - tw - 15, centerDrawTop + 61 , 1);

  M5.Lcd.setTextColor(TFT_LIGHTGREY);
  ix = rChoice + 1;
  if (ix == nRC) ix = 0;
  M5.Lcd.setFont(FF26);
  s = String(rightChoices[ix]);
  tw1 = M5.Lcd.textWidth(s, 1);
  M5.Lcd.drawString(s, 320 - tw - 16 + (tw - tw1) / 2, centerDrawTop + 90 , 1);
  M5.Lcd.drawString(s, 320 - tw - 15 + (tw - tw1) / 2, centerDrawTop + 91 , 1);
  if (rChoice == 0) ix = nRC - 1;
  else ix = rChoice - 1;
  s = String(rightChoices[ix]);
  tw1 = M5.Lcd.textWidth(s, 1);
  M5.Lcd.drawString(s, 320 - tw - 16 + (tw - tw1) / 2, centerDrawTop + 40 , 1);
  M5.Lcd.drawString(s, 320 - tw - 15 + (tw - tw1) / 2, centerDrawTop + 41 , 1);
}

void drawMainFooter() {
  M5.Lcd.setFont(FF18);
  M5.Lcd.fillRoundRect(31, 240 - FOOTERHEIGHT, 60, FOOTERHEIGHT, 3, TFT_BLUE); // BtnA
  M5.Lcd.fillRoundRect(126, 240 - FOOTERHEIGHT, 60, FOOTERHEIGHT, 3, TFT_OLIVE); // BtnB
  M5.Lcd.fillRoundRect(221, 240 - FOOTERHEIGHT, 60, FOOTERHEIGHT, 3, TFT_DARKGREEN); // BtnC
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.drawCentreString("pipe0", 31 + 30, 240 - FOOTERHEIGHT + 6, 2);
  M5.Lcd.drawCentreString("START", 126 + 30, 240 - FOOTERHEIGHT + 6, 2);
  M5.Lcd.drawCentreString("pipe1", 221 + 30, 240 - FOOTERHEIGHT + 6, 2);
  touch.setTouchFunctionA(loopPipe0);
  touch.setTouchFunctionB(startDaMusic);
  touch.setTouchFunctionC(loopPipe1);
}

void drawBusyFooter() {
  M5.Lcd.setFont(FF18);
  M5.Lcd.fillRoundRect(31, 240 - FOOTERHEIGHT, 60, FOOTERHEIGHT, 3, TFT_BLUE); // BtnA
  M5.Lcd.fillRoundRect(126, 240 - FOOTERHEIGHT, 60, FOOTERHEIGHT, 3, TFT_OLIVE); // BtnB
  M5.Lcd.fillRoundRect(221, 240 - FOOTERHEIGHT, 60, FOOTERHEIGHT, 3, TFT_DARKGREEN); // BtnC
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.drawCentreString(" -- ", 31 + 30, 240 - FOOTERHEIGHT + 6, 2);
  M5.Lcd.drawCentreString("STOP", 126 + 30, 240 - FOOTERHEIGHT + 6, 2);
  M5.Lcd.drawCentreString(" -- ", 221 + 30, 240 - FOOTERHEIGHT + 6, 2);
  touch.setTouchFunctionA(loopPipe0);
  touch.setTouchFunctionB(stopDaMusic);
  touch.setTouchFunctionC(loopPipe1);
}

void loopPipe0() {
  if (m5bridge.isActive()) return;
  // We're busy, guys, stop first, THEN let's talk...
  lChoice += 1;
  if (lChoice == nLC) lChoice = 0;
  speed0 = leftChoices[lChoice];
  drawCenter();
}

void loopPipe1() {
  if (m5bridge.isActive()) return;
  // We're busy, guys, stop first, THEN let's talk...
  rChoice += 1;
  if (rChoice == nRC) rChoice = 0;
  myBand = rightChoices[rChoice] * 1E6;
  drawCenter();
}

void startDaMusic() {
  drawBusyFooter();
  drawPill(TFT_GREEN);
  m5bridge.start();
}

void stopDaMusic() {
  drawMainFooter();
  drawPill(TFT_RED);
  m5bridge.stop();
}
