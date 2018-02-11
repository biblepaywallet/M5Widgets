# M5Widgets
Widgets for the M5Stack

This is based on the [alas now defunct!] [Phoenard project](https://github.com/Phoenard/Phoenard). The Phoenard had a touchscreen, whereas the M5Stack has a "dumb" screen. So instead of copy/pasting and adapting the code, I am selecting the juicy, non-touch bits, and adapting them to the M5, while simplifying a bit.

# Installation

It is a little more complex than the regular library, as I am integrating this to the M5Stack library. The first step is to drop all the .cpp and .h files (except `Free_fonts.h`, which is for the sample sketches) to the `~/Arduino/libraries/M5Stack/src/utility/` folder.

![alt text](https://github.com/Kongduino/M5Widgets/blob/master/README-00.png "All the files you need to add.")

You'll also need these two libraries in your Arduino/libraries folder: [QRCode](https://github.com/ricmoo/qrcode) and [Seeed_BMP280](https://github.com/Seeed-Studio/Grove_BMP280).

![alt text](https://github.com/Kongduino/M5Widgets/blob/master/README-02.png "Required libraries")

Then, in `M5Stack.h`, towards the bottom of the file, after:

    extern M5Stack M5;
    #define m5 M5
    #define lcd Lcd

add the following

    // added by Kongduino
    #include "utility/M5Widget.h"

All other .h / .cpp files are included from within M5Widget.h, which makes it easier to maintain.

You have now access to the M5Widgets. Yay!

I am adding two [similar] examples: M5_Widgets.ino and M5_Widgets_BMP280.ino. The first one displays random data points, whereas the second one uses a BMP280 sensor to display temperature and pressure data in various widgets. They both use the Free_Fonts.h header file. Make copies, and put then in folders. You know the drill.

![alt text](https://github.com/Kongduino/M5Widgets/blob/master/README-03.png "The two sketches.")

Added M5Bridge, which is working much better now (I sure ain't saying it is bug-free yet though). Added also a sample project M5_Bridge_Sample.ino, that demonstrates a Serial-to-LoRa bridge, with a menu.

![alt text](https://github.com/Kongduino/M5Widgets/blob/master/README-04.png "M5_Bridge_Sample")

# Remarks
Since this is a work in progress, I have stripped down the comments and license (I'm keeping the same MIT license). That doesn't mean I am trying to negate Phoenard's work, or take undue credit. I need the code to be as compact as possible, and don't need reams of comments to wade through, in every file. In due time, I will make a proper documentation for all the widgets, and the main M5Widget class, from which all widgets are descended.

The original is much more complex, and evolved. There are quite a few abstraction classes (widget container, display, etc), that I decided to skip to make things simpler. I have added one widget of my own, the M5Gauge, and will add more, as the need arises. Also, I will try to rework some of the `isTouched` logic into an abstraction class for the three buttons the M5Stack has. This would enable things like a scrollable ItemList, where Button A would be up, Button C down, and Button B select.

Added M5Touch, a framework for menus using the 3 buttons. Idea and partial code from the treasure trove at  https://github.com/tomsuch/M5Stack-SAM
