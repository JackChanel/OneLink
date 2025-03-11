#ifndef LED_H
#define LED_H

#include "init.h"
#include "WiFiConnect.h"

#define RED D1
#define GREEN D2
#define BLUE D5

enum SYSTEM_STATE
{
    UNCONFIG = 0,
    WIFI_CONNECTED = 1,
    WIFI_FAILED = 2
};

int LED_STATE = UNCONFIG;

// 初始化LED
void initLED()
{
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
}

// 未配置WiFi时，LED红灯闪烁
void LED_unconfig()
{
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(RED, HIGH);
        delay(500);
        digitalWrite(RED, LOW);
        delay(500);
    }
}

// 配置WiFi成功，LED绿灯常亮
void LED_wifi_connected()
{
    digitalWrite(GREEN, HIGH);
}

// 配置WiFi失败，LED蓝灯常亮
void LED_wifi_failed()
{
    digitalWrite(BLUE, HIGH);
}

// 设置LED状态
bool updateLEDState()
{
    int OLD_STATE = LED_STATE;
    if (isFirstStart())
    {
        LED_STATE = UNCONFIG;
    }
    else if (isWiFiConnected())
    {
        LED_STATE = WIFI_CONNECTED;
    }
    else
    {
        LED_STATE = WIFI_FAILED;
    }
    return OLD_STATE != LED_STATE;
}

// 更新LED状态
void ActivateLED()
{
    if (updateLEDState())
    {
        Serial.println("LED_STATE: " + String(LED_STATE));
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, LOW);
        switch (LED_STATE)
        {
        case UNCONFIG:
            LED_unconfig();
            break;
        case WIFI_CONNECTED:
            LED_wifi_connected();
            break;
        case WIFI_FAILED:
            LED_wifi_failed();
            break;
        default:
            break;
        }
    }
    else
    {
        return;
    }
}

#endif
