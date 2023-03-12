#ifndef Gigascope_h
#define Gigascope_h

#include <Arduino.h>


struct GigascopeValue {
  double Frequency;
  double DutyCycle;
};

struct Boundaries {
  int Min;
  int Max;
  
};


GigascopeValue Freqn(int BottomBoundary, int TopBoundary, int timePassedPC, int Values[]);
Boundaries findMinMax(int Values[]);
Boundaries BoundaryFind(int MinVoltage, int MaxVoltage, float minBound, float maxBound);




//struct GigascopeVal GigascopeValues;

//extern GigascopeVal GigascopeValues;

#endif
