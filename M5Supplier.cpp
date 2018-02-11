#include "M5Supplier.h"

void M5Supplier::inited(bool x) {
  _inited = x;
}

bool M5Supplier::isInited() {
  return _inited;
}

uint8_t M5Supplier::getError() {
  return _error;
}
void M5Supplier::setError(uint8_t x) {
  _error = x;
}

void M5Supplier::setInterval(unsigned long iv) {
  _interval = iv;
}

unsigned long M5Supplier::getInterval(void) {
  return _interval;
}

void M5Supplier::setLastCheck(unsigned long lc) {
  _lastCheck = lc;
}

unsigned long M5Supplier::getLastCheck(void) {
  return _lastCheck;
}

