#pragma once

#include "ofMain.h"

class TickReader {

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
