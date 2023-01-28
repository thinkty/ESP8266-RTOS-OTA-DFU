
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"

#include "app_ap.h"
#include "app_http.h"

void app_main()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    
    // Create event loop to handle WiFi and HTTP events
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Initialize the access point
    init_ap();

    // Initialize HTTP server for the webpage to upload updates
    init_http();
}
