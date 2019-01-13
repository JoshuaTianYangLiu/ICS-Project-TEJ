#include <Adafruit_CircuitPlayground.h>
#include <math.h>
#define FINETUNE 13
boolean startTime = false;
boolean systemOn = true;
void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
}

void loop() {
  if(systemOn){
    capPassword();
    if (!startTime) {
      lightSensor();
      buttonClicks();
        if (isDoubleClap()){
          toggleLights();
        //Turn on lights
      }
    }
  }
}

void buttonClicks() {
  static boolean leftButtonPressed;
  static boolean rightButtonPressed;
  static boolean commandEntered = false;
  if (CircuitPlayground.leftButton() or CircuitPlayground.rightButton()) {
    commandEntered = true;
    if (CircuitPlayground.leftButton()) {
      leftButtonPressed = true;
    }
    if (CircuitPlayground.rightButton()) {
      rightButtonPressed = true;
    }
  } else {
    if (commandEntered) {
      if (leftButtonPressed xor rightButtonPressed) {
        weWishYouAMerry();
        rightButtonPressed = false;
        leftButtonPressed = false;
        //Add a more complicated tune
      }
      if (leftButtonPressed and rightButtonPressed) {
        //Opens Door
        CircuitPlayground.playTone(329, 500);
        CircuitPlayground.playTone(277, 500);
        CircuitPlayground.playTone(220, 500);
        openDoor();
        rightButtonPressed = false;
        leftButtonPressed = false;
      }
    }
  }
}
void weWishYouAMerry() {
  int x = 2;
  CircuitPlayground.playTone(147, 1000 / x);
  CircuitPlayground.playTone(196, 1000 / x);
  CircuitPlayground.playTone(196, 500 / x);
  CircuitPlayground.playTone(220, 500 / x);
  CircuitPlayground.playTone(196, 500 / x);
  CircuitPlayground.playTone(185, 500 / x);
  CircuitPlayground.playTone(165, 1000 / x);
  CircuitPlayground.playTone(165, 1000 / x);
  CircuitPlayground.playTone(659, 1000 / x);
  CircuitPlayground.playTone(220, 1000 / x);
  CircuitPlayground.playTone(220, 500 / x);
  CircuitPlayground.playTone(247, 500 / x);
  CircuitPlayground.playTone(220, 500 / x);
  CircuitPlayground.playTone(196, 500 / x);
  CircuitPlayground.playTone(185, 1000 / x);
  CircuitPlayground.playTone(147, 1000 / x);
  CircuitPlayground.playTone(147, 1000 / x);
  CircuitPlayground.playTone(247, 1000 / x);
  CircuitPlayground.playTone(247, 500 / x);
  CircuitPlayground.playTone(131, 500 / x);
  CircuitPlayground.playTone(247, 500 / x);
  CircuitPlayground.playTone(220, 500 / x);
  CircuitPlayground.playTone(196, 1000 / x);
  CircuitPlayground.playTone(165, 1000 / x);
  CircuitPlayground.playTone(147, 500 / x);
  CircuitPlayground.playTone(147, 500 / x);
  CircuitPlayground.playTone(165, 1000 / x);
  CircuitPlayground.playTone(220, 1000 / x);
  CircuitPlayground.playTone(185, 1000 / x);
  CircuitPlayground.playTone(196, 1000 / x);
  delay(1000 / x);
  CircuitPlayground.playTone(494, 1000 / x);
}

