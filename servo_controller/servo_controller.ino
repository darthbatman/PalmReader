#include <Servo.h>

const boolean BRAILLE_ALL_DOWN[] = { false, false, false, false, false, false };
const boolean BRAILLE_ALL_UP[] = { true, true, true, true, true, true };
const boolean BRAILLE_A[] = { true, false, false, false, false, false };
const boolean BRAILLE_B[] = { true, false, true, false, false, false };
const boolean BRAILLE_C[] = { true, true, false, false, false, false };
const boolean BRAILLE_D[] = { true, true, false, true, false, false };
const boolean BRAILLE_E[] = { true, false, false, true, false, false };
const boolean BRAILLE_F[] = { true, true, true, false, false, false };
const boolean BRAILLE_G[] = { true, true, true, true, false, false };
const boolean BRAILLE_H[] = { true, false, true, true, false, false };
const boolean BRAILLE_I[] = { false, true, true, false, false, false };
const boolean BRAILLE_J[] = { false, true, true, true, false, false };
const boolean BRAILLE_K[] = { true, false, false, false, true, false };
const boolean BRAILLE_L[] = { true, false, true, false, true, false };
const boolean BRAILLE_M[] = { true, true, false, false, true, false };
const boolean BRAILLE_N[] = { true, true, false, true, true, false };
const boolean BRAILLE_O[] = { true, false, false, true, true, false };
const boolean BRAILLE_P[] = { true, true, true, false, true, false };
const boolean BRAILLE_Q[] = { true, true, true, true, true, false };
const boolean BRAILLE_R[] = { true, false, true, true, true, false };
const boolean BRAILLE_S[] = { false, true, true, false, true, false };
const boolean BRAILLE_T[] = { false, true, true, true, true, false };
const boolean BRAILLE_U[] = { true, false, false, false, true, true };
const boolean BRAILLE_V[] = { true, false, true, false, true, true };
const boolean BRAILLE_W[] = { false, true, true, true, false, true };
const boolean BRAILLE_X[] = { true, true, false, false, true, true };
const boolean BRAILLE_Y[] = { true, true, false, true, true, true };
const boolean BRAILLE_Z[] = { true, false, false, true, true, true };
const boolean BRAILLE_0[] = { false, true, true, true, false, false };
const boolean BRAILLE_1[] = { true, false, false, false, false, false };
const boolean BRAILLE_2[] = { true, false, true, false, false, false };
const boolean BRAILLE_3[] = { true, true, false, false, false, false };
const boolean BRAILLE_4[] = { true, true, false, true, false, false };
const boolean BRAILLE_5[] = { true, false, false, true, false, false };
const boolean BRAILLE_6[] = { true, true, true, false, false, false };
const boolean BRAILLE_7[] = { true, true, true, true, false, false };
const boolean BRAILLE_8[] = { true, false, true, true, false, false };
const boolean BRAILLE_9[] = { false, true, true, false, false, false };

const int timeBetweenDisplayingChars = 5000;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

const boolean * brailleCharFor(char c) {
  switch (c) {
    case 'A':
      return BRAILLE_A;
    case 'B':
      return BRAILLE_B;
    case 'C':
      return BRAILLE_C;
    case 'D':
      return BRAILLE_D;
    case 'E':
      return BRAILLE_E;
    case 'F':
      return BRAILLE_F;
    case 'G':
      return BRAILLE_G;
    case 'H':
      return BRAILLE_H;
    case 'I':
      return BRAILLE_I;
    case 'J':
      return BRAILLE_J;
    case 'K':
      return BRAILLE_K;
    case 'L':
      return BRAILLE_L;
    case 'M':
      return BRAILLE_M;
    case 'N':
      return BRAILLE_N;
    case 'O':
      return BRAILLE_O;
    case 'P':
      return BRAILLE_P;
    case 'Q':
      return BRAILLE_Q;
    case 'R':
      return BRAILLE_R;
    case 'S':
      return BRAILLE_S;
    case 'T':
      return BRAILLE_T;
    case 'U':
      return BRAILLE_U;
    case 'V':
      return BRAILLE_V;
    case 'W':
      return BRAILLE_W;
    case 'X':
      return BRAILLE_X;
    case 'Y':
      return BRAILLE_Y;
    case 'Z':
      return BRAILLE_Z;
    case '0':
      return BRAILLE_0;
    case '1':
      return BRAILLE_1;
    case '2':
      return BRAILLE_2;
    case '3':
      return BRAILLE_3;
    case '4':
      return BRAILLE_4;
    case '5':
      return BRAILLE_5;
    case '6':
      return BRAILLE_6;
    case '7':
      return BRAILLE_7;
    case '8':
      return BRAILLE_8;
    case '9':
      return BRAILLE_9;
    default:
      return BRAILLE_ALL_DOWN;
  }
}

void activateBrailleChar(const boolean *c) {
  int servoPos;
  for (servoPos = 0; servoPos < 90; servoPos++) {
    if (c[0]) {
      servo1.write(servoPos);
    } else {
      servo1.write(0);
    }
    if (c[1]) {
      servo2.write(servoPos);
    } else {
      servo2.write(0);
    }
    if (c[2]) {
      servo3.write(servoPos);
    } else {
      servo3.write(0);
    }
    if (c[3]) {
      servo4.write(servoPos);
    } else {
      servo4.write(0);
    }
    if (c[4]) {
      servo5.write(servoPos);
    } else {
      servo5.write(0);
    }
    if (c[5]) {
      servo6.write(servoPos);
    } else {
      servo6.write(0);
    }
    delay(2);
  }
}

void activateBrailleString(String s) {
  s.toUpperCase();
  int i;
  for (i = 0; i < s.length(); i++) {
    activateBrailleChar(brailleCharFor(s.charAt(i)));
    delay(timeBetweenDisplayingChars);
  }
}

void setup() {
  servo1.attach(3);
  servo2.attach(11);
  servo3.attach(5);
  servo4.attach(10);
  servo5.attach(6);
  servo6.attach(9);
}

void loop() {
  activateBrailleString("tony");
}
