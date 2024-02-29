#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <Servo.h>
// Pinii motor 1
#define mpin00 5
#define mpin01 6
// Pinii motor 2
#define mpin10 3
#define mpin11 11

#define PIN 8 
#define NUMPIXELS 8   

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
const int sensorLeft = 2;
const int sensorRight = 4;

int sensorStateLeft = 0;
int sensorStateRight = 0;

int buttonApin = A3;
int ok = 0;

void setup() {
  pixels.begin();

  pinMode(buttonApin, INPUT_PULLUP);  

  // configurarea pinilor motor ca iesire, initial valoare 0
  digitalWrite(mpin00, 0);
  digitalWrite(mpin01, 0);
  digitalWrite(mpin10, 0);
  digitalWrite(mpin11, 0);
  pinMode(mpin00, OUTPUT);
  pinMode(mpin01, OUTPUT);
  pinMode(mpin10, OUTPUT);
  pinMode(mpin11, OUTPUT);
  // pin LED
  pinMode(13, OUTPUT);
  delay(1000);
}

// Functie pentru controlul unui motor
// Intrare: pinii m1 si m2, directia si viteza
void StartMotor(int m1, int m2, int forward, int speed) {
  if (speed == 0)  // oprire
  {
    digitalWrite(m1, 0);
    digitalWrite(m2, 0);
  } else {
    if (forward) {
      digitalWrite(m2, 0);
      analogWrite(m1, speed);  // folosire PWM
    } else {
      digitalWrite(m1, 0);
      analogWrite(m2, speed);
    }
  }
}

// Functie de siguranta
// Executa oprire motoare, urmata de delay
void delayStopped(int ms) {
  StartMotor(mpin00, mpin01, 0, 0);
  StartMotor(mpin10, mpin11, 0, 0);
  delay(ms);
}

void loop() {
  pixels.clear();
  

  if (digitalRead(buttonApin) == LOW)
  {
    ok = 1;
  }

  if (ok == 1) {
    if ((digitalRead(sensorLeft)==0) && (digitalRead(sensorRight)==0)) {
         for(int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(0, 150, 0));
          pixels.show();
        }
        forward();
    }
    if ((digitalRead(sensorLeft)==1) && (digitalRead(sensorRight)==0)) {
        for(int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(0, 0, 150));
          pixels.show();
        }
        turnRight();
    }
    if ((digitalRead(sensorLeft)==0) && (digitalRead(sensorRight)==1)) {
        for(int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(150, 0, 150));
          pixels.show();
        }
        turnLeft();
    }
    if ((digitalRead(sensorLeft)==1) && (digitalRead(sensorRight)==1)) {
        for(int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(150, 0, 0));
          pixels.show();
        }
        stop();
    }
  } else {
    for(int i=0; i<NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(150, 0, 0));
      pixels.show();
    }
  }
}

void forward() {
  StartMotor(mpin00, mpin01, 1, 30);
  StartMotor(mpin10, mpin11, 0, 30);
}

void turnRight() {
  StartMotor(mpin00, mpin01, 1, 15);
  StartMotor(mpin10, mpin11, 0, 50);
}

void turnLeft() {
  StartMotor(mpin00, mpin01, 1, 50);
  StartMotor(mpin10, mpin11, 0, 15);
}

void stop() {
  StartMotor(mpin00, mpin01, 0, 0);
  StartMotor(mpin10, mpin11, 0, 0);
}