void capPassword() {
  int doorPassword[] = {2,2,2,2,2,2};
  int quitPassword[]={1,1,1,1,1};
  static int savedPassword[6];
  static boolean doorPassCorrect = true;
  static boolean togglePassCorrect = true;
  static int tL, tR, bL, bR = 0;
  static int passRounds = 0;
  static boolean passEntered = false;
  static boolean runPass = true;
  static int attempts = 0;
  static long timeStart = millis();
  long timeEnd = 0 ;
  static boolean resetPassStatus = true;


  if(resetPassStatus){
    doorPassCorrect = true;
    togglePassCorrect = true;
    resetPassStatus=false;
  }
  if (startTime) {

    timeEnd = millis();
  } else {
    timeStart = millis();
  }
  if (tLPressed() or tRPressed() or bLPressed() or bRPressed()) {
    if(!passEntered){
      CircuitPlayground.clearPixels();
    }
    if (tLPressed()) {
      tL = 1;
      CircuitPlayground.setPixelColor(0, 255, 0, 255);
      CircuitPlayground.setPixelColor(1, 255, 0, 255);
    }
    if (tRPressed()) {
      tR = 1;
      CircuitPlayground.setPixelColor(8, 255, 0, 255);
      CircuitPlayground.setPixelColor(9, 255, 0, 255);
    }
    if (bLPressed()) {
      bL = 1;
      CircuitPlayground.setPixelColor(3, 255, 0, 255);
      CircuitPlayground.setPixelColor(4, 255, 0, 255);
    }
    if (bRPressed()) {
      bR = 1;
      CircuitPlayground.setPixelColor(5, 255, 0, 255);
      CircuitPlayground.setPixelColor(6, 255, 0, 255);
    }
    startTime = true;
    passEntered = true;
    savedPassword[passRounds]=tL + tR * 2 + bL * 4 + bR * 8;
  } else {
    if (passEntered) {
      if ( timeEnd - timeStart < 120000) {
        if(!(savedPassword[passRounds]==quitPassword[passRounds] or savedPassword[passRounds]==doorPassword[passRounds])){
          flashIncorrect();
          passEntered = false;
          setCornerValues(&tL, &tR, &bL, &bR, 0);
          passRounds = 0;
          attempts++;
          resetPassStatus=true;
          if (attempts == 3) {
            for (int x = 0; x < 10; x++) {
              CircuitPlayground.playTone(220, 250);
              CircuitPlayground.playTone(340, 250);
            }
            attempts = 0;
            startTime = false;
          }else{
            CircuitPlayground.playTone(329, 500);
            CircuitPlayground.playTone(277, 500);
            CircuitPlayground.playTone(220, 500);
          }
        }
        if(passEntered){
          if(savedPassword[passRounds]==doorPassword[passRounds] and doorPassCorrect){
            if(passRounds+1 == sizeof(doorPassword)/sizeof(int)){
              flashCorrect();
              passEntered = false;
              setCornerValues(&tL, &tR, &bL, &bR, 0);
              startTime=false;
              passRounds=-1;
              attempts = 0;
              resetPassStatus=true;
              CircuitPlayground.playTone(220, 500);
              CircuitPlayground.playTone(277, 500);
              CircuitPlayground.playTone(329, 500); 
              //Open door
              openDoor();
            }
            passRounds++;
            passEntered = false;
          }else{
            doorPassCorrect = false;
          }
        }
        if(passEntered){
          if(savedPassword[passRounds]==quitPassword[passRounds] and togglePassCorrect){
            if(passRounds+1 == sizeof(quitPassword)/sizeof(int)){
              flashCorrect();
              passEntered = false;
              setCornerValues(&tL, &tR, &bL, &bR, 0);
              startTime=false;
              passRounds=-1;
              attempts = 0;
              resetPassStatus=true;
              CircuitPlayground.playTone(220, 500);
              CircuitPlayground.playTone(277, 500);
              CircuitPlayground.playTone(329, 500); 
              //Open toggle system
              systemOn=false;
            }
          passRounds++;
          passEntered = false;
          }else{
            togglePassCorrect = false;
          }
        }
      } else {
        flashIncorrect();
        passEntered = false;
        setCornerValues(&tL, &tR, &bL, &bR, 0);
        passRounds = 0;
        attempts++;
        doorPassCorrect = true;
        togglePassCorrect = true;
        if (attempts == 3) {
          for (int x = 0; x < 120; x++) {
            CircuitPlayground.playTone(220, 250);
            CircuitPlayground.playTone(340, 250);
          }
          attempts = 0;
          startTime = false;
        }else{
          CircuitPlayground.playTone(329, 500);
          CircuitPlayground.playTone(277, 500);
          CircuitPlayground.playTone(220, 500);
        }
      }
    } else {
      CircuitPlayground.clearPixels();
    }
  }
  if (timeEnd - timeStart > 120000 and !(timeEnd == 0)) {
    CircuitPlayground.clearPixels();
    for (int x = 0; x < 120; x++) {
      CircuitPlayground.playTone(220, 250);
      CircuitPlayground.playTone(340, 250);
    }
    startTime = false;
  }
}

void setCornerValues(int *tL, int *tR, int *bL, int *bR, int value) {
  *tL = value;
  *tR = value;
  *bL = value;
  *bR = value;
}


