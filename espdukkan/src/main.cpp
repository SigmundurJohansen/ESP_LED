#include <Arduino.h>
#include <FastLED.h>
#include <U8g2lib.h>
//U8G2_SSD1306_128X32_UNIVISION_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ 21, /* data=*/ 20, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather M0 Basic Proto + FeatherWing OLED
U8G2_SSD1306_128X32_UNIVISION_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
//U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED

// How many leds in your strip?
#define NUM_LEDS 1

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 19
#define CLOCK_PIN 18

// Define the array of leds
CRGB leds[NUM_LEDS];
int inter = 200;

void setup() { 
    // ## Clockless types ##
    // FastLED.addLeds<SK6812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<SK6822, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SK6822, DATA_PIN, RGB>(leds, NUM_LEDS);
    // ## Clocked (SPI) types ##
     FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN>(leds, 1);  // BGR ordering is typical
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tr);
}
void draw(const char *s)
{
  u8g2.firstPage();
  do {
    u8g2.drawStr(2,15,"PowerSaveTest");    
    u8g2.drawStr(2,30,s);    
    u8g2.drawFrame(0,0,u8g2.getDisplayWidth(),u8g2.getDisplayHeight() );
  } while ( u8g2.nextPage() );
  delay(2000);
}

void loop() { 
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
  u8g2.setPowerSave(0);
  draw("power on / x");
  u8g2.setPowerSave(1);
  draw("power off / x");
  u8g2.setPowerSave(0);
  draw("power on / +");
  u8g2.setPowerSave(1);
  draw("power off / +");
}