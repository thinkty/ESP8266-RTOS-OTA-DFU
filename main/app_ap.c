
#include "app_ap.h"

void wifi_event_handler(void * arg, esp_event_base_t event_base, int32_t event_id, void * event_data)
{
    wifi_event_ap_staconnected_t * event = (wifi_event_ap_staconnected_t *) event_data;

    switch (event_id)
    {
    case WIFI_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG, ""MACSTR" join", MAC2STR(event->mac));
        break;
    
    case WIFI_EVENT_AP_STADISCONNECTED:
        ESP_LOGI(TAG, ""MACSTR" leave", MAC2STR(event->mac));
        break;

    default:
        ESP_LOGE(TAG, "Unexpected WiFi event %d", event_id);
        break;
    }
}

void init_ap()
{
    // Initialize TCP/IP stack 
    tcpip_adapter_init();

    ESP_LOGI(TAG, "Initializing AP.");
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // Register event handler to handle new connection and disconnection
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = CONFIG_ESP_WIFI_SSID,
            .ssid_len = strlen(CONFIG_ESP_WIFI_SSID),
            .password = CONFIG_ESP_WIFI_PASSWORD,
            .max_connection = CONFIG_ESP_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    // Coredump if password not set
    if (strlen(CONFIG_ESP_WIFI_PASSWORD) == 0) {
        ESP_LOGE(TAG, "AP password not set. Aborting...");
        abort(); 
    }

    // Set WiFi as access point with the following configuration
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "AP initialized - SSID:%s password:%s", CONFIG_ESP_WIFI_SSID, CONFIG_ESP_WIFI_PASSWORD);
}