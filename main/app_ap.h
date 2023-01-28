
#ifndef APP_AP_H
#define APP_AP_H

#include <string.h>

#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_system.h"

#ifndef TAG
#define TAG "APP"
#endif

/**
 * Event handler for WiFi events.
 * Print the MAC addresses for the devices joining and leaving the access point.
 */
void wifi_event_handler(void * arg, esp_event_base_t event_base, int32_t event_id, void * event_data);

/**
 * Initialize the ESP8266 as an access point with configurations from the Kconfig.projbuild file.
 * 
 * - CONFIG_ESP_WIFI_SSID : name of access point
 * - CONFIG_ESP_WIFI_PASSWORD : password for access point
 * - CONFIG_ESP_MAX_STA_CONN : maximum number of stations connected
 */
void init_ap();

#endif
