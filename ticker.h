#pragma once

class Ticker
{
public:

  Ticker();

  void Init(unsigned int arg_max_ticks);

  // ticks max_tick times, before returning true
  bool Tick();
  bool Tick(unsigned int elapsed);
  void Clear();

private:
  unsigned int ticks;
  unsigned int tick_max;
};

