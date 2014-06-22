#pragma once

#include "ofMain.h"
#include "ITickReader.h"

class SerialTickReader
: public ITickReader {

  public:
    void setup(ofSerial &serial, int nChannels);
    void update();

    int getNumChannels();
    int getNumTicks(int channel);

  private:
    ofSerial* serial;
    int numChannels;
    int* numTicks;
};
