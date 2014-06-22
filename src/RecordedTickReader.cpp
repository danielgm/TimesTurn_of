#include "RecordedTickReader.h"

void RecordedTickReader::setup(string filepath, int nInputs) {
  ofFile file;
  file.open(filepath);
  fileBuffer = file.readToBuffer();
  savedLine = "";

  numInputs = nInputs;
  numTicks = new int[numInputs];

  startTime = ofGetSystemTime();
}

void RecordedTickReader::update() {
  for (int i = 0; i < numInputs; i++) {
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

int RecordedTickReader::getNumInputs() {
  return numInputs;
}

int RecordedTickReader::getNumTicks(int input) {
  return numTicks[input];
}

bool RecordedTickReader::processLine(string line) {
  long now = ofGetSystemTime() - startTime;

  vector<string> tokens = ofSplitString(line, "\t");

  long time = ofToInt(tokens[1]);
  if (time < now) {
    int input = ofToInt(tokens[0]);
    numTicks[input]++;
    return true;
  }
  else {
    return false;
  }
}
