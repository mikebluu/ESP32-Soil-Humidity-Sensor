#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <esp32-hal-cpu.h>

// Pin Definitions
const int SensorPin = A0;        // Analog pin for soil moisture sensor
const int ButtonPin = 19;        // Digital pin for button
const int DrySoilValue = 2750;   // Analog reading for dry soil
const int WateredSoilValue = 1150; // Analog reading for watered soil

// Global Variables
int buttonState;                 // Current state of the button
int lastButtonState = HIGH;      // Previous state of the button, default HIGH.
int soilMoistureValue;           // Analog reading from soil moisture sensor
int soilMoisturePercentage = 0;  // Calculated percentage of soil moisture

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variables for scrolling text
unsigned long scrollStartTime = 0;     // Time when scrolling started
const int scrollInterval = 15;          // Interval between character movements in milliseconds
int scrollOffset = 0;                   // Current scrolling offset
bool scrolling = false;                 // Flag indicating if scrolling is active
bool showSoilRH = false;                // Flag indicating if Soil RH should be displayed
unsigned long lastSoilRHDisplayTime = 0; // Time when Soil RH was last displayed
const int soilRHDisplayDuration = 3000; // Display duration for Soil RH in milliseconds
int soilRHCount = 0;                    // Counter for number of times Soil RH has been displayed
const int soilRHDisplayLimit = 2;       // Number of times to display Soil RH

void setup() {
  Serial.begin(74880); // Start serial communication
  setCpuFrequencyMhz(80); // Sets the ESP32's CPU Frequency to 80 MHz for power saving
  pinMode(ButtonPin, INPUT_PULLUP); // Set button pin as input with internal pull-up resistor

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Endless loop if display initialization fails
  }
  display.clearDisplay(); // Clear display
}

void loop() {
  buttonState = digitalRead(ButtonPin); // Read button state
  soilMoistureValue = analogRead(SensorPin); // Read soil moisture value

  // Calculate soil moisture percentage
  soilMoisturePercentage = map(soilMoistureValue, DrySoilValue, WateredSoilValue, 0, 100); // Correlate the analog value to a percentage
  soilMoisturePercentage = constrain(soilMoisturePercentage, 0, 100); // Constrain percentage within 0-100 range

  // Check if button is pressed
  if (buttonState == LOW && lastButtonState == HIGH) {
    scrolling = false; // Stop scrolling
    showSoilRH = true; // Display Soil RH
    lastSoilRHDisplayTime = millis(); // Record time of Soil RH display
    scrollOffset = 0; // Reset scroll offset
    soilRHCount = 0; // Reset Soil RH count
  }

  // Check if Soil RH should be displayed
  if (showSoilRH) {
    unsigned long currentTime = millis(); // Get current time
    // Check if it's time to stop displaying Soil RH
    if (currentTime - lastSoilRHDisplayTime >= soilRHDisplayDuration && soilRHCount >= soilRHDisplayLimit) {
      showSoilRH = false; // Stop displaying Soil RH
      scrolling = true; // Start scrolling again
      display.clearDisplay(); // Clear display
      scrollOffset = 0; // Reset scroll offset
    }

    // Start scrolling Soil RH text
    if (currentTime - scrollStartTime >= scrollInterval) {
      scrollOffset--; // Move text to the left
      scrollStartTime = currentTime; // Record current time

      display.clearDisplay(); 
      display.dim(0); // Set display brightness to normal
      display.setTextSize(3);
      display.setTextColor(WHITE); 
      display.setCursor(scrollOffset, 10); // Set cursor position
      display.print("  Soil RH: "); 
      display.print(soilMoisturePercentage); 
      display.println("% "); 
      display.display(); // Update display

      // Reset offset when text goes beyond the display width
      if (scrollOffset < -SCREEN_WIDTH * 2) {
        scrollOffset = SCREEN_WIDTH;
      }

      // Check if Soil RH message has been displayed twice
      if (scrollOffset == -SCREEN_WIDTH * 2 && soilRHCount < soilRHDisplayLimit) {
        soilRHCount++; // Increments the Soil RH appearances counter
      }
    }
  } else {
    // Show Waiting message
    scrolling = true; // Start scrolling
    unsigned long currentTime = millis(); // Get current time
    // Check if it's time to scroll again
    if (currentTime - scrollStartTime >= scrollInterval) {
      scrollOffset--; 
      scrollStartTime = currentTime;

      display.clearDisplay(); 
      display.dim(1); // Set display brightness to dim
      display.setTextSize(3); 
      display.setTextColor(WHITE); 
      display.setCursor(scrollOffset, 10); 
      display.println("  Waiting for button press"); // Display waiting message
      display.display(); 

      // Reset offset when text goes beyond the display width
      if (scrollOffset < -SCREEN_WIDTH * 4) {
        scrollOffset = SCREEN_WIDTH;
      }
    }
  }

  lastButtonState = buttonState; // Update last button state
}
