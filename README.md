9# M5Widgets
Widgets for the M5Stack

This is based on the [alas now defunct!] [Phoenard project](https://github.com/Phoenard/Phoenard). The Phoenard had a touchscreen, whereas the M5Stack has a "dumb" screen. So instead of copy/pasting and adapting the code, I am selecting the juicy, non-touch bits, and adapting them to the M5, while simplifying a bit.

# Installation

It is a little more complex than the regular library, as I am integrating this to the M5Stack library. The first step is to drop all the .cpp and .h files (except `Free_fonts.h`, which is for the sample sketches) to the `~/Arduino/libraries/M5Stack/src/utility/` folder. Then, in `M5Stack.h`, towards the bottom of the file, after:

    extern M5Stack M5;
    #define m5 M5
    #define lcd Lcd

add the following

    // added by Kongduino
    #include "utility/M5DataBuffer.h"
    #include "utility/M5Widget.h"
    #include "utility/M5Gauge.h"
    #include "utility/M5ProgressBar.h"
    #include "utility/M5BarGraph.h"
    #include "utility/M5LineGraph.h"

You have now access to the M5Widgets. Yay!

I am adding two [similar] examples: M5_Widgets.ino and M5_Widgets_BMP280.ino. The first one displays random data points, whereas the second one uses a BMP280 sensor to display temperature and pressure data in various widgets. They both use the Free_Fonts.h header file. Make copies, and put then in folders. You know the drill.

# Remarks
Since this is a work in progress, I have stripped down the comments and license (I'm keeping the same MIT license). That doesn't mean I am trying to negate Phoenard's work, or take undue credit. I need the code to be as compact as possible, and don't need reams of comments to wade through, in every file. In due time, I will make a proper documentation for all the widgets, and the main M5Widget class, from which all widgets are descended.

The original is much more complex, and evolved. There are quite a few abstraction classes (widget container, display, etc), that I decided to skip to make things simpler. I have added one widget of my own, the M5Gauge, and will add more, as the need arises. Also, I will try to rework some of the `isTouched` logic into an abstraction class for the three buttons the M5Stack has. This would enable things like a scrollable ItemList, where Button A would be up, Button C down, and Button B select.
