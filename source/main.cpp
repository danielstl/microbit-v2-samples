#include <CodalFS.h>
#include "MicroBit.h"

MicroBit uBit;

void buttonAEvent(MicroBitEvent)
{
    auto usb = uBit.flash;//new MicroBitUSBFlashManager(uBit.i2c, uBit.io, uBit.power);

    MicroBitUSBFlashConfig config;

    config.fileName = "MY_FILES.HTM";
    config.fileSize = usb.getFlashEnd() - usb.getFlashStart() - usb.getPageSize();
    config.visible = true;

    usb.setConfiguration(config, false);

    ManagedBuffer encodingWindowCommand(9);

    encodingWindowCommand[0] = 0x09; // set encoding window

    uint32_t encodingStart = 0;
    uint32_t encodingEnd = config.fileSize;

    encodingWindowCommand[4] = encodingStart; // encoding window start
    encodingWindowCommand[3] = encodingStart >> 8; // encoding window start
    encodingWindowCommand[2] = encodingStart >> 16; // encoding window start
    encodingWindowCommand[1] = encodingStart >> 24; // encoding window start

    encodingWindowCommand[8] = encodingEnd; // encoding window
    encodingWindowCommand[7] = encodingEnd >> 8; // encoding window
    encodingWindowCommand[6] = encodingEnd >> 16; // encoding window
    encodingWindowCommand[5] = encodingEnd >> 24; // encoding window

    usb.transact_DEBUG(encodingWindowCommand, 2);

    usb.remount();
}

int main()
{
    uBit.init();

    //uBit.log.clear(true);

    uBit.buttonA.enable();
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, buttonAEvent,
                           MESSAGE_BUS_LISTENER_IMMEDIATE);

    // 131072 bytes
    auto filesystem = new CodalFS(uBit.flash, 512);

    //filesystem->format();

    int version = (int) uBit.power.readProperty(MICROBIT_UIPM_PROPERTY_I2C_VERSION)[0];

    DMESG("Version is %d", version);

    filesystem->format();

    int res;

    res = filesystem->createDirectory("daniel");
    DMESG("daniel %d", res);
    res = filesystem->createDirectory("daniel/test4");
    DMESG("daniel/test4 %d", res);
    res = filesystem->createDirectory("daniel/test5");
    DMESG("daniel/test5 %d", res);
    res = filesystem->createDirectory("daniel/test10");
    DMESG("daniel/test10 %d", res);
    res = filesystem->createDirectory("daniel/test5/nested");
    DMESG("daniel/test10/nested %d", res);
    res = filesystem->createDirectory("daniel/test5/nested/again");
    DMESG("daniel/test10/nested/again %d", res);
    res = filesystem->createDirectory("daniel/test5/nested/again/limittesting0000");
    DMESG("daniel/test5/nested/again/limittesting0000 %d", res);
    res = filesystem->createDirectory("daniel/test5/nested/again/limittesting888");
    DMESG("daniel/test5/nested/again/limittesting888 %d", res);
    res = filesystem->createDirectory("daniel/test5/nested/again/limittesting11111");
    DMESG("daniel/test5/nested/again/limittesting11111 %d", res);

    auto handle = filesystem->open("daniel/test5/file.txt", FS_WRITE | FS_CREAT);

    res = filesystem->write(handle, (uint8_t *) "TESTTEST", 9);
    filesystem->close(handle);

    handle = filesystem->open("daniel/test5/file.txt", FS_WRITE | FS_CREAT);

    res = filesystem->write(handle, (uint8_t *) "TESTTEST", 9);
    filesystem->close(handle);

    filesystem->debug_print_directory(nullptr);

    DMESGF("AAA");

    release_fiber();

    return -1;

    // filesystem->debug_print_entire_filesystem();

    // filesystem->debug_print_root_dirent();

    filesystem->createDirectory("helloworld");

    filesystem->createDirectory("daniel");
    handle = filesystem->open("daniel/test6.txt", FS_READ);

    auto *buffer = new uint8_t[4];

    res = filesystem->read(handle, buffer, 4);
    filesystem->close(handle);

    DMESG((char *) buffer);

    return -1;

    filesystem->debug_print_directory("daniel");

    if (filesystem->createDirectory("Test1005") == DEVICE_OK)
    {
        DMESG("creating!!!");

        filesystem->createDirectory("daniel");
        auto handle = filesystem->open("daniel/test.txt", FS_WRITE | FS_CREAT);

        filesystem->write(handle, (uint8_t *) "abcdefghijklmnopqrstuvwxyz", 27);
        filesystem->close(handle);

        int stored = 1;
        uBit.storage.put("created_test_1", (uint8_t *) &stored, sizeof(int));
    } else
    {
        DMESG("read!");

        auto handle = filesystem->open("daniel/test.txt", FS_READ);

        auto *buffer = new uint8_t[27];

        auto res = filesystem->read(handle, buffer, 27);
        filesystem->close(handle);

        DMESG((char *) buffer);
    }

    release_fiber();
}