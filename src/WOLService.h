#ifndef BOOTSERVICE_H
#define BOOTSERVICE_H

#include <WiFiUDP.h>
#include "CONST.h"
#include <SPI.h>
#include <WiFiUdp.h>

WiFiUDP UDP;

class WOLService
{
public:
    static void sendWOL(IPAddress addr, byte *mac, size_t size_of_mac)
    {

        byte preamble[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        byte i;

        UDP.beginPacket(addr, 9);
        UDP.write(preamble, sizeof preamble);
        for (i = 0; i < 16; i++)
        {
            UDP.write(mac, size_of_mac);
        }
        UDP.endPacket();
    }

    static void BootService()
    {
        UDP.begin(9);
    }
};

void useWOL()
{
    WOLService::BootService();
}

#endif
