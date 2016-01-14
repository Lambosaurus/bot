#pragma once
class Transorb
{
public:
  Transorb();

  void Init(unsigned int length, bool default_state);

  bool Update(bool state);

  bool high;

private:

  unsigned int max_ticks;
  unsigned int ticks;
};

