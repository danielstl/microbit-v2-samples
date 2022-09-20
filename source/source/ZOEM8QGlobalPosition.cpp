#include <CodalDmesg.h>
#include "../inc/ZOEM8QGlobalPosition.h"

namespace codal
{

ZOEM8QGlobalPosition::ZOEM8QGlobalPosition(I2C &_i2c) : NMEAParser()
{
    this->_i2c = &_i2c;
}

void ZOEM8QGlobalPosition::periodicCallback()
{
    /*
     * We can read data from the 0xFD and 0xFE registers in order to determine the amount of bytes
     * available to be read
     */

    uint8_t res[2] = {0};

    if (_i2c->readRegister(0x42 << 1, 0xfd, res, 1, true) != DEVICE_OK ||
        _i2c->readRegister(0x42 << 1, 0xfe, res + 1, 1, true) != DEVICE_OK)
    {
        DMESG("I2C error reading GPS length!!");
        return;
    }

    int totalBytes = res[0] << 8 | res[1]; // length of available bytes to read

    while (totalBytes > 0) // keep reading all available bytes, 128 at a time
    {
        int bytesToRead = totalBytes < 128 ? totalBytes : 128;
        char *read = (char *)malloc(bytesToRead);

        if (_i2c->read(0x42 << 1, (uint8_t *)read, bytesToRead, false) != DEVICE_OK)
        {
            DMESG("I2C error reading GPS!!");
            return;
        }

        int bufferLen = _buffer.length();

        for (int i = 0; i < bytesToRead; i++)
        {
            /*
             * We shouldn't immediately write to the buffer - we should make sure that the start
             * of the buffer is the start of a NMEA message so that we don't have a partial message.
             *
             * So, if our buffer is currently empty, and the byte is not a '$' (indicating the start
             * of a message), we should just drop the byte and ignore the partial message until
             * the next one.
             *
             * Also, if our message ends up exceeding the 128 byte limit of the buffer, we will also
             * drop it - NMEA messages shouldn't be this long!
             */
            bool appendToString = _bufferWritePos > 0;

            if (_bufferWritePos == 0 || (_bufferWritePos >= bufferLen))
            { // wait until the start of a new message. we can't exceed buffer length either

                if (read[i] == '$')
                {
                    // found the start of a message, make sure we write to the beginning of the
                    // buffer
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
                if (read[i] == '\n') // end of string!
                {
                    _buffer.setByte(_bufferWritePos, '\0');

                    parse(); // message is complete, so parse to get the latest data
                }
                else
                {
                    _buffer.setByte(_bufferWritePos++, read[i]);
                }
            }
        }

        free(read);

        totalBytes -= bytesToRead;
    }
}

void ZOEM8QGlobalPosition::autoDetect()
{
    NMEAParser::autoDetect();
}

} // namespace codal