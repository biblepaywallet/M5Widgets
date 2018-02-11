#include "M5Supplier.h"

#ifndef _M5BMP280_H_
#define _M5BMP280_H_
#include "Seeed_BMP280.h"

class M5BMP280 : public M5Supplier {
  public:
    M5BMP280();
    ~M5BMP280();
    void setSeaLevel(float);
    virtual uint8_t dataPoints(void);
    virtual float dataPoint(uint8_t);
    virtual String dataPointName(uint8_t);
    virtual void updateValues(void);
    virtual char * name(void);

  private:
    float _values[4], _seaLevel;
    BMP280 sensor;
    String _valueNames[4] = {"temp", "pressure", "altitude", "computed altitude"};
};

#endif
