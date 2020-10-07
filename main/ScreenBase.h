//
// Created by Maxim Dobryakov on 06/10/2020.
//

#ifndef LCD_ILI9341_SCREENBASE_H
#define LCD_ILI9341_SCREENBASE_H

#include <lvgl/lvgl.h>

class ScreenBase {
public:
    virtual void initializeGui() = 0;
    virtual void deinitializeGui() = 0;
};


#endif //LCD_ILI9341_SCREENBASE_H
