
#ifndef Gigascope_h
#define Gigascope_h

#include <Arduino.h>


struct GigaScope {     //Struct with results
  double Frequency;
  float DutyCycle;
  long Min;
  long Max;
};



GigaScope Calculate(int Values[], long timePassedPC, int ValuesToStore, float minBound = 0.3, float maxBound = 0.7);


GigaScope Freqn(int BottomBoundary, int TopBoundary, long timePassedPC, int Values[], int ValuesToStore);
GigaScope findMinMax(int Values[], int ValuesToStore);
GigaScope BoundaryFind(int MinVoltage, int MaxVoltage, float minBound, float maxBound);




#endif
