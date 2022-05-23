#include <CodalFS.h>
#include "MicroBit.h"

MicroBit uBit;

#define WEBUSB_NO_OP                 0x00
#define WEBUSB_OP_PUSH_PATCH         0x01
#define WEBUSB_OP_REMOUNT            0x02
#define WEBUSB_OP_PRINT_MESSAGE      0x03
#define WEBUSB_OP_FORMAT_FS          0x04
#define WEBUSB_OP_RESPONSE_SUCCESS   0xFF

#define WEBUSB_DEBUG true

void myOnButtonB(MicroBitEvent)
{
   // CodalFS::webUsbBuffer[0] = WEBUSB_OP_FORMAT_FS;
}

int main()
{
    uBit.init();

    /*for (int i = 0; i < 256; i++)
    {
        CodalFS::webUsbBuffer[i] = 0;
    }

    CodalFS::webUsbBuffer[0] = WEBUSB_OP_RESPONSE_SUCCESS;*/

    uBit.buttonB.enable();
    uBit.messageBus.listen(DEVICE_ID_BUTTON_B, DEVICE_BUTTON_EVT_CLICK, myOnButtonB,
                           MESSAGE_BUS_LISTENER_IMMEDIATE);

    auto filesystem = CodalFS::defaultFileSystem;

    filesystem->init();

   // DMESGF("WebUSB interface @ %d", CodalFS::webUsbBuffer);

    release_fiber();

    return -1;
}