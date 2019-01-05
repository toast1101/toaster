void getAllSensorValue() {
  tcrt1Value = analogRead(tcrt1InputA0);
  tcrt2Value = digitalRead(tcrt2InputD0);//做開關判斷，所以只讀高低準位
  mlxValue = mlx.readObjectTempC();     //讀取當前吐司溫度
  temperature = mlxValue;
  adjustHeatTimeButton1State = digitalRead(adjustHeatTimeButton1);
  adjustHeatTimeButton2State = digitalRead(adjustHeatTimeButton2);
  reheatButtonState = digitalRead(reheatButton);
}

void detect_toast() {
  switch (tcrt1Value)               //========TCRT1=========
  {
    case 0 ... 300:
      toastInputState = 0;//放厚片
      break;
    case 501 ... 700://放薄片
      toastInputState = 1;
      break;
    case 701 ... 1200://沒放東西
      toastInputState = 2;
      break;
    default:
      toastInputState = 2;//沒放東西
  }
}

void debug() {
  Serial.println("======(； ･`д･´)=======");
  Serial.print("toastInputState(厚片為0，薄片為1) = ");
  Serial.println(toastInputState); //=========偵測狀態========
  Serial.print("functionSelect(快速加熱為0，完美加熱為1) = ");
  Serial.println(functionSelect);//快速加熱、完美加熱模式
  Serial.print("temperature(溫度) = "); Serial.print(temperature); Serial.println("*C");
  Serial.print("tcrt1Value = "); Serial.println(tcrt1Value);
  Serial.print("tcrt2Value = "); Serial.println(tcrt2Value);
  Serial.print("heatMode = "); Serial.println(heatMode);
  Serial.print("adjustHeatTimeButton1 and 2= "); Serial.print(adjustHeatTimeButton1State);
  Serial.println(adjustHeatTimeButton2State);
  Serial.print("reheatButton = "); Serial.println(reheatButtonState);
}

void calculateHeatMode() {
  if (temperature <= 5) { //冷凍
    if (toastInputState == 0) { //厚片
      heatMode = 'F';
    }
    else if (toastInputState == 1) { //薄片
      heatMode = 'E';
    }
    else heatMode = 'N';
  }
  else if (temperature <= 20) { //冷藏
    if (toastInputState == 0) { //厚片
      heatMode = 'D';
    }
    else if (toastInputState == 1) { //薄片
      heatMode = 'C';
    }
    else heatMode = 'N';
  }
  else { //temperature > 20 常溫
    if (toastInputState == 0) { //厚片
      heatMode = 'B';
    }
    else if (toastInputState == 1) { //薄片
      heatMode = 'A';
    }
    else heatMode = 'N';
  }
  if (adjustHeatTimeButton1State == 1 && adjustHeatTimeButton2State == 0) {
    adjustHeatTime = -10;
  }
  else if (adjustHeatTimeButton1State == 0 && adjustHeatTimeButton2State == 1) {
    adjustHeatTime = 10;
  }
  else {
    adjustHeatTime = 0;
  }
}

void reheatMode() {
  if (reheatButtonState == 1) { //判斷是否進入再加熱模式
    delay(10);//10ms防雜訊
    if (reheatButtonState == 1) {//再次判斷是否進入再加熱模式
      digitalWrite(relay1Pin, HIGH); //導通電磁鐵
      while (tcrt2Value == 1) { //1為尚未按下，0為已經按下按鈕
        getAllSensorValue();  //讀取各項感測器數值
        if (tcrt2Value == 0) delay(100); //等待使用者按下麵包機按鈕
        if (tcrt2Value == 0) break; //確定按鈕已經按下跳出 等待按鈕按下迴圈
        Serial.println("while");
      }
      ms = prems = millis();
      float reheatTime = 60;//60s
      digitalWrite(relay2Pin,HIGH);
      while (reheatTime != 0) {
        while (ms - prems < 100) { //delay 100ms
          ms = millis();
        }
        reheatTime -= 0.1;
        Serial.print("剩餘再加熱時間:"); Serial.println(reheatTime);
        if (digitalRead(reheatButton) == 0) {
          for (int owo = 0; owo < 10; owo++) {
            delay(5);
            if (digitalRead(reheatButton) == 0); //確定開關被關掉，不重置迴圈
            else break;//跳出迴圈
            if (owo == 9 && digitalRead(reheatButton) == 0)reheatTime = 0;
            //真的確定開關被關掉，直接跳出
          }
        }
      }
      digitalWrite(relay2Pin,LOW);//turn off heater
      digitalWrite(relay1Pin,LOW);//turn off magnet
    }
  }
}

void fastHeatMode() {
  if (functionSelect == 0) //==========模式為0(智慧模式--快速)==========
  {
    if (toastInputState != 2)
    {
      digitalWrite(relay2Pin, HIGH);
      int remainTime = 125;
      remainTime += adjustHeatTime;
      while (remainTime != 0) { //基礎加熱時間125s + adjustHeatTime;
        prems = ms = millis();
        while (ms - prems <= 1000) { //1s
          ms = millis();
        }
        remainTime -= 1;
        Serial.print("基礎加熱剩餘秒數:"); Serial.println(remainTime);
      }
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
      delay(500);
    }
  }
}

void perfectHeatMode() {
  if (functionSelect == 1)          //==========模式為1(智慧模式--完美)==========
  {
    if (toastInputState != 2)             //==========2個TCRT狀態不為2(正確)==========
    {
      digitalWrite(relay2Pin, HIGH); //======開啟電熱絲繼電器=======
      int remainTime = 125;
      remainTime += adjustHeatTime;
      while (remainTime != 0) { //基礎加熱時間125s + adjustHeatTime;
        prems = ms = millis();
        while (ms - prems <= 1000) { //1s
          ms = millis();
        }
        remainTime -= 1;
        Serial.print("基礎加熱剩餘秒數:"); Serial.println(remainTime);
      }
      switch (heatMode)           //==========狀態為ABCD===========
      {
        case 'A':
          Serial.print("caseA");
           for (int i = 0; i < 3; i++)
          {
            digitalWrite(relay2Pin, HIGH);
            delay(4000);
            digitalWrite(relay2Pin, LOW);
            delay(6000);
          }
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
      delay(500);
    }
  }
}
