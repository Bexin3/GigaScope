#include "STMSpeeduino.h"

const long ValuesToStore = 300;  //How many values to store, max 30000, the more the higher accuracy
int16_t CurrentValue = 0;  //tracks current stored value

int ADC1Values[ValuesToStore] = {};
int ADC2Values[ValuesToStore] = {};

const int ADC1Channel = A0; //ADC 1 channel
const int ADC2Channel = A1; //ADC 2 channel
const int Resolution = 16; //8, 10, 12, 14, 16
double ClockSpeed = 40; //Clock speed in mhz, stable up to 40mhz, may decrease range further
int SampleTime = 0; //0 to 7
int Samplenum = 0; //Number of samples, is 1 more, 0 to 1023

long Val1;
long Val2;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
ADCSimultaneous(ADC1Channel, ADC2Channel, Resolution, ClockSpeed, SampleTime, Samplenum);

}

void loop() {

while (CurrentValue < ValuesToStore) {
    collectloop();
};
CurrentValue = 0;
while (CurrentValue < ValuesToStore) {
    printloop();
};
CurrentValue = 0;

}

void collectloop() {
  ADC1Values[CurrentValue] = CatchADC1Value();
  ADC2Values[CurrentValue] = CatchADC2Value();
  CurrentValue += 1;
}

void printloop() {
  Serial.print("ADC1 Voltage: ");
  Serial.println(ADC1Values[CurrentValue]*3.3f/pow(2, Resolution),4);
  Serial.print("ADC2 Voltage: ");
  Serial.println(ADC2Values[CurrentValue]*3.3f/pow(2, Resolution),4);
  CurrentValue += 1;
}