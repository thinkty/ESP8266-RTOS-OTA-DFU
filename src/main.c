#include "esp_common.h"
#include "freertos/task.h"
#include "gpio.h"

void task_blink(void* ignore)
{
    gpio16_output_conf();
    while(true) {
    	gpio16_output_set(0);
        vTaskDelay(1000/portTICK_RATE_MS);
    	gpio16_output_set(1);
        vTaskDelay(1000/portTICK_RATE_MS);
    }

    vTaskDelete(NULL);
}

void user_init(void)
{
    xTaskCreate(&task_blink, "blink", 2048, NULL, 1, NULL);
}