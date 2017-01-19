/*
 * This is a minimal example, see extra-examples.cpp for a version
 * with more explantory documentation, example routines, how to
 * hook up your pixels and all of the pixel types that are supported.
 *
 */

/* button code snippet from: https://github.com/bkvarda/shamebutton */

#include "application.h"
#include "neopixel/neopixel.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_COUNT 6
#define PIXEL_TYPE WS2812B

bool pixels_on = false;
bool finish_recording = false;
bool finish_playing = false;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
uint32_t red = strip.Color(122,0,0);
uint32_t green = strip.Color(30, 210, 30);
uint32_t off = strip.Color(0,0,0);

int corkState = 0;
//int pwrState = 1;

int cork = D5;
//int pwr = A5;

char corkString[40];
//char pwrString[40];

int Timer = 0;


void setup()
    {
      strip.begin();
      strip.show(); // Initialize all pixels to 'off'
      Serial.begin(9600);
      pinMode(cork, INPUT);
      //pinMode(pwr, OUTPUT);
      //digitalWrite(pwr, HIGH);
      Serial.println("finished setup");

    }

void loop() {

  /*if (corkState == HIGH && pixels_on){
      delay(100);
  }*/
  delay(100);
  corkState = digitalRead(cork); //get the state of the button
  Serial.print("corkState is ");
  Serial.println(corkState);
  Serial.print("PO is ");
  Serial.println(pixels_on);

    if (corkState == LOW && pixels_on) {
      // turn lights off
        Serial.println("cork is in");
        for  (int i=0; i<6; i++) {
            strip.setPixelColor(i,off);
        }
        strip.show();
        pixels_on = false;
    }


    if (corkState == HIGH && !pixels_on) {
        // display recording lights in red
        pixels_on = true;
        Serial.println("cork is out");
        for  (int i=0; i<6; i++) {
            strip.setPixelColor(i,red);


        }
        strip.show();

        for (int i=0; i<6; i++) {
            strip.setPixelColor(i,off);
            delay(10000);
            strip.show();
            corkState = digitalRead(cork);
            if (corkState == LOW) {
                //delay(1000);
                break;
            }
            Timer = Timer + 10000;
        }

        finish_recording = true;

    }

    if (corkState == LOW && finish_recording && !finish_playing) {

      // display playback lights green
        Serial.println("cork is in");
        for  (int i=0; i<6; i++) {
            strip.setPixelColor(i,green);
        }
        strip.show();
        pixels_on = true;
        delay(Timer + 10000);
        Timer = 0;
        finish_playing = true;
    }

    if (corkState == LOW && finish_playing) {
        for  (int i=0; i<6; i++) {
            strip.setPixelColor(i,off);
        }
        strip.show();
        pixels_on = false;
        finish_recording = false;
        finish_playing = false;
    }

}
