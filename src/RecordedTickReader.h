#pragma once

#include "ofMain.h"
#include "ITickReader.h"

class RecordedTickReader
: public ITickReader {

  public:
    void setup(string filepath, int nChannels);
    void update();

    int getNumChannels();
    int getNumTicks(int channel);

  private:
    bool processLine(string line);

    long startTime;
    ofBuffer fileBuffer;
    string savedLine;
    int numChannels;
    int* numTicks;
};
