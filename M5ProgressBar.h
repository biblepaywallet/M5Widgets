#include "M5Widget.h"

#ifndef _M5PROGRESSBAR_H_
#define _M5PROGRESSBAR_H_

class M5ProgressBar : public M5Widget {
 public:
  /// Sets the minimum and maximum value of the gauge
  void setRange(float minimum, float maximum);
  /// Sets the value displayed by the gauge
  void setValue(float value);
  /// Gets the value displayed by the gauge
  float value() const { return _valueReq; }

  virtual void update(void);
  virtual void draw(void);
 private:
  void drawPointer();
  float _minimum, _maximum, _value, _valueReq;
};
#endif