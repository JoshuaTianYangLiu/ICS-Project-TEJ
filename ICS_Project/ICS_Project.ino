#include <Adafruit_CircuitPlayground.h>
#include <math.h>
#define FINETUNE 13
boolean open = false;
boolean startTime = false;
void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  //  Serial.print("Capsense #3: "); Serial.println(CircuitPlayground.readCap(3));
  //  Serial.print("Capsense #2: "); Serial.println(CircuitPlayground.readCap(2));
  //  Serial.print("Capsense #0: "); Serial.println(CircuitPlayground.readCap(0));
  //  Serial.print("Capsense #1: "); Serial.println(CircuitPlayground.readCap(1));
  //  Serial.print("Capsense #12: "); Serial.println(CircuitPlayground.readCap(12));
  //  Serial.print("Capsense #6: "); Serial.println(CircuitPlayground.readCap(6));
  //  Serial.print("Capsense #9: "); Serial.println(CircuitPlayground.readCap(9));
  //  Serial.print("Capsense #10: "); Serial.println(CircuitPlayground.readCap(10));
  capPassword();
  buttonClicks();
  if (!startTime) {
    lightSensor();
  }
  
  // Serial.println(CircuitPlayground.mic.soundPressureLevel(10));
  /*
  Serial.print(95);
  Serial.print(" ");
  Serial.print(90);
  Serial.print(" ");
  Serial.print(80);
  Serial.print(" ");
  Serial.print(75);
  Serial.print(" ");
  Serial.print(70);
  Serial.print(" ");
  Serial.print(65);
  Serial.print(" ");
  
  Serial.print(60);
  Serial.print(" ");
  Serial.print(48);
  Serial.print(" ");
  */
  // Uncomment these, they will give you a base line for 95, 90, 80, and 50
  if (isDoubleClap()){
      //Turn on lights
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
  int togglePassword[]={1,1,1,1,1};
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
        if(!(savedPassword[passRounds]==togglePassword[passRounds] or savedPassword[passRounds]==doorPassword[passRounds])){
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
            }
            passRounds++;
            passEntered = false;
          }else{
            doorPassCorrect = false;
          }
        }
        if(passEntered){
          if(savedPassword[passRounds]==togglePassword[passRounds] and togglePassCorrect){
            if(passRounds+1 == sizeof(togglePassword)/sizeof(int)){
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
    } else {
      CircuitPlayground.clearPixels();
    }
  }
  if (timeEnd - timeStart > 120000 and !(timeEnd == 0)) {
    CircuitPlayground.clearPixels();
    for (int x = 0; x < 10; x++) {
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
  if (CircuitPlayground.readCap(3) > 100 or CircuitPlayground.readCap(2) > 100) {
    return true;
  } else {
    return false;
  }
}

boolean tRPressed() {
  if (CircuitPlayground.readCap(9) > 100 or CircuitPlayground.readCap(10) > 100) {
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
  //  Serial.print("Light Sensor: ");
  //  Serial.println(brightness);
  for (int x = 0; x < 10; x++) {
    CircuitPlayground.setPixelColor(x, brightness, brightness, brightness);
  }
}
void lightSensor() {
  static int value;
  value = CircuitPlayground.lightSensor();
  //  Serial.print("Light Sensor: ");
  //  Serial.println(value);
  if (value < 70) {
    adjustLight(round((255.0 / 4900)*pow((value - 70.0), 2)));
    //turn on
  } else {
    if (open) {
      adjustLight(0);
      //turn off
    }
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
//  Serial.println(s[2]);
  //Wave length of sound
  //Below decides if its a clap
  if (detectRise(s[1], s[2]) and detectFall(s[2], s[FINETUNE - 1]) and noLargeBumps(s, FINETUNE - 2)) {
//    Serial.print(100);
//    Serial.print(" ");
        return true;
    //Shows a spike on the graph when a clap is heard
  } else {
//    Serial.print(30);
//    Serial.print(" ");
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
  if ((tick2 - tick1) > 30) {
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
