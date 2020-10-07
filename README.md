# Intro

Demonstration of work [lv_lib_freetype](https://github.com/lvgl/lv_lib_freetype/) on `ILI9341` display.

# SPIFFS performance

SPIFFS performance is ugly. So, font loading and initialization take about 1 minute on ESP32. 
So, will be better not to use lv_lib_freetype on ESP32.