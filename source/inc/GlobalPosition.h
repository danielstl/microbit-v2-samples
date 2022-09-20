#pragma once

#include <CodalComponent.h>
#include <ManagedBuffer.h>
namespace codal
{

/**
 * Class definition for global positioning data
 */
class GlobalPosition
{

public:
    /**
     * The latest recorded latitude data, in degrees
     */
    double latitude;

    /**
     * The latest recorded longitude data, in degrees
     */
    double longitude;

    /**
     * The latest recorded altitude data
     */
    double altitude;
};
} // namespace codal