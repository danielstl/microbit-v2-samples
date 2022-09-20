#pragma once

#include <I2C.h>
#include "NMEAParser.h"

namespace codal
{

/**
 * Global positioning driver for the U-BLOX ZOE-M8Q sensor
 */
class ZOEM8QGlobalPosition : public NMEAParser
{
public:
    /**
     * Constructor for the driver
     * @param _i2c the I2C instance to read data from
     */
    explicit ZOEM8QGlobalPosition(I2C &_i2c);

    void autoDetect() override;

private:
    I2C * _i2c;

    void periodicCallback() override;
};

} // namespace codal