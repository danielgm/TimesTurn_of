#pragma once

#include <list>

#include "ofMain.h"
#include "ITickReader.h"

#define TICK_INTERPRETER_DELTAS_SIZE 50

class TickInterpreter {

  public:
    void setup(ITickReader* tickReader, int nChannels);
    void update();

    long getAverage(int channel);

  private:
    ITickReader* tickReader;
    int numChannels;
    std::list<long>* deltas;
    unsigned long long* prevTimes;
};
