#include "SerialTickReader.h"

void SerialTickReader::setup(ofSerial &s, int nChannels) {
  serial = &s;

  direction = new int[numChannels];
  readings = new int[numChannels];
  for (int i = 0; i < numChannels; ++i) {
    direction[i] = 1;
    readings[i] = 0;
  }
}

void SerialTickReader::update() {
  while (serial->available()) {
    char c = serial->readByte();
    if (c == '\n') {
      processLine(buffer.getText());
      buffer.clear();
    }
    else {
      buffer.append(ofToString(c));
    }
  }
}

bool SerialTickReader::hasNext() {
  return queue.size() > 0;
}

Tick SerialTickReader::next() {
  Tick tick = queue.back();
  queue.pop();
  return tick;
}

int SerialTickReader::getReading(int channel) {
  return readings[channel];
}

void SerialTickReader::processLine(string line) {
  std::vector<string> tokens = ofSplitString(line, "\t");
  for (int c = 0; c < tokens.size(); ++c) {
    readings[c] = ofToInt(tokens[c]);
    if (readings[c] > SERIAL_TICK_READER_UPPER_THRESHOLD && direction[c] > 0) {
      Tick tick;
      tick.channel = c;
      tick.time = ofGetElapsedTimeMillis();
      queue.push(tick);

      direction[c] = -1;
    }
    else if (readings[c] < SERIAL_TICK_READER_LOWER_THRESHOLD && direction[c] < 0) {
      direction[c] = 1;
    }
  }
}

