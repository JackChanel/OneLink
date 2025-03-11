#ifndef MQTT_H
#define MQTT_H

#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>
#include "CONST.h"
#include "utils.h"
#include "WOLService.h"

WiFiClient wifiClient;
static MqttClient mqttClient(wifiClient);

class MQTT
{
private:
    const int port = MQTT_PORT;
    const char *broker;
    const char *clientId;
    const char *username;
    const char *password;
    const char *subTopic;
    const char *pubTopic;
    bool connected;
    static void onMqttMessage(int messageSize)
    {
        String inputString = "";
        while (mqttClient.available())
        {
            char inChar = (char)mqttClient.read();
            inputString += inChar;
        }
        Serial.println("Total message: " + inputString);

        JsonDocument doc;
        parseJson(inputString, doc);
        JsonObject items = doc["items"].as<JsonObject>();
        int value = items["ESPSTATUS"]["value"].as<int>();
        String MAC = items["MACAddress"]["value"].as<String>();
        Serial.println("ESPSTATUS: " + String(value));
        Serial.println("MAC: " + MAC);

        if (value == 1)
        {
            byte target_mac[6];
            String mac = MAC;
            for (int i = 0; i < 6; i++)
            {
                target_mac[i] = (byte)strtol(mac.substring(i * 3, i * 3 + 2).c_str(), NULL, 16);
            }
            WOLService::sendWOL(BROADCAST, target_mac, sizeof(target_mac));
        }
    }

public:
    MQTT()
    {
        connected = false;
    }

    // 带参构造函数，初始化对象时调用
    MQTT(const char *broker, const char *clientId, const char *username, const char *password)
    {
        connected = false;
        this->broker = broker;
        this->clientId = clientId;
        this->username = username;
        this->password = password;
    }

    // 析构函数，对象销毁时调用
    ~MQTT()
    {
        connected = false;
    }

    void bindConnection(const char *broker, const char *clientId, const char *username, const char *password)
    {
        this->broker = broker;
        this->clientId = clientId;
        this->username = username;
        this->password = password;
    }
    void bindTopic(const char *subTopic, const char *pubTopic)
    {
        this->subTopic = subTopic;
        this->pubTopic = pubTopic;
    }
    bool connect()
    {
        mqttClient.setId(clientId);
        mqttClient.setUsernamePassword(username, password);
        connected = mqttClient.connect(broker, port);
        return connected;
    }
    void bindMessage()
    {
        mqttClient.onMessage(onMqttMessage);
    }

    void subscribe()
    {
        Serial.print("Subscribing to topic: " + String(subTopic));
        mqttClient.subscribe(subTopic, 0);
    }
};

static MQTT mqtt;
void useMQTT()
{
    mqtt.bindConnection(MQTT_BROKER, MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD);
    mqtt.bindTopic("/sys/a1TcFhbvXev/onelink/thing/service/property/set", "/sys/a1TcFhbvXev/onelink/thing/event/property/post");
    if (mqtt.connect())
    {
        Serial.println("MQTT connected!");
        mqtt.bindMessage();
        mqtt.subscribe();
    }
    else
    {
        Serial.println("MQTT connect failed!");
    }
}

void MQTTService()
{
    mqttClient.poll();
}

#endif
