int functionSelectPin = 5;  //快速、完美加熱模式的選擇按鈕
int relay1Pin = 8;          //電磁鐵控制繼電器
int relay2Pin = 9;          //電熱絲控制繼電器
int tcrt1InputA0 = A1;  //tcrt1的類比讀值輸入接腳
int tcrt2InputA0 = A2;  //tcrt1的類比讀值輸入接腳
//-----以下為mlx溫度感測器的引入函式、物件宣告-----
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
//-----以上為mlx溫度感測器的引入函式、物件宣告-----
void setup(){
  Serial.begin(9600);
  Serial.print("===========Start!===========");
  pinMode(tcrt1InputA0, INPUT);
  pinMode(tcrt2InputA0, INPUT);
  pinMode(functionSelectPin, INPUT);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  mlx.begin();
  digitalWrite(relay1Pin,HIGH);//上電開啟電磁鐵
}

int tcrt1Value; //tcrt1感測數值
int tcrt2Value; //tcrt2感測數值
int mlxValue;   //紅外線溫度感測數值
int temperature;//紅外線溫度感測數值(把他取成比較好判別的名稱)
int tcrtState;  //判斷有沒有放吐司
int functionSelect; //一般模式、智慧模式切換開關
char heatMode = 'N';//加熱模式

void loop(){
  getAllSensorValue();  //讀取各項感測器數值
  functionSelect = digitalRead(functionSelectPin);//讀取開關選擇的模式(一般模式、智慧模式切換開關)
  detect_toast();   //利用2個TCRT判斷吐司是否放入
  calculateHeatMode();
  debug();          //在監控視窗上輸出各項數值
  fastHeatMode();   //依據functionSelect判斷是否進入快速加熱模式
  //===============================================================
  perfectHeatMode();//依據functionSelect判斷是否進入完美加熱模式
  
}
