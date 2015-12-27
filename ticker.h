#pragma once

class Ticker
{
public:

  Ticker();

  void init(unsigned int arg_max_ticks);

  bool tick();
  bool tick(unsigned int elapsed);
  void clear();

private:
  unsigned int ticks;
  unsigned int tick_max;
};

