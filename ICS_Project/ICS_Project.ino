#include <Adafruit_CircuitPlayground.h>
#include <math.h>
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
  Serial.println(CircuitPlayground.mic.soundPressureLevel(10));
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
  int password[] = {3, 4, 5, 6, 7, 8};
  static int tL, tR, bL, bR = 0;
  static int passRounds = 0;
  static boolean passEntered = false;
  static boolean runPass = true;
  static int attempts = 0;
  static long timeStart = millis();
  long timeEnd = 0 ;



  if (startTime) {

    timeEnd = millis();
  } else {
    timeStart = millis();
  }
  if (tLPressed() or tRPressed() or bLPressed() or bRPressed()) {
    if (!passEntered) {
      startTime = true;
    }
    toggleValues(&tL, &tR, &bL, &bR);
    passEntered = true;
  } else {
    if (passEntered) {
      if (tL + tR * 2 + bL * 4 + bR * 8 == password[passRounds] and timeEnd - timeStart < 30000) {
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
        delay(200);
        CircuitPlayground.playTone(220, 500);
        CircuitPlayground.playTone(277, 500);
        CircuitPlayground.playTone(329, 500);
        passEntered = false;
        setCornerValues(&tL, &tR, &bL, &bR, 0);
        passRounds++;
        if (passRounds == sizeof(password) / 2) {
          //Run code to disable password and open door.
        }
      } else {
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
        delay(200);
        CircuitPlayground.playTone(329, 500);
        CircuitPlayground.playTone(277, 500);
        CircuitPlayground.playTone(220, 500);
        passEntered = false;
        setCornerValues(&tL, &tR, &bL, &bR, 0);
        passRounds = 0;
        attempts++;
        if (attempts == 3) {
          for (int x = 0; x < 10; x++) {
            CircuitPlayground.playTone(220, 250);
            CircuitPlayground.playTone(340, 250);
          }
          attempts = 0;
          startTime = false;
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
  //  if ((tLPressed()==tLPassword[passRounds]) and (tRPressed()==tRPassword[passRounds]) and (bLPressed()==bLPassword[passRounds]) and (bRPressed()== bRPassword[passRounds])){
  //      passRounds++;
  //  }
}

void toggleValues(int *tL, int *tR, int *bL, int *bR) {
  if (tLPressed()) {
    *tL = 1;
    CircuitPlayground.setPixelColor(0, 255, 0, 255);
    CircuitPlayground.setPixelColor(1, 255, 0, 255);
  }
  if (tRPressed()) {
    *tR = 1;
    CircuitPlayground.setPixelColor(8, 255, 0, 255);
    CircuitPlayground.setPixelColor(9, 255, 0, 255);
  }
  if (bLPressed()) {
    *bL = 1;
    CircuitPlayground.setPixelColor(3, 255, 0, 255);
    CircuitPlayground.setPixelColor(4, 255, 0, 255);
  }
  if (bRPressed()) {
    *bR = 1;
    CircuitPlayground.setPixelColor(5, 255, 0, 255);
    CircuitPlayground.setPixelColor(6, 255, 0, 255);
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
