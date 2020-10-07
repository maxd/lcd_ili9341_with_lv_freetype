//
// Created by Maxim Dobryakov on 02/10/2020.
//

#ifndef LCD_ILI9341_DEMOSCREEN_H
#define LCD_ILI9341_DEMOSCREEN_H


#include "../ScreenBase.h"

class DemoScreen : public ScreenBase {
    const char* LOG_TAG = "DemoScreen";

    lv_font_t font1;
    lv_style_t style1;

    lv_obj_t *label1;

protected:
    void initializeGui() override;
    void deinitializeGui() override;

    void initializeSPIFFS();
    void initializeCustomFont();
};


#endif //LCD_ILI9341_DEMOSCREEN_H
