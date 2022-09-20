#include "inc/GlobalPosition.h"
#include "inc/ZOEM8QGlobalPosition.h"
#include "MicroBit.h"
#include "MicroBitDevice.h"

MicroBit uBit;

int main()
{
    uBit.init();

    GlobalPosition* gps = new ZOEM8QGlobalPosition(uBit.i2c);

    while (1) {
        uBit.sleep(100);
        DMESG("lat %d lon %d alt %d", (int) (gps->latitude * 1000), (int) (gps->longitude * 1000), (int) (gps->altitude * 1000));
    }
}