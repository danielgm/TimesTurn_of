#pragma once

#include "ofMain.h"

class TickReader {

  public:
    void setup();
    void update();

    int getNumInputs();
    int getNumTicks(int input);

  private:
    int numInputs;
    int* numTicks;
};
