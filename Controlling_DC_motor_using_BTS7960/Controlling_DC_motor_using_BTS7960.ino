// Define motor control pins
const int RPWM_PIN = 9;
const int LPWM_PIN = 10;
const int R_EN_PIN = 7;
const int L_EN_PIN = 8;

void setup() {
  // Set the motor control pins as outputs
  pinMode(RPWM_PIN, OUTPUT);
  pinMode(LPWM_PIN, OUTPUT);
  pinMode(R_EN_PIN, OUTPUT);
  pinMode(L_EN_PIN, OUTPUT);

  // Enable the motor driver
  digitalWrite(R_EN_PIN, HIGH);
  digitalWrite(L_EN_PIN, HIGH);
}

void loop() {
  // Example: Accelerate motor in one direction
  for (int speed = 0; speed <= 255; speed++) {
    analogWrite(RPWM_PIN, speed); // Speed increases
    analogWrite(LPWM_PIN, 0);     // LPWM must be 0 for forward motion
    delay(20);                    // Wait a bit to see the speed change
  }

  // Example: Decelerate motor to stop
  for (int speed = 255; speed >= 0; speed--) {
    analogWrite(RPWM_PIN, speed); // Speed decreases
    analogWrite(LPWM_PIN, 0);     // LPWM must be 0 for forward motion
    delay(20);                    // Wait a bit to see the speed change
  }

  delay(1000); // Wait before changing direction

  // Example: Accelerate motor in the opposite direction
  for (int speed = 0; speed <= 255; speed++) {
    analogWrite(LPWM_PIN, speed); // Speed increases in the opposite direction
    analogWrite(RPWM_PIN, 0);     // RPWM must be 0 for reverse motion
    delay(20);                    // Wait a bit to see the speed change
  }

  // Example: Decelerate motor to stop
  for (int speed = 255; speed >= 0; speed--) {
    analogWrite(LPWM_PIN, speed); // Speed decreases in the opposite direction
    analogWrite(RPWM_PIN, 0);     // RPWM must be 0 for reverse motion
    delay(20);                    // Wait a bit to see the speed change
  }

  delay(1000); // Wait before restarting the loop
}
