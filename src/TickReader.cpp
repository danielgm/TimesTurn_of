#include "TickReader.h"

void TickReader::setup() {
  // TODO: Remove hard-coded values.
  numInputs = 2;
  numTicks = new int[numInputs];
}

void TickReader::update() {
  for (int i = 0; i < numInputs; i++) {
    numTicks[i] = ofRandom(0, 8);
  }
}

int TickReader::getNumInputs() {
  return numInputs;
}

int TickReader::getNumTicks(int input) {
  return numTicks[input];
}

