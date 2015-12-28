#pragma once

#include "Energia.h"
#include "ticker.h"


// At 200 t/s, this means we refresh every 15 minutes
const unsigned int BLOCKAVG_REFRESH_TICKS = 180000;


class BlockAvg
{
 public:

 
   BlockAvg();

   // takes a pointer to the storage array, and the length of the array
   // I could use malloc's here, but I make a point of not doing it.
   void Init(float * buffer, unsigned int length);
   
   // fills the buffer with the given value
   void Flood(float value);

   // Passes the next value into the average
   // after many add calls, ForceRefresh may be called
   void Add(float value);

   // Calculates the average
   // This is done in O(1) time.
   float Average();

   // done in O(n) time
   void ForceRefresh();

   bool refresh_reccommended;

private:
   float * buffer; // pointer to the buffer
   unsigned int buffer_length; // length of the buffer

   Ticker refresh_reccommend_ticker;

   float weight; // 1.0/len. This value is precalculated, because division is oft 20x slower than multiplication.
   float sum;     // running sum of the buffer
   unsigned int index; // current write index of the buffer
};

