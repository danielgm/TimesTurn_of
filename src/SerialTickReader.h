#pragma once

#include <queue>

#include "ofMain.h"
#include "ITickReader.h"

#define SERIAL_TICK_READER_LOWER_THRESHOLD 600
#define SERIAL_TICK_READER_UPPER_THRESHOLD 700

class SerialTickReader
: public ITickReader {

  public:
    void setup(ofSerial &serial, int nChannels);
    void update();

    bool hasNext();
    Tick next();

  private:
    void processLine(string line);

    ofSerial* serial;
    ofBuffer buffer;
    std::queue<Tick> queue;
    int* direction;
    int numChannels;
};
