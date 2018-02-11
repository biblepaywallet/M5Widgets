#ifndef _M5TOUCH_H_
#define _M5TOUCH_H_

#include "M5Timer.h"

class M5Touch {
  public:
    M5Touch();
    void setTouchFunctionA(void (*upFunction)(void));
    void setTouchFunctionB(void (*upFunction)(void));
    void setTouchFunctionC(void (*upFunction)(void));
    void checkOnButtons(void);
    void drawMenu(String, String, String, String);
    void eraseMenu(void);
    bool visible(void);
    char getFeedback(void);
    void increaseBacklight(uint8_t);
    void decreaseBacklight(uint8_t);
    void logAnswer(const char *, const char *);
    void readRect(uint32_t, uint32_t, uint32_t, uint32_t, uint16_t *);

    M5Timer tm;

  private:
    void (*_touchAFunction)(void);
    void (*_touchBFunction)(void);
    void (*_touchCFunction)(void);

    uint16_t sys_menucolor, sys_windowcolor, sys_menutextcolor;
    uint16_t save0[320*28], save1[60*28], save2[60*28], save3[60*28];
    bool menuDisplayed;
    uint8_t brightness;
};
#endif
