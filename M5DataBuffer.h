#include <Arduino.h>

#ifndef _DATA_BUFFER_H_
#define _DATA_BUFFER_H_

class DataBuffer {
public:
  DataBuffer() : data(NULL), dataSize(0) {}
  DataBuffer(const void* data, int dataSize);
  ~DataBuffer();
  void resize(int newDataSize);
  void growToFit(int newDataSize);
  void set(const void* data, int dataSize);
  DataBuffer& operator=( const DataBuffer& other );
  virtual const char* text() { return (char*) data; }
  virtual void setTextRaw(const char* text, int textLen);
  void* data;
  int dataSize;
};

#endif