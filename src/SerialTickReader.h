#pragma once

#include <queue>

#include "ofMain.h"
#include "ITickReader.h"

class SerialTickReader
: public ITickReader {

  public:
    void setup(ofSerial &serial, int nChannels);
    void update();

    bool hasNext();
    Tick next();
    int getReading(int channel);
    int getLowerThreshold(int channel);
    int getUpperThreshold(int channel);

  private:
    void processLine(string line);

    ofSerial* serial;
    ofBuffer buffer;
    std::queue<Tick> queue;
    int* direction;
    int numChannels;
    int* readings;
    int* lowerThresholds;
    int* upperThresholds;
};
