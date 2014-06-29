#include "TickInterpreter.h"

void TickInterpreter::setup(ITickReader* reader, int nChannels) {
  tickReader = reader;
  numChannels = nChannels;
  ticks = new std::list<Tick>[numChannels];
}

void TickInterpreter::update() {
  tickReader->update();

  while (tickReader->hasNext()) {
    Tick tick = tickReader->next();
    if (tick.channel >= 0 && tick.channel < numChannels) {
      ticks[tick.channel].push_front(tick);
    }
  }

  unsigned long long now = ofGetElapsedTimeMillis();
  for (int c = 0; c < numChannels; ++c) {
    while (ticks[c].size() > 0
        && ticks[c].back().time + TICK_INTERPRETER_DURATION < now) {
      ticks[c].pop_back();
    }
  }
}

float TickInterpreter::getVelocity(int channel) {
  long d;
  if (ticks[channel].size() < 2
      || (d = ticks[channel].front().time - ticks[channel].back().time) <= 0) return 0;
  return (float)ticks[channel].size() / d;
}
