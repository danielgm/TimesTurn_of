#pragma once

#include "ofMain.h"
#include "ITickReader.h"

class RecordedTickReader
: public ITickReader {

  public:
    void setup(string filepath, int nChannels);
    void update();

    bool hasNext();
    Tick next();

  private:
    Tick processLine(string line);

    long startTime;
    ofBuffer fileBuffer;
    Tick nextTick;
    int numChannels;
};
