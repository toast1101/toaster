int load = 12;
int button = 7;
int buttonPower = 5;
int roastMode = 0;
bool btnReleased = true;
void setup() {
  pinMode(load,OUTPUT);
  pinMode(buttonPower,OUTPUT);
  digitalWrite(buttonPower,HIGH);
  pinMode(button,INPUT);
  Serial.begin(9600);
  Serial.println("===========Start!===========");
}
int btnStatus = 1;
void loop() {
  btnStatusDetectAndModeSwitch();
  switch(roastMode){
    case 1:
      digitalWrite(load,HIGH);
      delay(100);
      btnStatusDetectAndModeSwitch();
      digitalWrite(load,LOW);
      delay(100);
      btnStatusDetectAndModeSwitch();
      break;
    case 2:
      for(int i = 0;i<50;i++){
        digitalWrite(load,HIGH);
        delay(10);
        btnStatusDetectAndModeSwitch();
      }
      for(int i=0;i<50;i++){
        digitalWrite(load,LOW);
        delay(10);
        btnStatusDetectAndModeSwitch();
      }
      break;
    case 3:
      digitalWrite(load,LOW);
      btnStatusDetectAndModeSwitch();
      break;
    case 4:
      for(int i=0;i<3;i++){
        digitalWrite(load,HIGH);
        delay(100);
        btnStatusDetectAndModeSwitch();
        digitalWrite(load,LOW);
        delay(100);
        btnStatusDetectAndModeSwitch();
      }
      for(int owo = 0;owo < 40;owo++){
        digitalWrite(load,LOW);
        delay(10);
        btnStatusDetectAndModeSwitch();
      }
      break;
    default: //turn off toaster
      //do nothing;
      break;
  }
}
void btnStatusDetectAndModeSwitch(){
  btnStatus =  digitalRead(button);
  if(btnStatus == 1){
    delay(5);
    if(btnStatus == 1 && btnReleased == true){
      btnReleased = false;
      if(roastMode != 4){
        roastMode += 1;
      }
      else {
        roastMode = 0;
      }
    }
  }
  else btnReleased = true;
}
