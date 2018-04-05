#include <Arduino.h>
#include "ELM327.h"

byte ELM327::begin(HardwareSerial * serial)
{
    long baudrates[] = {115200, 38400};
    byte version = 0;
    for (byte n = 0; n < sizeof(baudrates) / sizeof(baudrates[0]) && version == 0; n++) {
        serial->begin(baudrates[n]);
        // @TODO: Read version string returned by ATZ command
    }

    _serial = (Stream *)serial;

    return version;
}

byte ELM327::begin(SoftwareSerial * serial)
{
    long baudrates[] = {115200, 38400};
    byte version = 0;
    for (byte n = 0; n < sizeof(baudrates) / sizeof(baudrates[0]) && version == 0; n++) {
        serial->begin(baudrates[n]);
        // @TODO: Read version string returned by ATZ command
    }

    _serial = (Stream *)serial;

    return version;
}

byte ELM327::begin(HardwareSerial * serial, HardwareSerial * debug)
{
    byte version = begin(serial);
    debug->begin(38400);
    _debug = (Stream *)debug;

    return version;
}

byte ELM327::begin(SoftwareSerial * serial, SoftwareSerial * debug)
{
    byte version = begin(serial);
    debug->begin(38400);
    _debug = (Stream *)debug;

    return version;
}

byte ELM327::begin(HardwareSerial * serial, SoftwareSerial * debug)
{
    byte version = begin(serial);
    debug->begin(38400);
    _debug = (Stream *)debug;

    return version;
}

byte ELM327::begin(SoftwareSerial * serial, HardwareSerial * debug)
{
    byte version = begin(serial);
    debug->begin(38400);
    _debug = (Stream *)debug;

    return version;
}

bool ELM327::init(OBD2_PROTOCOLS protocol)
{
    const char *initstrings[] = {"ATZ\r", "ATE0\r", "ATL1\r"};
    char buff[64];

    for (uint8_t i = 0; i < sizeof(initstrings) / sizeof(initstrings[0]); i++) {
        write(initstrings[i]);
        if (receive(buff, sizeof(buff)) == 0) {
            return false;
        }
    }

    while (initString is = _initStrings.pop()) {
        write(is());
        if (receive(buff, sizeof(buff)) == 0) {
            return false;
        }
    }
    if (protocol != PROTO_AUTO) {
        sprintf_P(buff, PSTR("ATSP %u\r"), protocol);
        write(buff);
        if (receive(buff, sizeof(buff)) == 0 && !strstr(buff, "OK")) {
            return false;
        }
    }

    // @TODO: Load supported PIDs into cache
}

byte ELM327::receive(char* buffer, byte bufferSize)
{
    byte res;

    // @TODO: Do serial reading here

    if (_debug) {
        // @TODO: Better serial debugging
        _debug->write(buffer);
    }

    return res;
}

void ELM327::write(const char* s)
{
    _serial->write(s);

    if (_debug) {
        // @TODO: Better serial debugging
        _debug->write(s);
    }
}

uint8_t ELM327::addInitString(initString str)
{
    _initStrings.add(str);

    return (uint8_t) _initStrings.size() - 1;
}

void ELM327::removeInitString(uint8_t index)
{
    _initStrings.remove(index);
}

byte ELM327::getVersion()
{
    byte version = 0;

	return version;
}

bool ELM327::readPID(byte pid, int &result, byte num_results)
{
    return false;
}
