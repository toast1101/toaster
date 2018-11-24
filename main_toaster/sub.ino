void getAllSensorValue() {
  tcrt1Value = analogRead(tcrt1InputA0);
  tcrt2Value = digitalRead(tcrt2InputD0);//做開關判斷，所以只讀高低準位
  mlxValue = mlx.readObjectTempC();     //讀取當前吐司溫度
  temperature = mlxValue;
}

void detect_toast() {
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

void debug() {
  Serial.println("======(； ･`д･´)=======");
  Serial.print("tcrtState(厚片為0，薄片為1) = ");
  Serial.println(tcrtState); //=========偵測狀態========
  Serial.print("functionSelect(快速加熱為0，完美加熱為1) = ");
  Serial.println(functionSelect);//快速加熱、完美加熱模式
  Serial.print("temperature(溫度) = "); Serial.print(temperature); Serial.println("*C");
  Serial.print("tcrt1Value = "); Serial.println(tcrt1Value);
  Serial.print("tcrt2Value = "); Serial.println(tcrt2Value);
  Serial.print("heatMode = "); Serial.println(heatMode);
}

void calculateHeatMode() {
  if (temperature <= 5) { //冷凍
    if (tcrtState == 0) { //厚片
      heatMode = 'F';
    }
    else if (tcrtState == 1) { //薄片
      heatMode = 'E';
    }
    else heatMode = 'N';
  }
  else if (temperature <= 20) { //冷藏
    if (tcrtState == 0) { //厚片
      heatMode = 'D';
    }
    else if (tcrtState == 1) { //薄片
      heatMode = 'C';
    }
    else heatMode = 'N';
  }
  else { //temperature > 20 常溫
    if (tcrtState == 0) { //厚片
      heatMode = 'B';
    }
    else if (tcrtState == 1) { //薄片
      heatMode = 'A';
    }
    else heatMode = 'N';
  }
}

void fastHeatMode() {
  if (functionSelect == 0) //==========模式為0(智慧模式--快速)==========
  {
    if (tcrtState != 2)
    {
      digitalWrite(relay2Pin, HIGH);
      delay(120000);//基礎加熱時間
      switch (heatMode) {
        case 'A':
          Serial.print("A");
          digitalWrite(relay2Pin, HIGH);
          delay(10000);
          digitalWrite(relay2Pin, LOW);
          digitalWrite(relay1Pin, LOW); //考完吐司，關閉電磁鐵
          break;
        case 'B':
          Serial.print("B");
          digitalWrite(relay2Pin, HIGH);
          delay(30000);
          digitalWrite(relay2Pin, LOW);
          digitalWrite(relay1Pin, LOW); //考完吐司，關閉電磁鐵
          break;
        case 'C':
          Serial.print("C");
          digitalWrite(relay2Pin, HIGH);
          delay(60000);
          digitalWrite(relay2Pin, LOW);
          digitalWrite(relay1Pin, LOW); //考完吐司，關閉電磁鐵
          break;
        case 'D':
          Serial.print("D");
          digitalWrite(relay2Pin, HIGH);
          delay(90000);
          digitalWrite(relay2Pin, LOW);
          digitalWrite(relay1Pin, LOW); //考完吐司，關閉電磁鐵
          break;
        case 'E':
          Serial.print("E");
          digitalWrite(relay2Pin, HIGH);
          delay(120000);
          digitalWrite(relay2Pin, LOW);
          digitalWrite(relay1Pin, LOW); //考完吐司，關閉電磁鐵
          break;
        case 'F':
          Serial.print("F");
          digitalWrite(relay2Pin, HIGH);
          delay(150000);
          digitalWrite(relay2Pin, LOW);
          digitalWrite(relay1Pin, LOW); //考完吐司，關閉電磁鐵
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

void perfectHeatMode() {
  if (functionSelect == 1)          //==========模式為1(智慧模式--完美)==========
  {
    if (tcrtState != 2)             //==========2個TCRT狀態不為2(正確)==========
    {
      digitalWrite(relay2Pin, HIGH); //======開啟電熱絲繼電器=======
      delay(120000);              //基礎加熱時間
      switch (heatMode)           //==========狀態為ABCD===========
      {
        case 'A':
          Serial.print("caseA");
          digitalWrite(relay2Pin, HIGH);
          delay(8000);
          digitalWrite(relay2Pin, LOW);
          digitalWrite(relay1Pin, LOW); //考完吐司，關閉電磁鐵
          break;
        case 'B':
          Serial.print("caseB");
          for (int i = 0; i < 3; i++)
          {
            digitalWrite(relay2Pin, HIGH);
            delay(5000);
            digitalWrite(relay2Pin, LOW);
            delay(5000);
          }
          digitalWrite(relay1Pin, LOW); //考完吐司，關閉電磁鐵
          break;
        case 'C':
          Serial.print("caseC");
          for (int i = 0; i < 6; i++)
          {
            digitalWrite(relay2Pin, HIGH);
            delay(6000);
            digitalWrite(relay2Pin, LOW);
            delay(4000);
          }
          digitalWrite(relay1Pin, LOW); //考完吐司，關閉電磁鐵
          break;
        case 'D':
          Serial.print("caseD");
          for (int i = 0; i < 9; i++)
          {
            digitalWrite(relay2Pin, HIGH);
            delay(7000);
            digitalWrite(relay2Pin, LOW);
            delay(3000);
          }
          digitalWrite(relay1Pin, LOW); //考完吐司，關閉電磁鐵
          break;
        case 'E':
          Serial.print("caseE");
          for (int i = 0; i < 12; i++)
          {
            digitalWrite(relay2Pin, HIGH);
            delay(8000);
            digitalWrite(relay2Pin, LOW);
            delay(2000);
          }
          digitalWrite(relay1Pin, LOW); //考完吐司，關閉電磁鐵
          break;
        case 'F':
          Serial.print("caseF");
          for (int i = 0; i < 15; i++)
          {
            digitalWrite(relay2Pin, HIGH);
            delay(9000);
            digitalWrite(relay2Pin, LOW);
            delay(1000);
          }
          digitalWrite(relay1Pin, LOW); //考完吐司，關閉電磁鐵
          break;
        default:
          break;
      }
      delay(2000);
      digitalWrite(relay1Pin, LOW); //考完吐司，關閉電磁鐵
    }
    else                  //==========TCRT1狀態為2(不在偵測範圍內)==========
    {
      delay(250);
    }
  }
}
