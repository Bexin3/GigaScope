#include "Gigascope.h"

const long ValuesToStore = 1270;  //How many values to store, max 32000, less if your arduino doesnt have enough storage
const int delayms = 0;            //Delay between each read sequence
const int AdcChannel = A0;        //Channel to read from
const float voltage = 3.3f;       //Your board voltage

const int Resolution = 12;      //8,10,12,14,16 on giga r1 wifi, depends on your board

const float minBound = 0.3f;  //Boundary fraction value has to go below to register as 0
const float maxBound = 0.7f;  //Boundary fraction value has to go below to register as 1

int BottomBoundary;
int TopBoundary;

unsigned long timeBegin;
unsigned long timeEnd;

double Frequency;
float DutyCycle;

int Values[ValuesToStore] = {};
int16_t CurrentValue;  //tracks current stored value

float MinVoltage;
float MaxVoltage;

void setup() {
analogReadResolution(Resolution); //Only enable on supported boards
  Serial.begin(115200);
}


void loop() {

  CurrentValue = 0; //Reset value currently being processed

  timeBegin = micros();

  while (CurrentValue < ValuesToStore) {
    collectloop();
  };

  timeEnd = micros();

  CurrentValue = 0;

  GigaScope Results = findMinMax(Values, ValuesToStore);
  MinVoltage = Results.Min;
  MaxVoltage = Results.Max;

  GigaScope boundaries = BoundaryFind(MinVoltage, MaxVoltage, minBound, maxBound);
  BottomBoundary = boundaries.Min;
  TopBoundary = boundaries.Max;

  Results = Freqn(BottomBoundary, TopBoundary, timeEnd-timeBegin, Values, ValuesToStore);
  Frequency = Results.Frequency;
  DutyCycle = Results.DutyCycle;


  print();
  delay(delayms);
}


void collectloop() {
  Values[CurrentValue] = analogRead(AdcChannel);
  CurrentValue += 1;
}



void print() {
  Serial.print("Frequency: ");
  Serial.print(Frequency);
  Serial.println(" hz");
  Serial.print("Duty Cycle: ");
  Serial.print(DutyCycle);
  Serial.println(" %");
  Serial.print("Min Voltage: ");
  Serial.print(MinVoltage*voltage/(pow(2, Resolution)-1),4);
  Serial.println(" v");
  Serial.print("Max Voltage: ");
  Serial.print(MaxVoltage*voltage/(pow(2, Resolution)-1),4);
  Serial.println(" v");
}


