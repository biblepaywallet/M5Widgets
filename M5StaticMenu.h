#ifndef _M5STATICMENU_H_
#define _M5STATICMENU_H_
#include "M5Widget.h"
#include "M5Touch.h"

class M5StaticMenu : public M5Widget {
  public:
    M5StaticMenu();
    void setDrawHeader(void (*myFunction)(void));
    void setDrawFooter(void (*myFunction)(void));
    void setDrawCenter(void (*myFunction)(void));
    void attachTouch(M5Touch);
    virtual void update(void);
    virtual void draw(void);

  private:
    void (*_drawHeader)(void);
    void (*_drawFooter)(void);
    void (*_drawCenter)(void);
    M5Touch _touch;
};
#endif
