#include "src/WiFiConnect.h"
#include "src/Server.h"
#include "src/init.h"
#include "src/utils.h"
#include "src/LED.h"
#include "src/WOLService.h"
#include "src/MQTT.h"

ESP8266WebServer &server = createServer(80);
DNSServer &dnsServer = createDNS();

void setup()
{
    Serial.begin(115200);
    initLED();
    if (isFirstStart())
    {
        Serial.println("first start... clearing all data...");
        initSystem();
    }
    else
    {
        Serial.println("not first start...");
        String ssid = getSystemConfig("ssid");
        String password = getSystemConfig("password");
        if (!isValideWiFi(ssid, password))
            createInitServer();
        else
        {
            // should be removed in production
            createInitServer();
            Serial.println("You can use this device now!");

            connectWiFi(ssid, password, 5);

            useMQTT();

            useWOL();
        }
    }
}

void loop()
{
    dnsServer.processNextRequest();
    server.handleClient(); // 处理http服务器访问
    MQTTService();
}
