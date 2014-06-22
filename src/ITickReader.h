#pragma once

#include "ofMain.h"

class ITickReader {

  public:
    virtual void update() = 0;

    virtual int getNumChannels() = 0;
    virtual int getNumTicks(int channel) = 0;
};
