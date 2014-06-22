#include "SerialTickReader.h"

void SerialTickReader::setup(ofSerial &s, int nChannels) {
  serial = &s;

  numChannels = nChannels;
  numTicks = new int[numChannels];
}

void SerialTickReader::update() {
  for (int i = 0; i < numChannels; i++) {
    numTicks[i] = 0;
  }

  char c;
  while (serial->available()) {
    c = serial->readByte();
    numTicks[ofToInt(ofToString(c))]++;
  }
}

int SerialTickReader::getNumChannels() {
  return numChannels;
}

int SerialTickReader::getNumTicks(int channel) {
  return numTicks[channel];
}

