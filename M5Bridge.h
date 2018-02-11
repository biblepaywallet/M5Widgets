#ifndef _M5BRIDGE_H_
#define _M5BRIDGE_H_

#include <Arduino.h>
#include <M5LoRa.h>
#include <SPI.h>

#define PIPE0 0
#define PIPE1 1
#define INPUTPIPE 0
#define OUTPUTPIPE 1
#define tSERIAL0 0
#define tSERIAL2 1
#define tLoRa 2

class M5Bridge {
  public:
    M5Bridge();
    void setIOFunction(uint8_t, uint8_t);
    void start(void);
    void stop(void);
    void run(void);
    void setLoRaBand(uint32_t);
    void setLoRaUUID(char *);
    bool isActive(void);
    bool serial0Inited(void);
    bool serial2Inited(void);
    bool loraInited(void);
    void setSerial0Inited(bool);
    void setSerial2Inited(bool);
    void setLoRaInited(bool);
    uint32_t getSerial0Speed(void);
    uint32_t getSerial2Speed(void);
    uint32_t getLoRaBand(void);

  private:
    bool _isActive, _serial0Inited, _serial2Inited, _loraInited;
    void (*_streamInput0Function)(void);
    void (*_streamInput1Function)(void);
    void (*_streamOutput0Function)(void);
    void (*_streamOutput1Function)(void);
    void (*_streamInit0Function)(M5Bridge*);
    void (*_streamInit1Function)(M5Bridge*);
    uint32_t _BAND, _serialSourceCount, _serialDestinationCount;
    uint32_t _Serial0Speed, _Serial2Speed;
    char *_myLoRaUUID;
};

#endif
