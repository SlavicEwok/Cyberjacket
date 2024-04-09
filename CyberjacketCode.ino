#include <Adafruit_NeoPixel.h>

#define LED_PIN 23
#define NUM_LEDS 160
#define DELAY_MS 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

#define BUTTON_PIN_1 25
#define BUTTON_PIN_2 26
#define BUTTON_PIN_3 27
#define BUTTON_PIN_4 12 //BROKEN
#define BUTTON_PIN_5 14

volatile bool buttonPressed = false;
uint8_t brightness = 28; // Initial brightness, change as needed

void handleButtonPress() {
  buttonPressed = true;
}

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);
  pinMode(BUTTON_PIN_5, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_1), handleButtonPress, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_2), handleButtonPress, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_3), handleButtonPress, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_4), handleButtonPress, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_5), handleButtonPress, FALLING);
}

void loop() {
  if (buttonPressed) {

    strip.setBrightness(brightness);

    if (digitalRead(BUTTON_PIN_1) == LOW) {
      colorWipe(strip.Color(255, 0, 0), 5); // Red

    } else if (digitalRead(BUTTON_PIN_2) == LOW) {
      rainbow(10);

    } else if (digitalRead(BUTTON_PIN_3) == LOW) {
      bisexualPrideEffect();
    
    } else if (digitalRead(BUTTON_PIN_5) == LOW) {
      colorWipe(strip.Color(0, 255, 255), 5); // Cyan

    } else {
      colorWipe(strip.Color(0, 0, 0), 1); // Black
    }

    strip.show();

    buttonPressed = false;
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j = 0; j < 256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void bisexualPrideEffect() {
  int numPixels = strip.numPixels();

  // Pink (first third of the strip)
  for (int i = 0; i < numPixels / 3; i++) {
    strip.setPixelColor(i, strip.Color(255, 105, 180)); // Pink
  }

  // Purple (second third of the strip)
  for (int i = numPixels / 3; i < (2 * numPixels) / 3; i++) {
    strip.setPixelColor(i, strip.Color(138, 43, 226)); // Purple
  }

  // Blue (last third of the strip)
  for (int i = (2 * numPixels) / 3; i < numPixels; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 255)); // Blue
  }

  strip.show();
  delay(DELAY_MS);

  // Shift the colors to create a dynamic effect
  uint32_t lastColor = strip.getPixelColor(numPixels - 1);
  for (int i = numPixels - 1; i > 0; i--) {
    strip.setPixelColor(i, strip.getPixelColor(i - 1));
  }
  strip.setPixelColor(0, lastColor);

  strip.show();
  delay(DELAY_MS);
}
