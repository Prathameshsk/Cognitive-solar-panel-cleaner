#include <AFMotor.h>

// Motor Driver Shield
AF_DCMotor motor1(1); // Motor 1 connected to M1 and M2 terminals
AF_DCMotor motor2(2); // Motor 2 connected to M3 and M4 terminals
AF_DCMotor motor3(3); // Motor 3 connected to M3 and M4 terminals

// Pins for Voltage Sensor and Dust Sensor
const int voltageSensorPin = A0;
const int dustSensorPin = A1;

// Threshold values for voltage and dust levels
const float voltageThreshold = 10.0; // Example threshold voltage in volts
const int dustThreshold = 500; // Example threshold dust level

// Function to read the voltage from the voltage sensor
float readVoltageSensor() {
  float voltage = analogRead(voltageSensorPin) * (5.0 / 1023.0);
  return voltage;
}

// Function to move the cleaner to the specific panel
void moveCleanerToPanel(int panelNumber) {
  int moveTime = panelNumber * 1000; // 1 second per panel
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(moveTime);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

// Function to read the dust level from the dust sensor
int readDustSensor() {
  int dustLevel = analogRead(dustSensorPin);
  return dustLevel;
}

// Function to calculate the power required to move to the specific panel
float calculatePowerRequired(int panelNumber) {
  float powerRequiredPerPanel = 0.5; // Example power required per panel
  float totalPowerRequired = panelNumber * powerRequiredPerPanel;
  return totalPowerRequired;
}

// Function to clean the specific panel
void cleanSolarPanel(int panelNumber) {
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  delay(1000);
  motor3.run(RELEASE);
}

void setup() {
  // Setup code if any
}

void loop() {
  // Read voltage from sensor
  float voltage = readVoltageSensor();
  
  // Check if voltage is below threshold
  if (voltage < voltageThreshold) {
    // Read dust level from sensor
    int dustLevel = readDustSensor();
    
    // Check if dust level is above threshold
    if (dustLevel > dustThreshold) {
      // Calculate power required to reach the panel
      int panelNumber = 1; // Example panel number
      float powerRequired = calculatePowerRequired(panelNumber);
      
      // Calculate power loss due to dust
      float powerLoss = dustLevel * 0.1; // Example power loss calculation
      
      // Check if power loss is more than power required
      if (powerLoss > powerRequired) {
        // Move to the specific panel
        moveCleanerToPanel(panelNumber);
        
        // Clean the panel
        cleanSolarPanel(panelNumber);
      }
    }
  }
  
  // Add any additional code or delays if needed
}
