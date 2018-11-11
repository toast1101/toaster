//int trigPin = 11;    // Trigger
//int echoPin = 12;    // Echo
//long duration, cm, inches;  //以上為超音波感測器專用範例CODE
int functionSelectPin = 5;
int relayPin = 7;
int TcrtInput_01 = 8;
int TcrtInput_02 = 9;

//mlx
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup()
{
  Serial.begin(9600);
  Serial.print("===========Start!===========");
  pinMode(TcrtInput_01, INPUT);
  pinMode(TcrtInput_02, INPUT);
  pinMode(functionSelectPin,INPUT); 
  pinMode(relayPin, OUTPUT);
  //pinMode(trigPin, OUTPUT);
  //pinMode(echoPin, INPUT);
  //mlx
  mlx.begin();  
}

int valueState;
int sensorValue;
int Tcrt01Value;
int valueGate = 100;
int sensorState;
int functionSelect;
int mlxValue;

void loop()
{
  //digitalWrite(trigPin, LOW);
  //delayMicroseconds(5);
  //digitalWrite(trigPin, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(trigPin, LOW);
  //pinMode(echoPin, INPUT);
  //duration = pulseIn(echoPin, HIGH);
  Tcrt01Value = analogRead(TcrtInput_01);
  mlxValue = mlx.readAmbientTempC();
  functionSelect = digitalRead(functionSelectPin);
  switch (Tcrt01Value)               //========TCRT1=========
  {
    case 0 ... 100:
      valueState = 1;
      break;
    case 101 ... 200:
      valueState = 2;
      break;
    case 201 ... 300:
      valueState = 3;
      break;
    case 301 ... 400:
      valueState = 4;
      break;
    default:
      valueState = 0;
  }
  Serial.println("======(； ･`д･´)=======");
  Serial.print("valueState"); Serial.print(valueState);       //=========偵測狀態========
  Serial.print(", state"); Serial.println(functionSelect);
  Serial.print("mlxValue"); Serial.println(mlxValue);
  if(functionSelect == 1)           //==========模式為1==========
  {
    if (sensorValue != 0)             //==========TCRT1狀態不為0(正確)==========
    {
      digitalWrite(relayPin, HIGH);       //======開啟繼電器=======
      delay(2000);
      switch (valueState)             //==========狀態為1234===========
      {
      case 1:
        int a1;
        for (a1 = 0; a1 < 10; a1++)
        {
          digitalWrite(relayPin, HIGH);
          delay(500);
          digitalWrite(relayPin, LOW);
          delay(500);
        }
        break;
      case 2:
        int a2;
        for (a2 = 0; a2 < 10; a2++)
        {
          digitalWrite(relayPin, HIGH);
          delay(500);
          digitalWrite(relayPin, LOW);
          delay(70);
        }
        break;
      case 3:
        int a3;
        for (a3 = 0; a3 < 10; a3++)
        {
          digitalWrite(relayPin, HIGH);
          delay(500);
          digitalWrite(relayPin, LOW);
          delay(1000);
        }
        break;
      case 4:
        int a4;
        for (a4 = 0; a4 < 10; a4++)
        {
          digitalWrite(relayPin, HIGH);
          delay(50);
          digitalWrite(relayPin, LOW);
          delay(150);
        }
        break;
      default:
        break;
      }
    delay(2000);
    } 
    else                  //==========TCRT1狀態為0(不在偵測範圍內)==========
    {
    delay(250);
    }
  }
  else                          //==========模式為0==========
  {
    if (sensorValue != 0) 
    {
      digitalWrite(relayPin, HIGH);
      delay(2000);
      switch (valueState)
      {
        case 1:
          digitalWrite(relayPin, HIGH);
          delay(5000);
          digitalWrite(relayPin, LOW);
          break;
        case 2:
          digitalWrite(relayPin, HIGH);
          delay(4000);
          digitalWrite(relayPin, LOW);
          break;
        case 3:
          digitalWrite(relayPin, HIGH);
          delay(3000);
          digitalWrite(relayPin, LOW);
          break;
        case 4:
          digitalWrite(relayPin, HIGH);
          delay(2000);
          digitalWrite(relayPin, LOW);
          break;
        default:
          break;
      }
      delay(2000);
    } 
    else          //==========TCRT1狀態為0(不在偵測範圍內)==========
    {
    delay(1000);
    }
  } 
}
