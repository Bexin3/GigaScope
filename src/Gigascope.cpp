#include "GigaScope.h"

GigascopeValue Freqn(int BottomBoundary, int TopBoundary, int timePassedPC, int Values[]) {
  
 int CurrentValue = 0;
 double Frequency = 0;
 bool StateOn = 0;
 float DutyC = 0;
 int ValuesToStore = 0;

 while ((Values[ValuesToStore]>=0)) {
  ValuesToStore += 1;
};

ValuesToStore -= 32; //Clueless why this works at all



  while (CurrentValue < ValuesToStore) {
    if (StateOn == true && Values[CurrentValue] < BottomBoundary) {
      StateOn = false;
      Frequency += 1;
    } else if (StateOn == false && Values[CurrentValue] > TopBoundary) {
      StateOn = true;
      Frequency += 1;
    };
    if (StateOn) { DutyC += 1; };
    CurrentValue += 1;
  };
  CurrentValue = 0;
  Frequency = Frequency * 1000000 / 2 / timePassedPC;
  DutyC = DutyC / ValuesToStore * 100;
  GigascopeValue result = { Frequency, DutyC };
return(result);
}




Boundaries findMinMax(int Values[]) {
int MinVoltage = Values[0];
int MaxVoltage = Values[0];
int CurrentValue = 0;

int ValuesToStore = 0;
while ((Values[ValuesToStore]>=0)) {
  ValuesToStore += 1;
};
ValuesToStore -= 32; //Clueless why this works at all

  while (CurrentValue < ValuesToStore) {

    if (Values[CurrentValue] < MinVoltage) { MinVoltage = Values[CurrentValue]; }
    else if (Values[CurrentValue] > MaxVoltage) { MaxVoltage = Values[CurrentValue]; };
    CurrentValue += 1;
  };
Boundaries MinMax = {MinVoltage, MaxVoltage};
return(MinMax);
}

Boundaries BoundaryFind(int MinVoltage, int MaxVoltage, float minBound, float maxBound) {
 int BottomBoundary = (MaxVoltage - MinVoltage) * minBound;
 int TopBoundary = (MaxVoltage - MinVoltage) * maxBound;
Boundaries boundaries = {BottomBoundary, TopBoundary};
return(boundaries);
}
