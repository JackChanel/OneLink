#ifndef UTILS_H
#define UTILS_H

#include "CONST.h"
#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

bool parseJson(String &json, JsonDocument &doc);

// FILE SYSTEM
// 启动文件系统
bool startFileSystem()
{
    return LittleFS.begin();
}
// 打印文件系统信息
void printFileSystem()
{
    LittleFS.begin();
    Dir dir = LittleFS.openDir("/");
    while (dir.next())
        Serial.println(dir.fileName());

    Serial.println("File System Info:");

    FSInfo fs_info;
    LittleFS.info(fs_info);
    Serial.println("Total Storage Size (Bytes) -> " + (String)fs_info.totalBytes);
    Serial.println("Used Storage Size (Bytes) -> " + (String)fs_info.usedBytes);
    Serial.println("Max Opened Files Count -> " + (String)fs_info.maxOpenFiles);
    Serial.println("File Block Size -> " + (String)fs_info.blockSize);
    Serial.println("File Page Size -> " + (String)fs_info.pageSize);
}
// 格式化文件系统
bool formatFileSystem()
{
    return LittleFS.format();
}
// 写入文件
bool writeFile(const String &path, const String &content)
{
    LittleFS.begin();
    File file = LittleFS.open(path, "w");
    if (!file)
        return false;
    file.print(content);
    file.close();
    return true;
}
// 显示目录
void showDir(const String &path)
{
    LittleFS.begin();
    Dir dir = LittleFS.openDir(path);
    while (dir.next())
    {
        Serial.print(dir.fileName());
        File file = dir.openFile("r");
        Serial.println(" -> " + file.size());
        file.close();
    }
    LittleFS.end();
}

// SYSTEM CONFIG
// 创建空JSON系统配置文件
void initSystemConfig()
{
    if (!startFileSystem() || LittleFS.exists(CONFIG_FILE_PATH))
        return;
    String plainjson = "{}";
    File configFile = LittleFS.open(CONFIG_FILE_PATH, "w");
    configFile.print(plainjson);
    configFile.close();
}
// 获取系统配置全文
String getSystemConfig()
{
    if (!LittleFS.begin() || !LittleFS.exists(CONFIG_FILE_PATH))
        return "";
    File configFile = LittleFS.open(CONFIG_FILE_PATH, "r");
    if (!configFile)
        return "";
    String config = configFile.readString();
    configFile.close();
    return config;
}
// 获取系统配置项
String getSystemConfig(String key)
{
    String config = getSystemConfig();
    if (config == "")
        return "";
    JsonDocument doc;
    parseJson(config, doc);
    return doc[key].as<String>();
}
// 获取系统配置项列表
String getSystemConfigList()
{
    String config = getSystemConfig();
    if (config == "")
        return "";
    JsonDocument doc;
    parseJson(config, doc);
    String list = "";
    for (JsonPair kv : doc.as<JsonObject>())
    {
        list += kv.key().c_str();
        list += "\n";
    }
    return list;
}

// 设置系统配置项
template <class _T>
void setSystemConfig(const String &key, _T value)
{
    String config = getSystemConfig();
    if (config == "")
        return;
    JsonDocument doc;
    parseJson(config, doc);
    doc[key] = value;
    File configFile = LittleFS.open(CONFIG_FILE_PATH, "w");
    serializeJson(doc, configFile);
    configFile.close();
}

// JSON HANDLER
// 将JSON解析为JsonDocument
bool parseJson(String &json, JsonDocument &doc)
{
    DeserializationError error = deserializeJson(doc, json);
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return false;
    }
    return true;
}

#endif
