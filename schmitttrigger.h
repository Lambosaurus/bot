#pragma once






class SchmittTrigger
{
public:

  SchmittTrigger();
  void Init(float low, float high);
  bool Update(float value);

private:

  bool high;
  float v_high;
  float v_low;
};

