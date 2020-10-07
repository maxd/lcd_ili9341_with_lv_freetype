
#include "LvGlApp.h"
#include "demo/DemoScreen.h"

extern "C" void app_main() {
    auto *demoScreen = new DemoScreen();

    auto *app = new LvGlApp(demoScreen);
    app->runEventLoop();
}