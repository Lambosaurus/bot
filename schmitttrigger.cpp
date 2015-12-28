#include "schmitttrigger.h"



SchmittTrigger::SchmittTrigger()
{
}

void SchmittTrigger::Init(float low, float high)
{
  v_high = high;
  v_low = low;
}

void SchmittTrigger::Update(float value)
{
  high = value > (high ? v_low : v_high);
}