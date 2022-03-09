#include <CodalFS.h>
#include "MicroBit.h"

MicroBit uBit;

int main()
{
    uBit.init();

    //uBit.log.setVisibility(false);//.clear(true);

    // 131072 bytes
    auto filesystem = uBit.filesystem;

    filesystem.init();

    DMESG("about to format");
    filesystem.format();
    DMESG("formatted");

    int res;

    res = filesystem.createDirectory("daniel");
    DMESG("daniel %d", res);
    res = filesystem.createDirectory("daniel/test4");
    DMESG("daniel/test4 %d", res);
    res = filesystem.createDirectory("daniel/test5");
    DMESG("daniel/test5 %d", res);
    res = filesystem.createDirectory("daniel/test10");
    DMESG("daniel/test10 %d", res);
    res = filesystem.createDirectory("daniel/test5/nested");
    DMESG("daniel/test5/nested %d", res);
    res = filesystem.createDirectory("daniel/test5/nested/again");
    DMESG("daniel/test5/nested/again %d", res);
    res = filesystem.createDirectory("daniel/test5/nested/again/12345");
    DMESG("daniel/test5/nested/again/12345 %d", res);
    res = filesystem.createDirectory("daniel/test5/nested/again/limittesting0000");
    DMESG("daniel/test5/nested/again/limittesting0000 %d", res);
    res = filesystem.createDirectory("daniel/test5/nested/again/limittesting6666");
    DMESG("daniel/test5/nested/again/limittesting6666 %d", res);
    res = filesystem.createDirectory("daniel/test5/nested/again/limittesting777");
    DMESG("daniel/test5/nested/again/limittesting777 %d", res);
    res = filesystem.createDirectory("daniel/test5/nested/again/limittesting888");
    DMESG("daniel/test5/nested/again/limittesting888 %d", res);
    res = filesystem.createDirectory("daniel/test5/nested/again/limittesting11111");
    DMESG("daniel/test5/nested/again/limittesting11111 %d", res);

    auto handle = filesystem.open("daniel/test5/file.txt", FS_WRITE | FS_CREAT);

    res = filesystem.write(handle, (uint8_t *) "TESTTEST", 9);
    filesystem.close(handle);

    handle = filesystem.open("daniel/test5/file2.txt", FS_WRITE | FS_CREAT);

    res = filesystem.write(handle, (uint8_t *) "TESTTEST", 9);
    filesystem.close(handle);

    auto longfile = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed tempor dui quis pellentesque vehicula. Vivamus ornare maximus magna vitae ultrices. Donec sem est, posuere non semper nec, luctus a enim. Mauris molestie blandit ultricies. Phasellus volutpat ac odio non vulputate. Ut mattis lacinia eros non faucibus. Phasellus auctor convallis rutrum. Nullam rhoncus nunc id massa bibendum, lobortis dapibus metus mollis. Vivamus non neque at nibh tincidunt varius at eu tellus. Nulla facilisi. Etiam auctor porta rutrum. Curabitur in malesuada purus. Mauris id consequat metus. Sed id vestibulum massa. Donec eget enim in diam commodo luctus a ac sapien.\n"
                    "\n"
                    "Curabitur convallis laoreet felis, vitae facilisis arcu consequat sed. Quisque in velit eu arcu condimentum fringilla sed sed orci. Nunc semper tempor massa placerat mollis. Proin non iaculis velit, sed fermentum dolor. Sed sit amet turpis luctus, congue sapien fermentum, tincidunt elit. Vestibulum ultrices magna nisi. Fusce magna sapien, egestas in neque nec, laoreet ullamcorper urna. Morbi eget condimentum magna. Nullam sit amet turpis augue. Nam id eleifend arcu, sed ultrices ipsum. Sed ac felis ac nisl ornare pharetra non sit amet velit. Morbi interdum aliquam feugiat. Nullam ipsum lorem, congue quis egestas at, pulvinar nec est. Phasellus a fermentum justo.\n"
                    "\n"
                    "Fusce at metus vel ante pellentesque tincidunt. Proin faucibus nunc aliquam, accumsan ex a, interdum arcu. In ac ante rutrum, pulvinar sem ac, vestibulum tellus. Maecenas at odio vel libero vestibulum tincidunt ac a metus. Quisque posuere rhoncus pretium. Vivamus porttitor lectus eget arcu sagittis maximus eget non eros. Ut interdum blandit convallis. Nunc sagittis aliquet est vel scelerisque. Integer nec viverra nunc. Cras convallis leo vitae pulvinar sollicitudin. Nunc eu gravida nulla.\n"
                    "\n"
                    "Vestibulum quis ipsum quis velit dapibus condimentum. In orci ex, cursus dapibus eros gravida, ullamcorper viverra odio. Nulla vitae ante posuere, pellentesque mi et, efficitur arcu. Morbi ac mauris nec urna vehicula ultrices. In ut turpis nibh. Nulla facilisi. Aenean sed lectus et augue dictum facilisis.\n"
                    "\n"
                    "Proin porta eros nec ex bibendum ornare. Curabitur vel mi urna. Donec ut aliquet elit, a pharetra enim. Maecenas convallis posuere enim at ultrices. Sed rutrum leo vitae lectus varius lacinia. Maecenas est erat, sodales lobortis imperdiet ut, placerat ac urna. Phasellus vitae sollicitudin purus. In cursus neque ut purus gravida, id aliquet felis convallis. Pellentesque mollis pretium urna, scelerisque euismod arcu lobortis ut. Maecenas porttitor blandit magna sit amet convallis. Cras at viverra est. Morbi sit amet quam porta dui imperdiet egestas. Donec accumsan ultricies mauris, a volutpat sapien vulputate in. Praesent eget ante fermentum, suscipit mauris a, laoreet nisi. Donec feugiat, nunc euismod vestibulum fermentum, ligula sapien iaculis erat, sed sodales turpis risus nec diam. Interdum et malesuada fames ac ante ipsum primis in faucibus.\n"
                    "\n"
                    "Sed leo nunc, egestas ut varius a, finibus a odio. Praesent lorem libero, rhoncus id posuere id, sollicitudin quis magna. Donec viverra eros id ligula iaculis, et pretium justo cursus. Etiam tincidunt tristique elit, sit amet egestas sapien consectetur vel. Vivamus non felis a turpis venenatis sollicitudin. In hac habitasse platea dictumst. Sed vel ultrices ipsum.\n"
                    "\n"
                    "Donec gravida porta maximus. Donec volutpat sed turpis non lacinia. In egestas sem ac nunc auctor accumsan. Nunc consequat bibendum ante, vitae tempor ipsum venenatis vel. Praesent est turpis, aliquet eu egestas a, volutpat eu mi. Etiam sagittis ut neque id mollis. Nulla non dolor mi. Nunc vestibulum ante vel odio hendrerit, a viverra purus rhoncus. Nunc orci tellus, rhoncus eget fringilla sed, vestibulum in massa. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.\n"
                    "\n"
                    "Fusce viverra tincidunt odio non sagittis. Morbi ullamcorper dui id efficitur cursus. Nullam at felis et diam condimentum varius. Phasellus accumsan, sem nec vestibulum hendrerit, mauris nunc pharetra quam, ut consequat lorem eros eu ipsum. Sed posuere purus vitae justo blandit, mollis facilisis nisl volutpat. Etiam feugiat metus vitae semper porttitor. Praesent ac ante venenatis, lobortis elit ut, ornare ante. Proin feugiat augue vitae nulla tempor posuere. Quisque quis risus non justo congue facilisis. Ut sollicitudin vulputate mauris ut porttitor. Vestibulum ac mauris cursus, molestie quam ut, elementum nulla. Suspendisse potenti. Fusce fermentum sit amet urna id efficitur. Nullam non dapibus eros. Nam aliquam velit nec libero maximus tincidunt.\n"
                    "\n"
                    "In fringilla sapien eu metus porta, nec fringilla nisl venenatis. Suspendisse viverra, nunc nec ornare vehicula, massa dui lobortis erat, lacinia venenatis est augue in magna. Suspendisse efficitur tempor scelerisque. Quisque tristique, sapien ut egestas aliquam, urna nibh dapibus dolor, a lacinia lacus mauris quis lectus. Cras consectetur, massa nec eleifend facilisis, neque ipsum porttitor.";

    handle = filesystem.open("longfile.txt", FS_WRITE | FS_CREAT);

    filesystem.write(handle, (uint8_t *) longfile, strlen(longfile));
    filesystem.close(handle);

   // filesystem.debug_print_directory(nullptr);

    auto usb = uBit.flash;//new MicroBitUSBFlashManager(uBit.i2c, uBit.io, uBit.power);

    MicroBitUSBFlashConfig config;

    config.fileName = "MY_FILES.HTM";
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

    // filesystem.debug_print_entire_filesystem();

    // filesystem.debug_print_root_dirent();

    /*filesystem.createDirectory("helloworld");

    filesystem.createDirectory("daniel");
    handle = filesystem.open("daniel/test6.txt", FS_READ);

    auto *buffer = new uint8_t[4];

    res = filesystem.read(handle, buffer, 4);
    filesystem.close(handle);

    DMESG((char *) buffer);

    return -1;

    filesystem.debug_print_directory("daniel");

    if (filesystem.createDirectory("Test1005") == DEVICE_OK)
    {
        DMESG("creating!!!");

        filesystem.createDirectory("daniel");
        auto handle = filesystem.open("daniel/test.txt", FS_WRITE | FS_CREAT);

        filesystem.write(handle, (uint8_t *) "abcdefghijklmnopqrstuvwxyz", 27);
        filesystem.close(handle);

        int stored = 1;
        uBit.storage.put("created_test_1", (uint8_t *) &stored, sizeof(int));
    } else
    {
        DMESG("read!");

        auto handle = filesystem.open("daniel/test.txt", FS_READ);

        auto *buffer = new uint8_t[27];

        auto res = filesystem.read(handle, buffer, 27);
        filesystem.close(handle);

        DMESG((char *) buffer);
    }

    release_fiber();*/
}