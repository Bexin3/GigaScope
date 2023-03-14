#include "Gigascope.h"

const int ValuesToStore = 4000;   //How many values to store, more values - more accuracy
const int delayms = 0;            //Delay between each read sequence
const int AdcChannel = A0;        //Channel to read from
const float voltage = 3.3f;       //Your board voltage
const int delaybetweenreads = 0;

const int Resolution = 16;      //8,10,12,14,16 on giga r1 wifi, depends on your board

const float minBound = 0.3f;  //Boundary fraction value has to go below to register as 0
const float maxBound = 0.7f;  //Boundary fraction value has to go below to register as 1
bool Diffmode = 0;      //Limits channel selection to A1 positive, A0 negative

unsigned long timeBegin;
unsigned long timeEnd;

GigaScope Results;

int Values[ValuesToStore] = {};
int16_t CurrentValue;


void setup() {
  analogWrite(7, 127);
  analogReadResolution(Resolution);
  Serial.begin(2000000);
}


void loop() {

CurrentValue = 0; //Reset value currently being processed

  timeBegin = micros(); //Find out when did reads began

  while (CurrentValue < ValuesToStore) {
    collectloop();      //Collect values
  };

  timeEnd = micros(); //Find out when did reads finish


  Results = Calculate(Values, timeEnd-timeBegin, ValuesToStore);
  /*
  Calculate min, max, frequency and duty cycle, 
  minBound and maxBound are fully optional, defines when signal is considered as high
  */

  print(); //Print all relevant values
  delay(delayms); //Wait between next loop
}


void collectloop() {
  Values[CurrentValue] = analogRead(AdcChannel); //Collect value
  CurrentValue += 1; //Add value
  delayMicroseconds(delaybetweenreads); //Delay before next collection
}

void print() {
  Serial.print("Frequency: ");
  Serial.print(Results.Frequency);
  Serial.println(" hz");
  Serial.print("Duty Cycle: ");
  Serial.print(Results.DutyCycle);
  Serial.println(" %");
  Serial.print("Min Voltage: ");
  Serial.print(Results.Min*voltage/pow(2, Resolution),4); //Calculate actual voltage and print
  Serial.println(" v");
  Serial.print("Max Voltage: ");
  Serial.print(Results.Max*voltage/pow(2, Resolution),4); //Calculate actual voltage and print
  Serial.println(" v");
}

