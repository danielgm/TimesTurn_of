#include "SerialTickReader.h"

void SerialTickReader::setup(ofSerial &s, int nChannels) {
  serial = &s;
  numChannels = nChannels;

  direction = new int[numChannels];
  readings = new int[numChannels];
  lowerThresholds = new int[numChannels];
  upperThresholds = new int[numChannels];

  for (int i = 0; i < numChannels; ++i) {
    direction[i] = 1;
    readings[i] = 0;

    lowerThresholds[i] = 515;
    upperThresholds[i] = 530;
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

int SerialTickReader::getLowerThreshold(int channel) {
  return lowerThresholds[channel];
}

void SerialTickReader::setLowerThreshold(int channel, int threshold) {
  lowerThresholds[channel] = threshold;
}

int SerialTickReader::getUpperThreshold(int channel) {
  return upperThresholds[channel];
}

void SerialTickReader::setUpperThreshold(int channel, int threshold) {
  upperThresholds[channel] = threshold;
}

void SerialTickReader::processLine(string line) {
  std::vector<string> tokens = ofSplitString(line, "\t");
  for (int c = 0; c < tokens.size(); ++c) {
    readings[c] = ofToInt(tokens[c]);
    if (readings[c] > upperThresholds[c] && direction[c] > 0) {
      Tick tick;
      tick.channel = c;
      tick.time = ofGetElapsedTimeMillis();
      queue.push(tick);

      direction[c] = -1;
    }
    else if (readings[c] < lowerThresholds[c] && direction[c] < 0) {
      direction[c] = 1;
    }
  }
}

