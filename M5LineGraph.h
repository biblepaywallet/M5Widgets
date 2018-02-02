#include "M5Widget.h"

#ifndef _M5WIDGET_LINE_GRAPH_H_
#define _M5WIDGET_LINE_GRAPH_H_

class M5LineGraph : public M5Widget {
 public:
  M5LineGraph() : _pos(0), autoClearDisabled(false) {}
  void setLineCount(int nrLines);
  const void setLineColor(unsigned char lineIdx, uint16_t color) { _lineColors[lineIdx]=color; }
  void setRange(float minimum, float maximum);
  const uint16_t lineColor(unsigned char lineIdx) { return _lineColors[lineIdx]; }
  const unsigned int position(void) { return _pos; }
  void addValues(const float* values);
  void addValue(float value);
  void setAutoClear(bool autoClear) { autoClearDisabled = !autoClear; }
  void clear(void);
  virtual void update(void);
  virtual void draw(void);
 private:
  unsigned char _dim;
  float _min, _max;
  int _pos;
  bool autoClearDisabled;
  DataBuffer _lastValues;
  uint16_t _lineColors[256];
};

#endif
