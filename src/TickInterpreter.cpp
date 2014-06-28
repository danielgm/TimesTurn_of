#include "TickInterpreter.h"

void TickInterpreter::setup(ITickReader* reader, int nChannels) {
  tickReader = reader;
  numChannels = nChannels;

  unsigned long long now = ofGetElapsedTimeMillis();

  times = new std::list<long>[numChannels];
  deltas = new std::list<long>[numChannels];
  prevTimes = new unsigned long long[numChannels];
  for (int i = 0; i < numChannels; ++i) {
    prevTimes[i] = now;
  }
}

void TickInterpreter::update() {
  while (tickReader->hasNext()) {
    Tick tick = tickReader->next();
    if (tick.channel >= 0 && tick.channel < numChannels) {
      times[tick.channel].push_front(tick.time);
      if (times[tick.channel].size() > TICK_INTERPRETER_DELTAS_SIZE) {
        times[tick.channel].pop_back();
      }

      long delta = tick.time - prevTimes[tick.channel];
      deltas[tick.channel].push_front(delta);
      if (deltas[tick.channel].size() > TICK_INTERPRETER_DELTAS_SIZE) {
        deltas[tick.channel].pop_back();
      }

      prevTimes[tick.channel] = tick.time;
    }
  }
}

long TickInterpreter::getRaw(int channel) {
  return (deltas[channel].size() <= 0) ? 0 : deltas[channel].front();
}

long TickInterpreter::getAverage(int channel) {
  if (deltas[channel].size() <= 0) return 0;

  long sum = 0;
  for (std::list<long>::iterator i = deltas[channel].begin(); i != deltas[channel].end(); ++i) {
    sum += *i;
  }
  return sum / deltas[channel].size();
}

long TickInterpreter::getRawVelocity(int channel) {
  if (deltas[channel].size() <= 1) return 0;
  return deltas[channel].front() - *++deltas[channel].begin();
}

long TickInterpreter::getAverageVelocity(int channel) {
  if (deltas[channel].size() <= 1) return 0;
  return (times[channel].front() - times[channel].back()) / times[channel].size();
}
