//https://www.arduino.cc/reference/en/
int sensorInput = 8;

void setup() {
  Serial.begin(9600);
  Serial.print("===========Start!===========");
  pinMode(8,INPUT);

}
int valueState;
int sensorValue;
int valueGate = 100;
int sensorState;
void loop() {
  sensorValue = digitalRead(sensorInput);
  if(sensorValue<100){
    valueState = 1;
  }
  else if(sensorValue<200){
    valueState = 2;
  }
  else if(sensorValue<300){
    valueState = 3;
  }
  else if(sensorValue<400){
    valueState = 4;
  }
  delay(1000);
  Serial.println("=====wryyyyyyy=====");
  Serial.println("valueState: " + valueState);
  

}
