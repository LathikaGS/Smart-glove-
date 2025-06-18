#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  Serial.println("Smart Glove Ready");
}

void loop() {
  // Flex sensor inputs (A0 to A4)
  int flex1 = analogRead(A0);  // Thumb
  int flex2 = analogRead(A1);  // Index
  int flex3 = analogRead(A2);  // Middle
  int flex4 = analogRead(A3);  // Ring
  int flex5 = analogRead(A4);  // Little

  // MPU6050 accelerometer data
  int ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // Convert analog to boolean based on threshold
  bool isF1 = flex1 > 200;
  bool isF2 = flex2 > 220;
  bool isF3 = flex3 > 215;
  bool isF4 = flex4 > 230;
  bool isF5 = flex5 > 210;

  // Count how many fingers are bent
  int bentCount = isF1 + isF2 + isF3 + isF4 + isF5;

  // ------------ GESTURE CONDITIONS ------------

  // Single finger gestures
  if (bentCount == 1) {
    if (isF1) Serial.println("Gesture: Hello");
    else if (isF2) Serial.println("Gesture: Thank You");
    else if (isF3) Serial.println("Gesture: Sorry");
    else if (isF4) Serial.println("Gesture: Welcome");
    else if (isF5) Serial.println("Gesture: Fine");
  }

  // Two-finger gestures
  else if (bentCount == 2) {
    if (isF1 && isF2) Serial.println("Gesture: Please");
    else if (isF3 && isF4) Serial.println("Gesture: Nice");
    else if (isF4 && isF5) Serial.println("Gesture: No");
    else if (isF2 && isF3) Serial.println("Gesture: Yes");
  }

  // Three-finger gestures
  else if (bentCount == 3) {
    if (isF1 && isF2 && isF3) Serial.println("Gesture: Good");
    else if (isF2 && isF3 && isF4) Serial.println("Gesture: What");
    else if (isF3 && isF4 && isF5) Serial.println("Gesture: Love");
  }

  // Four-finger gestures
  else if (bentCount == 4) {
    if (!isF1) Serial.println("Gesture: How are you");
    else if (!isF5) Serial.println("Gesture: Where");
  }

  // All fingers bent
  else if (bentCount == 5) {
    Serial.println("Gesture: Good Morning");
  }

  // No fingers bent
  else if (bentCount == 0) {
    // Use MPU6050 values to detect motion-based gestures
    if (ax > 15000) {
      Serial.println("Gesture: Stop");
    } else if (ay > 15000) {
      Serial.println("Gesture: Come");
    } else if (az > 15000) {
      Serial.println("Gesture: Go");
    } else if (az < -15000) {
      Serial.println("Gesture: Back");
    } else {
      Serial.println("Gesture: Neutral");
    }
  }

  delay(2000);  // Adjust as needed
}
