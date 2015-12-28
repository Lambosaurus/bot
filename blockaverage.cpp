

#include "blockaverage.h"


BlockAvg::BlockAvg()
{
}

// takes a pointer to the storage array, and the length of the array
// I could use malloc's here, but I make a point of not doing it.
void BlockAvg::Init(float * buffer, unsigned int length)
{
  buffer = buffer;
  buffer_length = length;
  weight = 1.0 / length;

  index = 0;
  refresh_reccommend_ticker.Init(BLOCKAVG_REFRESH_TICKS);

  // ensure the buffer is zeroed, otherwise the sum
  // will get polluted.
  Flood(0.0);
}

void BlockAvg::Flood(float value)
{
  sum = value;

  for (unsigned int i = 0; i < buffer_length; i++)
  {
    buffer[i] = value;
  }
}


// This average will very gradually accrue floating point errors
// So what if I have this schedule its own refreshes?
void BlockAvg::Add(float value)
{
  sum -= buffer[index];

  buffer[index] = value;
  sum += buffer[index];

  // circular buffer
  index += 1;
  if (index >= buffer_length)
  {
    index = 0;
  }

  if (refresh_reccommend_ticker.Tick())
  {
    // we reccommend a refresh, for the user to do when convenient
    refresh_reccommended = true;
  }
}

float BlockAvg::Average(void)
{
  return sum * weight;
}

// Re-averages the buffer in O(n) time.
// This will clear any floating point errors that have accrued into the sum.
// Doing this one in a million loops should be sufficient...
void BlockAvg::ForceRefresh()
{
  // manual summation of the buffer
  sum = 0.0;
  for (unsigned int i = 0; i < buffer_length; i++)
  {
    sum += buffer[i];
  }
}








