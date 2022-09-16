#include "inc/GlobalPosition.h"
#include "inc/ZOEM8QGlobalPosition.h"
#include "MicroBit.h"
#include "MicroBitDevice.h"

MicroBit uBit;

struct GNGGAMessage {
    float utc;
    double lat;
    char lat_dir;
    double lon;
    char lon_dir;
    uint8_t quality;
    uint8_t sats;
    float hdop;
    double alt;
    char a_units;
    float undulation;
    char u_units;
    //uint8_t age; always empty
};

void parseGNGGAMessage(char* message) {
    if (strncmp(message, "$GNGGA", 5) != 0) {
        return;
    }

    int len = strlen(message);

    int fieldStartIndexes[15] = {};

    int fieldNum = 1;

    fieldStartIndexes[0] = 0;

    for (int index = 0; index < len; index++) {
        if (message[index] == ',') {
            fieldStartIndexes[fieldNum++] = index + 1;
            message[index] = '\0';
        }

        if (fieldNum == 14) {
            break; // don't continue parsing after this point, we should have all our fields
        }
    }

    if (fieldNum != 14) {
        DMESG("Invalid GNGGA message, too few fields");
        return;
    }

    char* utc = message + fieldStartIndexes[1];
    char* lat = message + fieldStartIndexes[2];
    char* lat_dir = message + fieldStartIndexes[3];
    char* lon = message + fieldStartIndexes[4];
    char* lon_dir = message + fieldStartIndexes[5];
    char* quality = message + fieldStartIndexes[6];
    char* sats = message + fieldStartIndexes[7];
    char* hdop = message + fieldStartIndexes[8];
    char* alt = message + fieldStartIndexes[9];
    char* a_units = message + fieldStartIndexes[10];
    char* undulation = message + fieldStartIndexes[11];
    char* u_units = message + fieldStartIndexes[12];
    char* age = message + fieldStartIndexes[13];
    char* station = message + fieldStartIndexes[14];

    GNGGAMessage parsed;

    parsed.utc = strtof(utc, nullptr);

    parsed.lat_dir = lat_dir[0];
    float latRaw = strtof(lat, nullptr);
    parsed.lat = (floor(latRaw / 100) + fmod(latRaw, 100) / 60) * (parsed.lat_dir == 'S' ? -1 : 1);

    parsed.lon_dir = lon_dir[0];
    float lonRaw = strtof(lon, nullptr);
    parsed.lon = (floor(lonRaw / 100) + fmod(lonRaw, 100) / 60) * (parsed.lon_dir == 'W' ? -1 : 1);

    parsed.quality = strtol(quality, nullptr, 10);
    parsed.sats = strtol(sats, nullptr, 10);
    parsed.hdop = strtof(hdop, nullptr);
    parsed.alt = strtof(alt, nullptr);
    parsed.a_units = a_units[0];
    parsed.undulation = strtof(undulation, nullptr);
    parsed.u_units = u_units[0];

    // casting to int since it's hard to log floats!
    DMESGF("GNGGA! utc: %d, lat: %d, lon: %d, alt: %d", (int) parsed.utc, (int) (parsed.lat * 1000), (int) (parsed.lon * 1000), (int) (parsed.alt * 1000));
}

int main()
{
    uBit.init();

    ManagedBuffer message = ManagedBuffer(255);
    int messageLen = 0;

    while (1) {
        uBit.sleep(80);
        uint8_t res[2] = {0};

        if (uBit.i2c.readRegister(0x42 << 1, 0xfd, res, 1, true) != DEVICE_OK || uBit.i2c.readRegister(0x42 << 1, 0xfe, res + 1, 1, true) != DEVICE_OK) {
            DMESG("I2C error reading GPS!!");
            continue;
        }

        int bytes = res[0] << 8 | res[1];

        if (bytes > 0)
        {
            char *read = (char *)malloc(bytes);

            uBit.i2c.read(0x42 << 1, (uint8_t*) read, bytes, false);
            int bufferLen = message.length();

            for (int i = 0; i < bytes; i++) {
                bool appendToString = messageLen > 0;

                if (messageLen == 0 || (messageLen >= bufferLen)) { // wait until the start of a new message. we can't exceed buffer length either

                    if (read[i] == '$') {
                        messageLen = 0;
                        appendToString = true;
                    } else {
                        continue;
                    }
                }

                if (appendToString) {
                    if (read[i] == '\n') { // end of string!
                        message.setByte(messageLen, '\0');

                        parseGNGGAMessage((char*) message.getBytes());

                        messageLen = 0;
                    } else {
                        message.setByte(messageLen++, read[i]);
                    }
                }
            }

            free(read);
        }
    }
}

int main0()
{
    uBit.init();

    GlobalPosition* gps = new ZOEM8QGlobalPosition(uBit.i2c);

    while (1) {
        uBit.sleep(100);
        DMESG("lat %d lon %d alt %d", (int) (gps->latitude * 1000), (int) (gps->longitude * 1000), (int) (gps->altitude * 1000));
    }
}