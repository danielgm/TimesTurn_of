#include "RecordedTickReader.h"

void RecordedTickReader::setup(string filepath, int nChannels) {
  ofFile file;
  file.open(filepath);
  fileBuffer = file.readToBuffer();
  savedLine = "";

  numChannels = nChannels;
  numTicks = new int[numChannels];

  startTime = ofGetSystemTime();
}

void RecordedTickReader::update() {
  for (int i = 0; i < numChannels; i++) {
    numTicks[i] = 0;
  }

  if (savedLine != "") {
    if (processLine(savedLine)) {
      savedLine = "";
    }
  }

  if (savedLine == "") {
    while (!fileBuffer.isLastLine()) {
      string line = fileBuffer.getNextLine();
      if (!processLine(line)) {
        savedLine = line;
        break;
      }
    }
  }
}

int RecordedTickReader::getNumChannels() {
  return numChannels;
}

int RecordedTickReader::getNumTicks(int channel) {
  return numTicks[channel];
}

bool RecordedTickReader::processLine(string line) {
  long now = ofGetSystemTime() - startTime;

  vector<string> tokens = ofSplitString(line, "\t");

  long time = ofToInt(tokens[1]);
  if (time < now) {
    int channel = ofToInt(tokens[0]);
    numTicks[channel]++;
    return true;
  }
  else {
    return false;
  }
}
