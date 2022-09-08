#include "MicroBit.h"
#include "MicroBitDevice.h"

MicroBit uBit;

struct GNGGAMessage {
    uint16_t utc;
    double lat;
    uint8_t lat_dir;
    double lon;
    uint8_t lon_dir;
    uint8_t quality;
    uint8_t sats;
    float hdop;
    double alt;
    uint8_t a_units;
    float undulation;
    uint8_t u_units;
    uint8_t age;
};

void parseGNGGAMessage(char* message) {
    if (strncmp(message, "$GNGGA", 5) == 0) {
        DMESGF("new gngga: %s", message);
    }

    int index = 6;


}

int main()
{
    uBit.init();

    ManagedBuffer message = ManagedBuffer(255);
    int messageLen = 0;

    while (1) {
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