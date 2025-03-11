#ifndef SERVER_H
#define SERVER_H

#include "CONST.h"
#include <ESP8266WebServer.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include "WiFiConnect.h"
#include "utils.h"

ESP8266WebServer &createServer(int PORT);

// DNS
DNSServer &createDNS();

// Init Server
void createInitServer();

ESP8266WebServer &createServer(int PORT)
{
    static ESP8266WebServer server(PORT); // 初始化 server 对象
    return server;                        // 返回 server 对象
}

// 创建DNS服务器定向到AP
DNSServer &createDNS()
{
    static DNSServer dnsServer;
    dnsServer.setTTL(300);
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    bool dnsServerStatus = dnsServer.start(DNS_PORT, "www.onelink.com", APIP);
    if (dnsServerStatus)
        Serial.println("DNS Server Created!");
    else
        Serial.println("DNS Server Failed to Create!");
    return dnsServer;
}

// 初始化服务器 - 首页
void _initHomePage()
{
    ESP8266WebServer &server = createServer(80);
    server.send(200, "text/html", LittleFS.open(WEB_CONFIG_PATH, "r").readString());
}

// 初始化服务器 - WiFi配置
void _initWiFiPost()
{
    ESP8266WebServer &server = createServer(80);
    String rowJson = server.arg("plain");
    JsonDocument doc;
    parseJson(rowJson, doc);
    String ssid = doc["ssid"].as<String>();
    String password = doc["password"].as<String>();

    if (isValideWiFi(ssid, password))
    {
        setSystemConfig("ssid", ssid);
        setSystemConfig("password", password);
        setSystemConfig("wifi", "true");
        server.send(200, "application/json", "{\"success\": true}");
        delay(1000);
        ESP.restart();
    }
    else
        server.send(200, "application/json", "{\"success\": false}");
}

// 创建初始化服务器
void createInitServer()
{
    createAP("onelink", "12345678");
    createDNS();
    ESP8266WebServer &server = createServer(80);
    server.on("/", _initHomePage);
    server.on("/setup", HTTP_POST, _initWiFiPost);
    server.on("/formatFileSystem", HTTP_GET, [&server]()
              {
        formatFileSystem();
        server.send(200, "application/json", "{\"success\": true,\"message\": \"File System is format!\"}"); });
    server.begin();
}

#endif
