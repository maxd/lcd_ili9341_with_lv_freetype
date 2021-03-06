//
// Created by Maxim Dobryakov on 01/10/2020.
//

#include "LvGlApp.h"


#include <esp_log.h>

LvGlApp::LvGlApp(ScreenBase *mainScreen) : mainScreen(mainScreen) {
}

void LvGlApp::runEventLoop() {
    BaseType_t taskResult = xTaskCreatePinnedToCore(eventLoopTaskHandler, "gui-event-loop", 8 * 4096, this, 0, &eventLoopTaskHandle, 1);
    if (taskResult != pdPASS) {
        ESP_LOGW(LOG_TAG, "Can't create `gui-event-loop` task. Error: %d", taskResult);
        abort();
    }
}

void LvGlApp::cancelEventLoop() {
    isCancelled = true;
}

void LvGlApp::eventLoopTask() {
    lv_init();

    initializeDriver();

    mainScreen->initializeGui();

    startTickTimer();
    while(!isCancelled) {
        vTaskDelay(pdMS_TO_TICKS(10));

        if (xSemaphoreTake(guiSemaphore, portMAX_DELAY) == pdTRUE) {
            lv_task_handler();
            xSemaphoreGive(guiSemaphore);
        }
    }
    stopTickTimer();

    mainScreen->deinitializeGui();

    lv_deinit();

    vTaskDelete(eventLoopTaskHandle);
    eventLoopTaskHandle = nullptr;
}

void LvGlApp::initializeDriver() {
    lvgl_driver_init();

    lv_disp_buf_init(&displayBuffer, buffer1, buffer2, DISP_BUF_SIZE);

    lv_disp_drv_init(&displayDriver);
    displayDriver.flush_cb = disp_driver_flush;
    displayDriver.monitor_cb = &driverMonitorCallback;
    displayDriver.buffer = &displayBuffer;
    lv_disp_drv_register(&displayDriver);
}

void LvGlApp::startTickTimer() {
    const esp_timer_create_args_t tickTimerArgs = {
            .callback = &tickTaskHandler,
            .arg = nullptr,
            .dispatch_method = ESP_TIMER_TASK,
            .name = "gui-tick-timer",
    };
    ESP_ERROR_CHECK(esp_timer_create(&tickTimerArgs, &tickTimer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(tickTimer, TickPeriod * 1000));
}

void LvGlApp::stopTickTimer() {
    ESP_ERROR_CHECK(esp_timer_stop(tickTimer));
}

void LvGlApp::eventLoopTaskHandler(void *arg) {
    auto *instance = static_cast<LvGlApp *>(arg);
    instance->eventLoopTask();
}

void LvGlApp::tickTaskHandler(__unused void *arg) {
    lv_tick_inc(TickPeriod);
}

//TODO: temporary method (for debug)
void LvGlApp::driverMonitorCallback(__unused _disp_drv_t *displayDriver, __unused uint32_t time, uint32_t updatedPixels) {
    ESP_LOGI("", "Updated pixels: %d", updatedPixels);
}
