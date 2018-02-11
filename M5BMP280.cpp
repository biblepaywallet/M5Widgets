#include "M5BMP280.h"

M5BMP280::M5BMP280() {
  if (!sensor.init()) {
    inited(false);
    setError(1);
    Serial.println("BMP280 init error!");
  }
  inited(true);
  setError(0);
  _seaLevel = 1000.0;
  setInterval(0);
}

M5BMP280::~M5BMP280() {
}

uint8_t M5BMP280::dataPoints() {
  return 4;
}

float M5BMP280::dataPoint(uint8_t num) {
  if (num > 3) return -1.111111;
  return _values[num];
}

String M5BMP280::dataPointName(uint8_t num) {
  if (num > 3) return "?";
  return _valueNames[num];
}

void M5BMP280::updateValues() {
  if (!isInited()) {
    setError(2);
    return;
  }
  _values[0] = sensor.getTemperature();
  _values[1] = sensor.getPressure() / 100.0;
  _values[2] = sensor.calcAltitude(_values[1] * 100.0);
  _values[3] = 44330.0 * (1.0 - pow(_values[1] / _seaLevel, 0.1903));
}

void M5BMP280::setSeaLevel(float SL) {
  _seaLevel = SL;
}

char * M5BMP280::name() {
  return "BMP280";
}
