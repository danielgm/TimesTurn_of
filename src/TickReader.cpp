#include "TickReader.h"

void TickReader::setup(ofSerial &s, int nInputs) {
  serial = &s;

  numInputs = nInputs;
  numTicks = new int[numInputs];
}

void TickReader::update() {
  for (int i = 0; i < numInputs; i++) {
    numTicks[i] = 0;
  }

  char c;
  while (serial->available()) {
    c = serial->readByte();
    numTicks[ofToInt(ofToString(c))]++;
  }
}

int TickReader::getNumInputs() {
  return numInputs;
}

int TickReader::getNumTicks(int input) {
  return numTicks[input];
}

