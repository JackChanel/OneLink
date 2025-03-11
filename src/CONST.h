#ifndef CONST_H
#define CONST_H

#include <ESP8266WiFi.h>

#define WEB_CONFIG_PATH "/web/init.html"
#define CONFIG_FILE_PATH "/data/config.json"
#define DNS_PORT 53

#define PRODUCT_KEY "a1TcFhbvXev"
#define DEVICE_NAME "onelink"
#define DEVICE_SECRET "228145be5e719ffb12dec66cf27156bc"
#define REGION_ID "cn-shanghai"

#define MQTT_PORT 1883
#define MQTT_BROKER "a1TcFhbvXev.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define MQTT_CLIENT_ID "a1TcFhbvXev.onelink|securemode=2,signmethod=hmacsha256,timestamp=1716566948736|"
#define MQTT_USERNAME "onelink&a1TcFhbvXev"
#define MQTT_PASSWORD "4cae308a3f00fe04675a57dd646e3ffd664bc0b6e32807c086c353577b74fdef"

const IPAddress APIP(192, 168, 1, 1);
const IPAddress MASK(255, 255, 255, 0);
const IPAddress BROADCAST(255, 255, 255, 255);

#endif
