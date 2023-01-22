
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_http_server.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"

static const char *TAG = "APP";
static httpd_handle_t server = NULL;
static const char *PAGE = "hello world";

esp_err_t get_handler(httpd_req_t *req)
{
    httpd_resp_send(req, PAGE, strlen(PAGE));

    return ESP_OK;
}

httpd_uri_t home = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = get_handler,
    .user_ctx  = NULL
};

void init_http()
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    // Start the httpd server on default port
    ESP_LOGI(TAG, "Starting HTTP server on port: '%d'", config.server_port);
    ESP_ERROR_CHECK(httpd_start(&server, &config));

    // Set URI handlers
    httpd_register_uri_handler(server, &home);
}

static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;

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
    ESP_LOGI(TAG, "Initializing AP.");
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // Register event handler to handle new connection and disconnection
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));

    /**
     * The WiFi configuration is set in the Kconfig.projbuild file.
     * - CONFIG_ESP_WIFI_SSID
     * - CONFIG_ESP_WIFI_PASSWORD
     * - CONFIG_ESP_MAX_STA_CONN : maximum number of stations connected
    */
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = CONFIG_ESP_WIFI_SSID,
            .ssid_len = strlen(CONFIG_ESP_WIFI_SSID),
            .password = CONFIG_ESP_WIFI_PASSWORD,
            .max_connection = CONFIG_ESP_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };
    if (strlen(CONFIG_ESP_WIFI_PASSWORD) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    // Set WiFi as access point with the following configuration
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "AP initialized. SSID:%s password:%s", CONFIG_ESP_WIFI_SSID, CONFIG_ESP_WIFI_PASSWORD);
}

void app_main()
{
    ESP_ERROR_CHECK(nvs_flash_init());

    // Initialize TCP/IP stack 
    tcpip_adapter_init();
    
    // Create event loop to handle WiFi and HTTP events
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Initialize the access point
    init_ap();

    // Initialize HTTP server that simply shows HelloWorld
    init_http();
}
