#define WIFI_SSID_REGEX "ssid_pattern"
#define WIFI_PASSWORD ""
#define HOSTNAME "MHI-AC-Ctrl"

#define MQTT_SERVER "my_mqtt_server"                // broker name or IP address of the broker
#define MQTT_PORT 1883                              // port number used by the broker
#define MQTT_USER ""                                // if authentication is not used, leave it empty
#define MQTT_PASSWORD ""                            // if authentication is not used, leave it empty
#define MQTT_PREFIX HOSTNAME "/"                    // basic prefix used for publishing AC data (e.g. for status),
                                                    // replace "/" by e.g. "/Living-Room/" when you have multiple ACs
