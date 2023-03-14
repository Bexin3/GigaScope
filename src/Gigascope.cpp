#include "Gigascope.h"


GigaScope Freqn(int BottomBoundary, int TopBoundary, long timePassedPC, int Values[], int ValuesToStore) {
  
GigaScope Results;

 int CurrentValue = 0;
 double Frequency = 0;
 bool StateOn = 0;
 float DutyC = 0;


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
  Results.DutyCycle = DutyC;
  Results.Frequency = Frequency;
return(Results);
}

//Try long time


GigaScope findMinMax(int Values[], int ValuesToStore) {

GigaScope Results;

int MinVoltage = Values[0];
int MaxVoltage = Values[0];
int CurrentValue = 0;


  while (CurrentValue < ValuesToStore) {

    if (Values[CurrentValue] < MinVoltage) { MinVoltage = Values[CurrentValue]; }
    else if (Values[CurrentValue] > MaxVoltage) { MaxVoltage = Values[CurrentValue]; };
    CurrentValue += 1;
  };
Results.Max = MaxVoltage;
Results.Min = MinVoltage;
return(Results);
}

GigaScope BoundaryFind(int MinVoltage, int MaxVoltage, float minBound, float maxBound) {

 GigaScope Boundaries;

 Boundaries.Min = (MaxVoltage - MinVoltage) * minBound;
 Boundaries.Max = (MaxVoltage - MinVoltage) * maxBound;
return(Boundaries);
}

GigaScope Calculate(int Values[], long timePassedPC, int ValuesToStore, float minBound, float maxBound) {

GigaScope Results = findMinMax(Values, ValuesToStore);
GigaScope Boundaries = BoundaryFind(Results.Min, Results.Max, minBound, maxBound);
Results = Freqn(Boundaries.Min, Boundaries.Max, timePassedPC, Values, ValuesToStore);
return(Results);

}
