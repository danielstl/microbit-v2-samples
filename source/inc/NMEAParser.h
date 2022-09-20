#pragma once

#include <CodalComponent.h>
#include "GlobalPosition.h"
namespace codal
{

/**
 * Class definition for a component which reads NMEA data from an external sensor periodically,
 * and exposes the data in a consistent format
 */
class NMEAParser : CodalComponent, public GlobalPosition
{

public:
    NMEAParser();
    virtual void autoDetect(); // todo docs

protected:
    /**
     * The internal buffer which messages are written into before being processed
     */
    ManagedBuffer _buffer;

    /**
     * The number of bytes written into the buffer
     */
    uint8_t _bufferWritePos = 0;

    /**
     * Notifies the parser that its data buffer is full with a message and ready to be parsed
     */
    void parse();

private:
    void periodicCallback() override;

    /**
     * Interprets the message buffer as a GNGGA message and attempts to parse appropriately
     */
    void _parseGNGGA();
};

} // namespace codal