#pragma once

#include "ofMain.h"
#include "ITickReader.h"

class SerialTickReader
: public ITickReader {

  public:
    void setup(ofSerial &serial, int nChannels);
    void update();

    bool hasNext();
    Tick next();

  private:
    ofSerial* serial;
    int numChannels;
};
