#pragma once

#include "MHI-AC-Ctrl-core.h"
#include "MHI-AC-Ctrl.h"

#include "secrets.h"

#define VERSION "2.5R3"
#define WiFI_SEARCHStrongestAP true                 // when false then the first WiFi access point with matching SSID found is used.
                                                    // when true then the strongest WiFi access point with matching SSID found is used, it doesn't work with hidden SSID
                                                    
#define WiFI_SEARCH_FOR_STRONGER_AP_INTERVALL 12    // WiFi network re-scan interval in minutes with alternate to +5dB stronger signal if detected

#define MQTT_SET_PREFIX MQTT_PREFIX "set/"          // prefix for subscribing set commands, must end with a "/"
#define MQTT_OP_PREFIX MQTT_PREFIX "OpData/"        // prefix for publishing operating data, must end with a "/"
#define MQTT_ERR_OP_PREFIX MQTT_PREFIX "ErrOpData/" // prefix for publishing operating data from last error, must end with a "/"

#define OTA_HOSTNAME HOSTNAME                       // default for the OTA_HOSTNAME is the HOSTNAME
#define OTA_PASSWORD HOSTNAME                       // Enter an OTA password if required

#define TEMP_MEASURE_PERIOD 0                       // period in seconds for temperature measurement with the external DS18x20 temperature sensor
                                                    // enter 0 if you don't use the DS18x20 
#define ONE_WIRE_BUS 4                              // D2, PIN for connecting temperature sensor DS18x20 DQ pin

//#define ROOM_TEMP_DS18X20                           // use room temperature from DS18x20

#define ROOM_TEMP_MQTT_SET_TIMEOUT  40              // time in seconds, after this time w/o receiving a valid room temperature
                                                    // via MQTT fallback to IU temperature sensor value

//#define POWERON_WHEN_CHANGING_MODE true           // uncomment it to switch on the AC when the mode (heat, cool, dry etc.) is changed
                                                    // used e.g. for home assistant support

// SHT21 support via I2C
// Required library: https://github.com/e-radionicacom/SHT21-Arduino-Library
// Connect the middle pin of the three-point connector (D2/SDA on WEIMOS D1 Mini) to the SDA pin of the SHT21 breakout board.
// Connect the D1/SCL pin of the WEIMOS D1 Mini to the SCL pin of the SHT21 breakout board.
// I2C termination resistors should be on the breakout board. The three-point connector's VCC and GND pins can be used.
// Test I2C functionality using the example provided by the library!
#define USE_SHT21                                   // if this is defined, the SHT21 temperature/humidity sensor is used
                                                    // cannot be used together with TEMP_MEASURE_PERIOD > 0!
#define SHT21_READ_INTERVAL       5000              // milliseconds

#define ROOM_TEMP_SHT21                             // use room temperature from SHT21

#if defined(USE_SHT21) && (TEMP_MEASURE_PERIOD > 0)
  #error You cannot use TEMP_MEASURE_PERIOD (DS18x20) and USE_SHT21 at the same time!
#endif

// *** The configuration ends here ***

#include <ESP8266WiFi.h>        // https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi
#include <PubSubClient.h>       // https://github.com/knolleary/pubsubclient
#include <ArduinoOTA.h>         // https://github.com/esp8266/Arduino/tree/master/libraries/ArduinoOTA

#if TEMP_MEASURE_PERIOD > 0
#include <OneWire.h>            // https://www.pjrc.com/teensy/td_libs_OneWire.html
#include <DallasTemperature.h>  // https://github.com/milesburton/Arduino-Temperature-Control-Library
#endif

#ifdef ROOM_TEMP_DS18X20
#if (TEMP_MEASURE_PERIOD == 0)
#error "You have to use a value>0 for TEMP_MEASURE_PERIOD when you want to use DS18x20 as an external temperature sensor"
#endif
#endif

#ifdef USE_SHT21
#include <SHT21.h>              // https://github.com/e-radionicacom/SHT21-Arduino-Library
#endif

extern PubSubClient MQTTclient;

bool MeasureFrequency();                                      // measures the frequency of the SPI pins
void initWiFi();                                              // basic WiFi initialization
void setupWiFi(int& WiFiStatus);                              // setup WIFi connection to AP
int MQTTreconnect();                                          // (re)connect to MQTT broker
void publish_cmd_ok();                                        // last MQTT cmd was o.k.
void publish_cmd_unknown();                                   // last MQTT cmd was unknown
void publish_cmd_invalidparameter();                          // a paramter of the last MQTT was wrong
void output_P(const ACStatus status, PGM_P topic, PGM_P payload);   // publish via MQTT
void output(const ACStatus status, PGM_P topic, char* payload);

void setupOTA();                                              // initialize and start OTA
void setup_ds18x20();                                         // setup the temperature measurement
byte getDs18x20Temperature(int temp_hysterese);               // read the temperature from the DS18x20 sensor

void setup_SHT21();                                           // setup the temperature measurement
float getSHT21Temperature();                                  // read the temperature from the SHT21 sensor
float getSHT21Humidity();                                     // read the humidity from the SHT21 sensor

#define WIFI_CONNECT_TIMEOUT 2
#define WIFI_CONNECT_ONGOING 1
#define WIFI_CONNECT_OK 0

#define MQTT_NOT_CONNECTED 2
#define MQTT_RECONNECTED 1
#define MQTT_CONNECT_OK 0
