#include "M5StaticMenu.h"

M5StaticMenu::M5StaticMenu() {

}

void M5StaticMenu::setDrawHeader(void (*myFunction)(void)) {
  _drawHeader=myFunction;
}

void M5StaticMenu::setDrawFooter(void (*myFunction)(void)) {
  _drawFooter=myFunction;
}

void M5StaticMenu::setDrawCenter(void (*myFunction)(void)) {
  _drawCenter=myFunction;
}

void M5StaticMenu::attachTouch(M5Touch t) {
  _touch=t;
}

void M5StaticMenu::update() {
  _drawCenter();
  _touch.tm.run();
}

void M5StaticMenu::draw() {
  _drawHeader();
  _drawFooter();
  _drawCenter();
}

