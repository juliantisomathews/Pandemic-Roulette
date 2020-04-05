//

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_WIDTH 128 // OLED display width, in pixels
#define OLED_HEIGHT 64 // OLED display height, in pixels

#define OLED_ADDR 0x3C

int fidget = 0;
int state = 0;

String text[8] = {"You have  Corona    virus", "You don't have      Corona    virus", "You have  Corona    virus", "You don't have      Corona    virus", "You have  Corona    virus", "You don't have      Corona    virus", "You have  Corona    virus", "You don't have      Corona    virus"};

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

int hallSensorPin = 2;     
int ledPin =  13;    
int previousState = 0; 
         
void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  
  pinMode(ledPin, OUTPUT);      
  pinMode(hallSensorPin, INPUT);     
}

void loop(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(text[fidget]);
  display.display();

  // conditional statement saying if the variable state is low (not above the sesnor) go through the array
  
  state = digitalRead(hallSensorPin);
  if (state == LOW && previousState == 0) {        
     fidget++;  

     if (fidget == 8)
        fidget = 0;
        previousState = 1;
  }

  // what allows the the statement to not run through the array when it's not hovering over it and only once it's passed it (i.e previous state = 0 not 1);

      if (state == HIGH && previousState == 1) {
         previousState = 0;

      
    digitalWrite(ledPin, HIGH);
  } 
  else {
    digitalWrite(ledPin, LOW); 
  }

  
}
