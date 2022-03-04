#include <CodalFS.h>
#include "MicroBit.h"

MicroBit uBit;

int main()
{
    uBit.init();

    //uBit.log.setVisibility(false);//.clear(true);

    // 131072 bytes
    auto filesystem = new CodalFS(uBit.flash, 512);

    DMESG("about to format");
    filesystem->format();
    DMESG("formatted");

    int version = (int) uBit.power.readProperty(MICROBIT_UIPM_PROPERTY_I2C_VERSION)[0];

    DMESG("Version is %d", version);

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

    handle = filesystem->open("daniel/test5/file2.txt", FS_WRITE | FS_CREAT);

    res = filesystem->write(handle, (uint8_t *) "TESTTEST", 9);
    filesystem->close(handle);

    filesystem->debug_print_directory(nullptr);

    DMESGF("AAA");

    DMESGF("button A pressed!");

    auto usb = uBit.flash;//new MicroBitUSBFlashManager(uBit.i2c, uBit.io, uBit.power);

    MicroBitUSBFlashConfig config;

    config.fileName = "AA_FILES.HTM";
    config.fileSize = usb.getFlashEnd() - usb.getFlashStart() - usb.getPageSize();
    config.visible = true;

    DMESGF("setting config");

    usb.setConfiguration(config, false);

    DMESGF("config set");

    DMESGF("encoding...");

    usb.setHexEncodingWindow(4096, usb.getFlashEnd());

    DMESGF("done");

    usb.remount();

    DMESGF("remounted");

    while(1);

    release_fiber();

    return -1;

    // filesystem->debug_print_entire_filesystem();

    // filesystem->debug_print_root_dirent();

    /*filesystem->createDirectory("helloworld");

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

    release_fiber();*/
}