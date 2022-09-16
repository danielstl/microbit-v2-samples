//
// Created by Daniel on 12/09/2022.
//

#include <CodalDmesg.h>
#include "../inc/ZOEM8QGlobalPosition.h"

namespace codal
{

ZOEM8QGlobalPosition::ZOEM8QGlobalPosition(I2C &_i2c) : NMEAParser(), _i2c(_i2c) {}

void ZOEM8QGlobalPosition::periodicCallback()
{
    uint8_t res[2] = {0};

    if (_i2c.readRegister(0x42 << 1, 0xfd, res, 1, true) != DEVICE_OK ||
        _i2c.readRegister(0x42 << 1, 0xfe, res + 1, 1, true) != DEVICE_OK)
    {
        DMESG("I2C error reading GPS!!");
        return;
    }

    int bytes = res[0] << 8 | res[1]; // length of available bytes to read

    if (bytes > 0)
    {
        char *read = (char *)malloc(bytes);

        _i2c.read(0x42 << 1, (uint8_t *)read, bytes, false);
        int bufferLen = _buffer.length();

        for (int i = 0; i < bytes; i++)
        {
            bool appendToString = _bufferWritePos > 0;

            if (_bufferWritePos == 0 || (_bufferWritePos >= bufferLen))
            { // wait until the start of a new message. we can't exceed buffer length either

                if (read[i] == '$')
                {
                    _bufferWritePos = 0;
                    appendToString = true;
                }
                else
                {
                    continue;
                }
            }

            if (appendToString)
            {
                if (read[i] == '\n')
                { // end of string!
                    _buffer.setByte(_bufferWritePos, '\0');

                    parse();
                }
                else
                {
                    _buffer.setByte(_bufferWritePos++, read[i]);
                }
            }
        }

        free(read);
    }
}

void ZOEM8QGlobalPosition::autoDetect()
{
    NMEAParser::autoDetect();
}

} // namespace codal