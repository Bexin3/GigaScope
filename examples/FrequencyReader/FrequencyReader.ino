#include "Gigascope.h"

const int ValuesToStore = 127;   //How many values to store, more values - more accuracy
const int delayms = 0;            //Delay between each read sequence
const int AdcChannel = A0;        //Channel to read from
const float voltage = 3.3f;       //Your board voltage
const int delaybetweenreads = 0;

const int Resolution = 8;      //Only change on boards that support it, and allow it in void setup first.

unsigned long timeBegin;
unsigned long timeEnd;

GigaScope Results;

int Values[ValuesToStore] = {};
int16_t CurrentValue;


void setup() {
  //analogReadResolution(Resolution); //Only allow for supported boards
  Serial.begin(115200);
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
  Serial.print(Results.Min*voltage/(pow(2, Resolution)-1),4); //Calculate actual voltage and print
  Serial.println(" v");
  Serial.print("Max Voltage: ");
  Serial.print(Results.Max*voltage/(pow(2, Resolution)-1),4); //Calculate actual voltage and print
  Serial.println(" v");
}

