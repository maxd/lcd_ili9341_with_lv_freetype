FILE(GLOB_RECURSE app_sources ${COMPONENT_DIR}/*.*)

idf_component_register(SRCS ${app_sources}
        REQUIRES lvgl_esp32_drivers lvgl lvgl_tft lv_lib_freetype spiffs)

spiffs_create_partition_image(storage spiffs_storage FLASH_IN_PROJECT)