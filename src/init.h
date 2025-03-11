#ifndef INIT_H
#define INIT_H

#include "CONST.h"
#include "Server.h"
#include "init.h"
#include "utils.h"

bool isFirstStart();
void initSystem();

// 是否首次使用系统
bool isFirstStart()
{
    LittleFS.begin();
    return !LittleFS.exists(CONFIG_FILE_PATH);
}

// 创建WiFi配置页面文件
void _writeInitWebFile()
{
    bool status = writeFile(WEB_CONFIG_PATH, R"(<!DOCTYPE html> <html> <head> <meta charset="UTF-8" /> <meta name="viewport" content="width=device-width, initial-scale=1.0" /> <title>OneLink开机棒</title> <style> body { font-family: Arial, sans-serif; background-color: #f0f0f0; } .container { margin: 0 auto; padding: 50px; max-width: 400px; background-color: #fff; border-radius: 5px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); } .container h1 { margin: 0 0 20px; font-size: 24px; text-align: center; } .container input { width: 100%; padding: 10px; margin: 10px; border: 1px solid #ccc; border-radius: 5px; } .container button { width: 100%; padding: 10px; margin: 10px 0; border: 0; border-radius: 5px; background-color: #4caf50; color: #fff; font-size: 16px; cursor: pointer; } .form { display: flex; flex-direction: column; align-items: center; } </style> </head> <body> <div class="container"> <h1>欢迎使用 OneLink开机棒</h1> <form class="form" action="/setup" method="post"> <input type="text" name="ssid" placeholder="WiFi 账号" required /> <input type="password" name="password" placeholder="WiFi 密码" required /> <button type="submit">连接 WiFi</button> </form> </div> </body> <script> const form = document.querySelector(".form"); form.addEventListener("submit", (e) => { e.preventDefault(); const ssid = form.ssid.value; const password = form.password.value; fetch("/setup", { method: "POST", headers: { "Content-Type": "application/json", }, body: JSON.stringify({ ssid, password }), }) .then((res) => res.json()) .then((data) => { if (data.success) { alert("WiFi 连接成功，设备正在重启，请稍后访问设备IP地址"); } else { alert("WiFi 连接失败，请检查 WiFi账号和密码是否正确"); } }); }); </script> </html>)");
    if (status)
        Serial.println("Web Config File Created!");
    else
        Serial.println("Web Config File Failed to Create!");
}

// 首次启动系统
void initSystem()
{
    formatFileSystem();
    initSystemConfig();

    _writeInitWebFile();

    createInitServer();
}

#endif
