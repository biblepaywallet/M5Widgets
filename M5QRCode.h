#include "M5Widget.h"

#ifndef _M5QRCODE_H_
#define _M5QRCODE_H_
// If you don't have the qrcode library, this is gonna hurt...
#include "qrcode.h"

class M5QRCode : public M5Widget {
  public:
    M5QRCode();
    void setValue(char *text);
    void setValue(const String &);
    char *value() const { return _text; }
    virtual void draw(void);
    virtual void update(void);
    virtual void erase(void);
    virtual void centerDisplay(bool);
    virtual void consoleDisplay(bool);
    virtual uint8_t version(void);
    virtual void setVersion(uint8_t);
    uint8_t xOffset, yOffset;

  private:
    char * _text;
    QRCode _qrcode;
    uint8_t _version = 6, _thickness = 2;
    bool _center, _serial, _isDrawn;
};
#endif
