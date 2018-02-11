#include "M5Widget.h"
#include "M5Supplier.h"
#include "M5BMP280.h"

#ifndef _M5SMARTGAUGE_H_
#define _M5SMARTGAUGE_H_

class M5SmartGauge : public M5Widget {
 public:
    M5SmartGauge();
    void attach(M5BMP280);
    void setRange(float minimum, float maximum);
    void setDataIndex(uint8_t ix);
    virtual void update(void);
    virtual void draw(void);
  private:
    void drawPointer(uint16_t color, bool fillBg = false);
    void drawLineAngle(int x, int y, int r1, int r2, float angle, uint16_t color);
    void drawTickLine(int r1, int r2, float ang, uint16_t color);
    float _minimum, _maximum, _value, _valueReq;
    uint8_t _index;
    M5BMP280 wd;
};
#endif