boolean tLPressed() {
  if (CircuitPlayground.readCap(2) > 100) {
    return true;
  } else {
    return false;
  }
}

boolean tRPressed() {
  if (CircuitPlayground.readCap(9) > 100) {
    return true;
  } else {
    return false;
  }
}

boolean bLPressed() {
  if (CircuitPlayground.readCap(0) > 100 or CircuitPlayground.readCap(1) > 100) {
    return true;
  } else {
    return false;
  }
}

boolean bRPressed() {
  if (CircuitPlayground.readCap(12) > 100 or CircuitPlayground.readCap(6) > 100) {
    return true;
  } else {
    return false;
  }
}
void flashIncorrect(){
  redLight();
  delay(200);
  CircuitPlayground.clearPixels();
  delay(200);
  redLight();
  delay(200);
  CircuitPlayground.clearPixels();
  delay(200);
  redLight();
  delay(200);
  CircuitPlayground.clearPixels();
}
void flashCorrect(){
  greenLight();
  delay(200);
  CircuitPlayground.clearPixels();
  delay(200);
  greenLight();
  delay(200);
  CircuitPlayground.clearPixels();
  delay(200);
  greenLight();
  delay(200);
  CircuitPlayground.clearPixels();
}

void greenLight() {
  for (int x = 0; x < 10; x++) {
    CircuitPlayground.setPixelColor(x, 0, 255, 0);
  }
}
void redLight() {
  for (int x = 0; x < 10; x++) {
    CircuitPlayground.setPixelColor(x, 255, 0, 0);
  }
}
void adjustLight(int brightness) {
  for (int x = 0; x < 10; x++) {
    CircuitPlayground.setPixelColor(x, brightness, brightness, brightness);
  }
}
void lightSensor() {
  static int value;
  value = CircuitPlayground.lightSensor();
  if (value < 70) {
    adjustLight(round((255.0 / 4900)*pow((value - 70.0), 2)));
    //turn on
  }
}
boolean isDoubleClap(){
  static boolean firstClap = false;
  static long firstClapTime;
  if (clap()){
    if(firstClap == false){
      firstClapTime = millis();
      firstClap = true;
    }
    else{
      if ( millis()-firstClapTime >500){
        firstClapTime= millis();
        firstClap = true;
      }else{
        firstClap = false;
        return true;
      }
    }
  }
  else{
    if (firstClap){
       if (millis()-firstClapTime>500){
          firstClap = false;
       }
    } 
  }
  return false;
}

boolean clap() {
  static int s[FINETUNE] = {0};

  for (int x = 0; x < FINETUNE - 1; x++) {
    s[x] = s[x + 1];
  }
  //Moves pos 14 to 13, 13 to 12, 12 to 11, 10 to 9 ect. Shifts all values one down the table

  s[FINETUNE - 1] = CircuitPlayground.mic.soundPressureLevel(10);
//  Below decides if its a clap
  if (detectRise(s[1], s[2]) and detectFall(s[2], s[FINETUNE - 1]) and noLargeBumps(s, FINETUNE - 2)) {
        return true;
    //Shows a spike on the graph when a clap is heard
  } else {
        return false;
    //Baseline
  }
}

boolean noLargeBumps(int tick[], int arrSize) {
  for ( int i = 2; i < arrSize - 1; i++) {
    if (tick[i + 1] - tick[i] > 5) {
      return false;
    }
  }
  return true;
}


boolean detectRise(int tick1, int tick2) {
  if ((tick2 - tick1) > 20) {
    return true;
  } else {
    return false;
  }
}
//Compares the rise between the two "ticks" beside each other
boolean detectFall(int tick1, int tick2) {
  if ((tick1 - tick2) > 10) {
    return true;
  } else {
    return false;
  }
}
//Compares the fall between the height of the clap and the finetune you set - 2 "ticks" beside each other
void openDoor(){
    analogWrite(3,230);
    delay(500);
    analogWrite(3,0);
    delay(10000);
    analogWrite(3,90);
    delay(400);
    analogWrite(3,0);
}
void toggleLights(){
  static boolean isOn = false;
  if (isOn ){
    for(int x=255;x>0;x--){
      analogWrite(10,x);
      delay(4);
    }
  }
  if(!isOn){
    for(int x=0;x<256;x++){
      analogWrite(10,x);
      delay(4);
    }
  }
  isOn = !isOn;
}
