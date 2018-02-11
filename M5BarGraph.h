#ifndef _M5BARGRAPH_H_
#define _M5BARGRAPH_H_

#include "M5Widget.h"

class M5BarGraph : public M5Widget {
 public:
  void setRange(float minimum, float maximum);
  void setBaseValue(float baseValue);
  void setValue(float value);
  float value() const { return _valueReq; }

  virtual void update(void);
  virtual void draw(void);
 private:
  void drawBar(float val_a, float val_b, uint16_t color);
  float _minimum, _maximum, _value, _valueReq, _baseVal;
};

#endif