#pragma once

#include "ofMain.h"

class ITickReader {

  public:
    virtual void update() = 0;

    virtual int getNumInputs() = 0;
    virtual int getNumTicks(int input) = 0;
};
