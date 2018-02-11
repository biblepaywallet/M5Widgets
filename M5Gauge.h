#ifndef _M5GAUGE_H_
#define _M5GAUGE_H_

#include "M5Widget.h"

class M5Gauge : public M5Widget {
 public:
  void setRange(float minimum, float maximum);
  void setValue(float value);
  float value() const { return _valueReq; }
  virtual void update(void);
  virtual void draw(void);
 private:
  void drawPointer(uint16_t color, bool fillBg = false);
  void drawLineAngle(int x, int y, int r1, int r2, float angle, uint16_t color);
  void drawTickLine(int r1, int r2, float ang, uint16_t color);
  float _minimum, _maximum, _value, _valueReq;
};
#endif