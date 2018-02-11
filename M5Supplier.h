#include <Arduino.h>

#ifndef _M5SUPPLIER_H_
#define _M5SUPPLIER_H_

class M5Supplier {
  public:
    virtual uint8_t dataPoints(void);
    virtual float dataPoint(uint8_t);
    virtual String dataPointName(uint8_t);
    virtual void updateValues(void);
    virtual char * name(void);
    void setInterval(unsigned long);
    unsigned long getInterval(void);
    void setLastCheck(unsigned long);
    unsigned long getLastCheck(void);
    bool isInited(void);
    void inited(bool);
    uint8_t getError(void);
    void setError(uint8_t);

  private:
    bool _inited;
    uint8_t _error;
    unsigned long _interval, _lastCheck;
};

#endif