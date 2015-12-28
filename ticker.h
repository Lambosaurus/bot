#pragma once

class Ticker
{
public:

  Ticker();

  void Init(unsigned int arg_max_ticks);

  // ticks max_tick times, before returning true
  inline bool Tick();
  bool Tick(unsigned int elapsed);
  void Clear();

  unsigned int ticks;

private:
  unsigned int tick_max;
};

