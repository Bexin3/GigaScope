
const long ValuesToStore = 300;  //How many values to store, max 30000, the more the higher accuracy
int16_t CurrentValue = 0;  //tracks current stored value

int ADC1Values[ValuesToStore] = {};
int ADC2Values[ValuesToStore] = {};

const int ADC1Channel = A0; //ADC 1 channel
const int ADC2Channel = A1; //ADC 2 channel
const int Resolution = 10;


long Val1;
long Val2;


void setup() {

Serial.begin(9600);

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
  ADC1Values[CurrentValue] = analogRead(ADC1Channel);
  ADC2Values[CurrentValue] = analogRead(ADC2Channel);
  CurrentValue += 1;
}

void printloop() {
  Serial.print("ADC1 Voltage: ");
  Serial.println(ADC1Values[CurrentValue]*3.3f/pow(2, Resolution),4);
  Serial.print("ADC2 Voltage: ");
  Serial.println(ADC2Values[CurrentValue]*3.3f/pow(2, Resolution),4);
  CurrentValue += 1;
}
