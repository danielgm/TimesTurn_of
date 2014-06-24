#pragma once

#include "ofMain.h"

struct Tick {
  int channel;
  long time;
};

class ITickReader {

  public:
    virtual void update() = 0;

    virtual bool hasNext() = 0;
    virtual Tick next() = 0;
};
