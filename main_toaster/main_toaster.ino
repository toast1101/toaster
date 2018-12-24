int functionSelectPin = 5;  //快速、完美加熱模式的選擇按鈕
int relay1Pin = 8;          //電磁鐵控制繼電器
int relay2Pin = 9;          //電熱絲控制繼電器
int tcrt1InputA0 = A1;  //tcrt1(吐司厚度)的類比讀值輸入接腳
int tcrt2InputA0 = A2;  //tcrt2(下壓開關)的類比讀值輸入接腳
int tcrt2InputD0 = 7;   //tcrt2(下壓開關)的數位讀值輸入接腳
unsigned long ms;   //當前時間
unsigned long prems;//前一次紀錄的時間

//在Arduino Nano Board 的 A5為SCL
//                        A4為SDA
//-----以下為mlx溫度感測器的引入函式、物件宣告-----
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
//-----以上為mlx溫度感測器的引入函式、物件宣告-----
void setup() {
  Serial.begin(9600);
  Serial.print("===========Start!===========");
  pinMode(tcrt1InputA0, INPUT);
  pinMode(tcrt2InputA0, INPUT);
  pinMode(tcrt2InputD0, INPUT);
  pinMode(functionSelectPin, INPUT);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  mlx.begin();
  ms = millis();
  prems = ms;
}

int tcrt1Value; //tcrt1感測數值
int tcrt2Value; //tcrt2感測數值(0與1)
int mlxValue;   //紅外線溫度感測數值
int temperature;//紅外線溫度感測數值(把他取成比較好判別的名稱)
int toastInputState = 2;  //判斷有沒有放吐司
int functionSelect; //快速加熱、完美加熱模式
char heatMode = 'N';//加熱模式

void loop() {
  ms = millis();
  getAllSensorValue();  //讀取各項感測器數值
  detect_toast();//判斷吐司厚度
  functionSelect = digitalRead(functionSelectPin);//讀取開關選擇的模式(快速加熱、完美加熱模式)
  if (toastInputState != 2) { //利用1個TCRT判斷吐司是否放入
    for (int i = 0; i < 5; i++) {//共計判斷5次(約花費1秒)會較準確
      prems = ms = millis();
      while(ms - prems <= 200){//delay200ms
         ms = millis();
      }
      getAllSensorValue();  //再次讀取各項感測器數值
      detect_toast();//再次判斷吐司厚度
      if (toastInputState != 2) continue;//確定連續5次偵測到有東西放入
      else break;
    }
  }
  if (toastInputState != 2) calculateHeatMode();

  if (toastInputState != 2 && heatMode != 'N') {
    digitalWrite(relay1Pin, HIGH); //吐司的各項數值正確，開啟電磁鐵準備加熱
    while (tcrt2Value == 1) { //1為尚未按下，0為已經按下按鈕
      getAllSensorValue();  //讀取各項感測器數值
      if (tcrt2Value == 0) delay(100); //等待使用者按下麵包機按鈕
      if (tcrt2Value == 0) break; //確定按鈕已經按下跳出 等待按鈕按下迴圈
      Serial.println("while");
    }
  }
  debug();          //在監控視窗上輸出各項數值
  fastHeatMode();   //依據functionSelect判斷是否進入快速加熱模式
  //===============================================================
  perfectHeatMode();//依據functionSelect判斷是否進入完美加熱模式

}
