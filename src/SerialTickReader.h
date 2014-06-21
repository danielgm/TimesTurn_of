#pragma once

#include "ofMain.h"
#include "ITickReader.h"

class SerialTickReader
: public ITickReader {

  public:
    void setup(ofSerial &serial, int nInputs);
    void update();

    int getNumInputs();
    int getNumTicks(int input);

  private:
    ofSerial* serial;
    int numInputs;
    int* numTicks;
};
