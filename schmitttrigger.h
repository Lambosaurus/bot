#pragma once






class SchmittTrigger
{
public:

  SchmittTrigger();
  void Init(float low, float high);
  void Update(float value);

  bool high;

private:

  float v_high;
  float v_low;
};

