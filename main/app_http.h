
#ifndef APP_HTTP_H
#define APP_HTTP_H

#include "esp_log.h"
#include "esp_http_server.h"

#ifndef TAG
#define TAG "APP"
#endif

/**
 * URI handler for root (/).
 * Respond with the webpage to upload an image.
 */
esp_err_t get_handler(httpd_req_t * req);

/**
 * Start the http daemon in background on the default port
 */
void init_http();

#endif
