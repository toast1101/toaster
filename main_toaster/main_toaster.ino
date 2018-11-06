//https://www.arduino.cc/reference/en/
int sensorInput = 8;
//指定接腳

int s1 = 25;
int s2 = 50;
int s3 = 75;
int s4 = 100;
//將TCRT感測器讀到的數字，利用四個標準值分成五段(四個功能段+超出感測範圍即非功能區段)

void setup() {
  Serial.begin(9600);
  Serial.print("===========Start!===========");
  pinMode(8,INPUT);
  //pinMode(A0,INPUT);
//將感測接腳模式設為輸入
}
int valueState;       //感測分段模式(狀態1、2、3、4)
int sensorValue;      //接收感測數值
int valueGate = 100;  //最低接收數值，同時也是分段感測程式的啟動條件

void loop() {
  sensorValue = analogRead(A0);   //讀取感測值
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
  //delay(1000);
  //Serial.println("=====wryyyyyyy=====");
  //Serial.println(" valueState: " + valueState);
  Serial.println(valueState);     //打印出分段狀態(1、2、3、4)
  delay(1000);                   //連續感測延遲
}
