//https://www.arduino.cc/reference/en/
int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
long duration, cm, inches;

int relayPin = 7;

int sensorInput = 8;
void setup()
{
  Serial.begin(9600);
  Serial.print("===========Start!===========");
  pinMode(8, INPUT);

  pinMode(relayPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //pinMode(A0,INPUT);
}
int valueState;
int sensorValue;
//int V;
int valueGate = 100;
int sensorState;
void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  sensorValue = duration;
  //V = sensorValue/100;
  switch (sensorValue)
  {
    case 0 ... 100:
      valueState = 1;
      break;
    case 101 ... 20000:
      valueState = 2;
      break;
    case 20001 ... 300000:
      valueState = 3;
      break;
    case 300001 ... 310001:
      valueState = 4;
      break;
    default:
      valueState = 0;
  }
  /*
    if(sensorValue<s1){
     valueState = 1;
    }
    else if(sensorValue>=s1 && sensorValue<s2){
     valueState = 2;
    }
    else if(sensorValue>=s2 && sensorValue<s3){
     valueState = 3;
    }
    else if(sensorValue>=s3 && sensorValue<s4){
     valueState = 4;
    }
  */
  //delay(1000);
  //Serial.println("=====wryyyyyyy=====");
  //Serial.println(" valueState: " + valueState);
  Serial.println(valueState);
  if (sensorValue != 0) {
    switch (valueState)
    {
      case 1:
        int a1;
        for (a1 = 0; a1 < 10; a1++) {
          digitalWrite(relayPin, HIGH);
          delay(500);
          digitalWrite(relayPin, LOW);
          delay(500);
        }
        break;
      case 2:
        int a2;
        for (a2 = 0; a2 < 10; a2++) {
          digitalWrite(relayPin, HIGH);
          delay(500);
          digitalWrite(relayPin, LOW);
          delay(700);
        }
        break;
      case 3:
        int a3;
        for (a3 = 0; a3 < 10; a3++) {
          digitalWrite(relayPin, HIGH);
          delay(500);
          digitalWrite(relayPin, LOW);
          delay(1000);
        }
        digitalWrite(relayPin, HIGH);
        delay(500);
        digitalWrite(relayPin, LOW);
        delay(1000);
        break;
      case 4:
        int a4;
        for (a4 = 0; a4 < 10; a4++) {
          digitalWrite(relayPin, HIGH);
          delay(500);
          digitalWrite(relayPin, LOW);
          delay(1500);
        }
        break;
      default:
        break;
    }
    delay(2000);
  } else {
    delay(1000);
  }

}
