#ifndef _M5WIDGET_H_
#define _M5WIDGET_H_

#include <M5Stack.h>
#include <Arduino.h>
#include "utility/M5DataBuffer.h"

#define BACKGROUND  0
#define FRAME       1
#define FOREGROUND  2
#define CONTENT     3
#define HIGHLIGHT   4
#define ACTIVATED   5

// New color definitions use for all my libraries
#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFD20      /* 255, 165,   0 */
#define TFT_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define TFT_PINK        0xF81F

void drawStringMiddle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const char* text, const GFXfont* myFont, uint16_t bg, uint16_t fg);
uint16_t calculateRGB565(uint8_t r, uint8_t g, uint8_t b);

class M5Widget {
  public:
    /// Constructor for a new widget, initializing all fields to the default values
    M5Widget();
    /// Destructor for a widget, clearing any child widgets and freeing memory
    virtual ~M5Widget();
    /// Gets the x-coordinate of the widget
    const int getX(void) {
      return x;
    }
    /// Gets the y-coordinate of the widget
    const int getY(void) {
      return y;
    }
    /// Gets the width of the widget
    const int getWidth(void) {
      return width;
    }
    /// Gets the height of the widget
    const int getHeight(void) {
      return height;
    }
    /// Sets the new bounds (x, y, width, height) of the widget
    void setBounds(int x, int y, int width, int height);
    /// Sets the size (width, height) of the widget
    void setSize(int width, int height);
    /** @brief Sets a style color for this widget

       The colorId specifies an index in the palette to set the color.
       Standard indices for all widgets are defined as the constants
       BACKGROUND, FRAME, FOREGROUND, CONTENT, HIGHLIGHT and ACTIVATED.
    */
    virtual void setColor(int colorId, uint16_t color);
    /** @brief Gets a style color set for this widget

       The colorId specifies an index in the palette to set the color.
       Standard indices for all widgets are defined as the constants
       BACKGROUND, FRAME, FOREGROUND, CONTENT, HIGHLIGHT and ACTIVATED.
    */
    const uint16_t color(int colorId) {
      return myColors[colorId];
    }

    virtual void setFont(const GFXfont* font);

    /// Sets whether the widget is displayed and updated
    void setVisible(bool visible);
    /// Gets whether the widget is displayed and updated
    bool isVisible(void);

    /// Gets whether the widget has been drawn
    bool isDrawn(void);

    /// Sets whether the widget is drawn and undrawn
    void setDrawingEnabled(bool drawing);
    /// Gets whether the widget is drawn and undrawn
    bool isDrawingEnabled(void);
    // Erases widget
    void eraseWidget(void);
    void fillBorderRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color, uint16_t borderColor);
    void fillBorderRoundRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t radius, uint16_t color, uint16_t borderColor);
    void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

    /// Invalidated the widget, causing it to be re-drawn at a later time
    void invalidate(void);
    /// Checks whether the widget is invalidated and needs to be redrawn
    bool isInvalidated(void);
    /// Draws the widget if invalidated, clearing the invalidated state
    void draw_validate();
    /// Clear draw function routine, where widgets perform un-drawing (to background)
    virtual void undraw(void);
    /// Draw function routine, where widgets must perform drawing
    virtual void draw(void) = 0;
    /// Update function routine, where widget logic must be performed
    virtual void update(void) = 0;
    uint16_t myColors[6] = {
      TFT_WHITE, TFT_LIGHTGREY, TFT_BLACK, TFT_BLACK, TFT_YELLOW, TFT_LIGHTGREY
    };

  protected:
    //! \name Widget bounds
    //@{
    int x, y, width, height;
    const GFXfont* myFont = &FreeMono9pt7b;
    //@}
    //! Draw state flags of the widget (0=invisible, 0x1=visible, 0x2=drawn, 0x4=draw_disabled)
    unsigned char visible;
    //! Invalidated state of the widget
    bool invalidated;
};

#include "utility/M5Gauge.h"
#include "utility/M5ProgressBar.h"
#include "utility/M5BarGraph.h"
#include "utility/M5LineGraph.h"
#include "utility/M5QRCode.h"
#include "utility/M5Bridge.h"
#include "utility/M5Supplier.h"
#include "utility/M5BMP280.h"
#include "utility/M5SmartGauge.h"
#include "utility/M5Touch.h"
#include "utility/M5StaticMenu.h"

#endif