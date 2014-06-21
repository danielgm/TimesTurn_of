#include "SerialTickReader.h"

void SerialTickReader::setup(ofSerial &s, int nInputs) {
  serial = &s;

  numInputs = nInputs;
  numTicks = new int[numInputs];
}

void SerialTickReader::update() {
  for (int i = 0; i < numInputs; i++) {
    numTicks[i] = 0;
  }

  char c;
  while (serial->available()) {
    c = serial->readByte();
    numTicks[ofToInt(ofToString(c))]++;
  }
}

int SerialTickReader::getNumInputs() {
  return numInputs;
}

int SerialTickReader::getNumTicks(int input) {
  return numTicks[input];
}

