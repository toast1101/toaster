void setup() {
  Serial.begin(9600);
  Serial.print("===========Start!===========");
  

}
int valueState;
int sensorValue;
int valueGate = 100;
int sensorState;
void loop() {
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
