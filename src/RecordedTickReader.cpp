#include "RecordedTickReader.h"

void RecordedTickReader::setup(string filepath, int nChannels) {
  ofFile file;
  file.open(filepath);
  fileBuffer = file.readToBuffer();

  nextTick.channel = -1;

  numChannels = nChannels;
}

void RecordedTickReader::update() {}

bool RecordedTickReader::hasNext() {
  if (nextTick.channel < 0) {
    if (fileBuffer.isLastLine()) {
      return false;
    }

    nextTick = processLine(fileBuffer.getNextLine());
  }

  return nextTick.channel >= 0 && nextTick.time < ofGetElapsedTimeMillis();
}

Tick RecordedTickReader::next() {
  Tick result = nextTick;
  nextTick.channel = -1;
  return result;
}

Tick RecordedTickReader::processLine(string line) {
  vector<string> tokens = ofSplitString(line, "\t");

  Tick tick;
  tick.channel = ofToInt(tokens[0]);
  tick.time = ofToInt(tokens[1]);
  return tick;
}
