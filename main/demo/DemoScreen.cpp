//
// Created by Maxim Dobryakov on 02/10/2020.
//

#include "DemoScreen.h"


#include <esp_log.h>
#include <esp_spiffs.h>
#include <lv_freetype.h>

void DemoScreen::initializeGui() {
    initializeSPIFFS();
    initializeCustomFont();

    label1 = lv_label_create(lv_scr_act(), nullptr);

    ESP_LOGI(LOG_TAG, "Add style1 to label1...");
    lv_obj_add_style(label1, LV_LABEL_PART_MAIN, &style1);
    ESP_LOGI(LOG_TAG, "style1 added to label1!");

    ESP_LOGI(LOG_TAG, "Set text to label1...");
    lv_label_set_text(label1, "Прювет Всем!");
    ESP_LOGI(LOG_TAG, "Text set to label1!");

    lv_obj_align(label1, nullptr, LV_ALIGN_CENTER, 0, 0);
}

void DemoScreen::deinitializeGui() {
}

void DemoScreen::initializeSPIFFS() {
    ESP_LOGI(LOG_TAG, "Initializing SPIFFS...");

    esp_vfs_spiffs_conf_t conf = {
            .base_path = "/storage",
            .partition_label = nullptr,
            .max_files = 5,
            .format_if_mount_failed = false
    };
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(LOG_TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(LOG_TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(LOG_TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        abort();
    }

    ESP_LOGI(LOG_TAG, "SPIFFS initialized!");
}

void DemoScreen::initializeCustomFont() {
    ESP_LOGI(LOG_TAG, "Initializing custom font...");

    lv_freetype_init(64);

    lv_freetype_font_init(&font1, "/storage/arial.ttf", 16);

    lv_style_init(&style1);
    lv_style_set_text_font(&style1, LV_STATE_DEFAULT, &font1);

    ESP_LOGI(LOG_TAG, "Custom font initialized!");
}
