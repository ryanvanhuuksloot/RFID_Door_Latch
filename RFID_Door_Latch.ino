#include <Wire.h>
#include <SPI.h>
#include <Servo.h> 
#include <Adafruit_PN532.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif


Servo myservo; 


// Neopixel Pins
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

// RFID Pins
#define PN532_IRQ   (2)
#define PN532_RESET (3)  // Not connected by default on the NFC Shield

// Setup NFC shield
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
// also change #define in Adafruit_PN532.cpp library file
   #define Serial SerialUSB
#endif


// Control and feedback pins
int servoPin = 9;
int feedbackPin = A0;
 
// Calibration values
int minDegrees;
int maxDegrees;
int minFeedback;
int maxFeedback;
int tolerance = 2; // max feedback measurement error

// Other Values
int val;
String UIDString;
 
// Function to test Servo
void calibrate(Servo servo, int analogPin, int minPos, int maxPos)
{
  // Move to the minimum position and record the feedback value
  servo.write(minPos);
  minDegrees = minPos;
  delay(2000); // make sure it has time to get there and settle
  minFeedback = analogRead(analogPin);
  
  // Move to the maximum position and record the feedback value
  servo.write(maxPos);
  maxDegrees = maxPos;
  delay(2000); // make sure it has time to get there and settle
  maxFeedback = analogRead(analogPin);
  Serial.println(minDegrees); 
  Serial.println(maxDegrees);  
}

void setup(void) {
  #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
  #endif
  Serial.begin(115200);
  Serial.println("Hello!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
  
  Serial.println("Waiting for an ISO14443A Card ...");

    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  // Setup RFID + Neopixel
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  myservo.attach(servoPin);
  myservo.write(10);
}

void loop(void) {
  Serial.println("Hello!");
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  //uint8_t value[] = { 0, 0, 0, 16, 123, 222, 22 }; Value of the "good card"
  
  // Wait for an NTAG203 card.  When one is found 'uid' will be populated with
  // the UID, and uidLength will indicate the size of the UUID 
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  if (success) {
    Serial.println("Found an ISO14443A card");
    UIDString = "";
    for (byte i = 0; i < uidLength; i++) {
      UIDString = UIDString + String(uid[i]);
    }
    
    if (UIDString == "1612322222")
    {
        colorWipe(strip.Color(0, 255, 0), 50); // Green
        myservo.write(130);
        delay(2000);
        colorWipe(strip.Color(255, 0, 0), 50); // Red
        myservo.write(10);
    }
    else
    {
        colorWipe(strip.Color(0, 0, 255), 50); // Blue
        delay(500);
        colorWipe(strip.Color(255, 0, 0), 50); // Red
    }
  }
}

// NEOPIXEL FUNCTIONS BELOW (PROVIDED)

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
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

