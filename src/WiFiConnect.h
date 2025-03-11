#ifndef WIFICONNECT_H
#define WIFICONNECT_H

#include "CONST.h"
#include <ESP8266WiFi.h>

// AP
void createAP(String ssid, String password);

// WiFi
bool connectWiFi(String SSID, String PASSWORD, int wait_time);
bool isValideWiFi(String ssid, String password);
bool isWiFiConnected();

// 创建AP
void createAP(String ssid, String password)
{
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(APIP, APIP, MASK);
    WiFi.softAP(ssid, password);
    Serial.println("AP Created! : " + ssid + " " + password);
}

// 连接WiFi
bool connectWiFi(String SSID, String PASSWORD, int retry = 5)
{
    WiFi.begin(SSID, PASSWORD);

    int cnt = 0;

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println(cnt);
        if (cnt++ >= retry)
            return false;
    }

    if (WiFi.status() == WL_CONNECTED)
        return true;
    return false;
}

// 验证WiFi，但不连接
bool isValideWiFi(String ssid, String password)
{
    if (ssid == "" || password == "")
        return false;
    WiFi.begin(ssid, password);
    int count = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        if (count++ > 20)
        {
            WiFi.disconnect();
            return false;
            break;
        }
    }
    WiFi.disconnect();
    return true;
}

// WiFi连接状态查询
bool isWiFiConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

#endif
