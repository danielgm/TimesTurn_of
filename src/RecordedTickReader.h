#pragma once

#include "ofMain.h"
#include "ITickReader.h"

class RecordedTickReader
: public ITickReader {

  public:
    void setup(string filepath, int nInputs);
    void update();

    int getNumInputs();
    int getNumTicks(int input);

  private:
    bool processLine(string line);

    long startTime;
    ofBuffer fileBuffer;
    string savedLine;
    int numInputs;
    int* numTicks;
};
