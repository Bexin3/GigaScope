#include "STMSpeeduino.h"

const long ValuesToStore = 3000;  //How many values to store, max 30000, the more the higher accuracy
int16_t CurrentValue = 0;  //tracks current stored value

int ADC1Values[ValuesToStore] = {};

const int ADCChannel = A0; //ADC channel, limited to A0 when gain is on
const int Resolution = 16; //8, 10, 12, 14, 16
const bool Differential = 0; //Sets A10 as positive and A11 as negative, doesnt work when Gain is on
double ClockSpeed = 40; //Clock speed in mhz, stable up to 40mhz, may decrease range further
const int Gain = 2; //1, 2, 4, 8, 16
const int Sampletime = 0;
const int Samplenum = 0;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

if (Gain==1) {
ADC1Begin(ADCChannel, Resolution, Differential, ClockSpeed, Sampletime, Samplenum);
} else {
OPAMPCFG(Gain);
ADC1Begin(A0, Resolution, 0, ClockSpeed, Sampletime, Samplenum);
}

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
  CurrentValue += 1;
}

void printloop() {
  Serial.print("ADC1 Voltage: ");
  Serial.println(ADC1Values[CurrentValue]);
  CurrentValue += 1;
}