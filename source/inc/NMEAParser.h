#pragma once

#include <CodalComponent.h>
#include "GlobalPosition.h"
namespace codal
{

class NMEAParser : CodalComponent, public GlobalPosition
{

public:
    NMEAParser();
    virtual void autoDetect();

    void parse();

protected:
    ManagedBuffer _buffer;
    uint8_t _bufferWritePos = 0;

private:
    void periodicCallback() override;

    void _parseGNGGA();
    //~NMEAParser() override;
};

} // namespace codal