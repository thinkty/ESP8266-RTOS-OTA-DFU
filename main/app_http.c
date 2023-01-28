
#include "app_http.h"

static const char * PAGE = "hello world";

esp_err_t get_handler(httpd_req_t * req)
{
    httpd_resp_send(req, PAGE, strlen(PAGE));

    return ESP_OK;
}

void init_http()
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    // Start the httpd server on default port
    ESP_LOGI(TAG, "Starting HTTP server on port: '%d'", config.server_port);
    ESP_ERROR_CHECK(httpd_start(&server, &config));

    // URI handler for root
    httpd_uri_t home = {
        .uri       = "/",
        .method    = HTTP_GET,
        .handler   = get_handler,
        .user_ctx  = NULL
    };

    // Set URI handlers
    httpd_register_uri_handler(server, &home);
}