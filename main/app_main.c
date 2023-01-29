
#include "esp_event.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"

#include "app_ap.h"
#include "app_http.h"
#include "app_tasks.h"

void app_main()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    
    // Create event loop to handle WiFi and HTTP events
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Initialize the access point
    init_ap();

    // Initialize HTTP server for the webpage to upload updates
    init_http();

    // Interval (in milliseconds) to read/print sensor values.
    th_task_args th_args = {
        .interval = 10000,
        .pin = CONFIG_APP_AM2302_GPIO
    };

    // Initialize and run the temperature/humidity sensor task with priority 10
    ESP_ERROR_CHECK(init_th(th_args.pin));
    xTaskCreate(th_task, "th task", DEFAULT_THREAD_STACKSIZE, &th_args, 10, NULL);
}
