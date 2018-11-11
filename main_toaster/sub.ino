void getAllSensorValue(){
  tcrt1Value = analogRead(tcrt1InputA0);
  tcrt2Value = analogRead(tcrt2InputA0);
  mlxValue = mlx.readObjectTempC();     //讀取當前吐司溫度
}

void detect_toast(){
  switch (tcrt1Value)               //========TCRT1=========
  {
    case 0 ... 100:
      tcrtState = 0;//放厚片
      break;
    case 101 ... 150://放薄片
      tcrtState = 1;
      break;
    case 151 ... 200://沒放東西
      tcrtState = 2;
      break;
    default:
      tcrtState = 2;//沒放東西
  }
}

void debug(){
  Serial.println("======(； ･`д･´)=======");
  Serial.print("tcrtState = ");
  Serial.print(tcrtState); //=========偵測狀態========
  Serial.print(", state = ");
  Serial.println(functionSelect);//一般模式、智慧模式切換開關
  Serial.print("mlxValue = "); Serial.print(mlxValue);Serial.println("*C");
  Serial.print("tcrt1Value = "); Serial.println(tcrt1Value);
}

void fastHeatMode(){
  if (functionSelect == 0) //==========模式為0(智慧模式--快速)==========
  {
    if (tcrtState != 0)
    {
      digitalWrite(relay2Pin, HIGH);
      delay(2000);
      switch (tcrtState){
        case 1:
          Serial.print("s1");
          digitalWrite(relay2Pin, HIGH);
          delay(5000);
          digitalWrite(relay2Pin, LOW);
          break;
        case 2:
          Serial.print("s2");
          digitalWrite(relay2Pin, HIGH);
          delay(4000);
          digitalWrite(relay2Pin, LOW);
          break;
        case 3:
          Serial.print("s3");
          digitalWrite(relay2Pin, HIGH);
          delay(3000);
          digitalWrite(relay2Pin, LOW);
          break;
        case 4:
          Serial.print("s4");
          digitalWrite(relay2Pin, HIGH);
          delay(2000);
          digitalWrite(relay2Pin, LOW);
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

void perfectHeatMode(){
  if (functionSelect == 1)          //==========模式為1(智慧模式--完美)==========
  {
    if (tcrtState != 2)             //==========2個TCRT狀態不為2(正確)==========
    {
      digitalWrite(relay2Pin, HIGH); //======開啟電熱絲繼電器=======
      delay(2000);//基礎加熱時間
      switch (heatMode)           //==========狀態為ABCD===========
      {
        case 'A':
          Serial.print("caseA");
          int a1;
          for (a1 = 0; a1 < 10; a1++)
          {
            digitalWrite(relay2Pin, HIGH);
            delay(500);
            digitalWrite(relay2Pin, LOW);
            delay(500);
          }
          break;
        case 'B':
          Serial.print("caseB");
          int a2;
          for (a2 = 0; a2 < 10; a2++)
          {
            digitalWrite(relay2Pin, HIGH);
            delay(500);
            digitalWrite(relay2Pin, LOW);
            delay(70);
          }
          break;
        case 'C':
          Serial.print("caseC");
          int a3;
          for (a3 = 0; a3 < 10; a3++)
          {
            digitalWrite(relay2Pin, HIGH);
            delay(500);
            digitalWrite(relay2Pin, LOW);
            delay(1000);
          }
          break;
        case 'D':
          Serial.print("caseD");
          int a4;
          for (a4 = 0; a4 < 10; a4++)
          {
            digitalWrite(relay2Pin, HIGH);
            delay(50);
            digitalWrite(relay2Pin, LOW);
            delay(150);
          }
          break;
        default:
          break;
      }
      delay(2000);
    }
    else                  //==========TCRT1狀態為2(不在偵測範圍內)==========
    {
      delay(250);
    }
  }
}
