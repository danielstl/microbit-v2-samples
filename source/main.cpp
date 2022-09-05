#include "MicroBit.h"
#include "MicroBitDevice.h"

MicroBit uBit;

struct GPGGAMessage {
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

int main()
{
    uBit.init();
    //uBit.serial.init();

    //uBit.log.clear();

    //ManagedBuffer buffer = ManagedBuffer(255);
    int index = 0;

    //uBit.i2c.clearBus();

    while (1) {
        uBit.sleep(100);

        uint8_t* res = new uint8_t[2];
        int resCode = uBit.i2c.readRegister(0x42, 0xfd, res, 1, true);
        int resCode2 = uBit.i2c.readRegister(0x42, 0xfe, res + 1, 1, true);


        //buffer.setByte(index, res);

        /*if (res < 255) {
            if (res == 10) {
                auto str = ManagedString(buffer).toCharArray();
                DMESGF(str);

                if (strncmp(str, "$GPGGA", 5) == 0) {


                }
            }
        }*/

        //uBit.sleep(1000);
        //uint8_t* data = (uint8_t*) malloc(100);
        //uBit.i2c.read(0x42, data, 100);
        DMESG("%c", res);

        index++;
    }
}