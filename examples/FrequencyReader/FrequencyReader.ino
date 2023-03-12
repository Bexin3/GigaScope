#include "STMSpeeduino.h"
#include "Gigascope.h"

const long ValuesToStore = 30000;  //How many values to store, max 30000, the more the higher accuracy
const int delayms = 0;            //Delay between each read sequence
const int AdcChannel = A0;        //Channel to read from
const double ClockSpeed = 40;      //clock speed in mhz

int Resolution = 16;      //8,10,12,14,16
int SampleTime = 0;       //Time for taking a sample, 0-7
const int Samplenum = 0;  //0-1023, is 1 more than specified, oversampling will increase the value, right shifting fixes that

float minBound = 0.3f;  //Boundary fraction value has to go below to register as 0
float maxBound = 0.7f;  //Boundary fraction value has to go below to register as 1
bool Diffmode = 0;      //Limits channel selection to A1 positive, A0 negative

int Gain = 1;  //Setting to more than 1 will limit positive channel to 4, which means that A0 is where amplified signal is, and A2 is source for it. Settings - 1, 2, 4, 8, 15, not supported on Portenta or in diffmode.
int BottomBoundary;
int TopBoundary;

unsigned long timeBegin;
unsigned long timeEnd;

double Frequency;
float DutyCycle;

int Values[ValuesToStore] = {};
int16_t CurrentValue = 0;  //tracks current stored value

float MinVoltage;
float MaxVoltage;

void setup() {


  analogWrite(5, 127);

  if (Gain == 1) {
    ADC1Begin(AdcChannel, Resolution, Diffmode, ClockSpeed);
  } else {
    OPAMPCFG(Gain);
    ADC1Begin(A0, Resolution, 0, SampleTime);
    //ADCInterleaved(4, Resolution, Diffmode);
  }

  Serial.begin(2000000);
}


void loop() {

  timeBegin = micros();

  while (CurrentValue < ValuesToStore) {
    collectloop();
  };

  timeEnd = micros();

  CurrentValue = 0;

  Boundaries MinMax = findMinMax(Values);
  MinVoltage = MinMax.Min;
  MaxVoltage = MinMax.Max;

  Boundaries boundaries = BoundaryFind(MinVoltage, MaxVoltage, minBound, maxBound);
  BottomBoundary = boundaries.Min;
  TopBoundary = boundaries.Max;

  GigascopeValue Results = Freqn(BottomBoundary, TopBoundary, timeEnd-timeBegin, Values);
  Frequency = Results.Frequency;
  DutyCycle = Results.DutyCycle;

  print();
  delay(delayms);
}


void collectloop() {
  Values[CurrentValue] = CatchADC1Value();
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
  Serial.print(MinVoltage*3.3f/Gain/pow(2, Resolution),4);
  Serial.println(" v");
  Serial.print("Max Voltage: ");
  Serial.print(MaxVoltage*3.3f/Gain/pow(2, Resolution),4);
  Serial.println(" v");
}


