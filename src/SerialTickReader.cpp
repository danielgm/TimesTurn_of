#include "SerialTickReader.h"

void SerialTickReader::setup(ofSerial &s, int nChannels) {
  serial = &s;
}

void SerialTickReader::update() {
}

bool SerialTickReader::hasNext() {
  return serial->available();
}

Tick SerialTickReader::next() {
  Tick tick;

  if (serial->available()) {
    char c = serial->readByte();

    tick.channel = ofToInt(ofToString(c));
    tick.time = ofGetElapsedTimeMillis();
  }
  else {
    tick.channel = -1;
    tick.time = 0;
  }

  return tick;
}

