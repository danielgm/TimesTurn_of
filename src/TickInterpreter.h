#pragma once

#include <list>

#include "ofMain.h"
#include "ofxMacamPs3Eye.h"
#include "ITickReader.h"

#define TICK_INTERPRETER_DURATION 2000

class TickInterpreter {

  public:
    void setup(ITickReader* tickReader, int nChannels);
    void update();

    float getVelocity(int channel);

  private:
    ITickReader* tickReader;
    int numChannels;
    std::list<Tick>* ticks;
};
