#pragma once

#include <I2C.h>
#include "NMEAParser.h"

namespace codal
{

class ZOEM8QGlobalPosition : public NMEAParser
{
public:
    ZOEM8QGlobalPosition(I2C &_i2c);
    ZOEM8QGlobalPosition();

    void autoDetect() override;

private:
    I2C _i2c;

    void periodicCallback() override;
};

} // namespace codal