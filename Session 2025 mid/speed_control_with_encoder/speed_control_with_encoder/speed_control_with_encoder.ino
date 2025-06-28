// === Motor control pins for BTS7960 ===
const int RPWM = 5;
const int LPWM = 6;
const int R_EN = 7;
const int L_EN = 8;

// === Encoder pins ===
const int ENCODER_A = 2;
const int ENCODER_B = 3;

// === Encoder variables ===
volatile long encoderTicks = 0;
long lastEncoderTicks = 0;
unsigned long lastMillis = 0;

// === Motor/encoder specs ===
int encoderCPR = 330;                // Can be changed using calibration
const float wheelDiameter = 0.065;   // meters
const float wheelCircumference = 3.1416 * wheelDiameter;

// === Control variables ===
float targetSpeed = 0.0;    // m/s
float currentSpeed = 0.0;   // m/s
int pwmValue = 0;           // PWM output

void setup() {
  Serial.begin(9600);

  // Motor setup
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);
  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);

  // Encoder setup
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), readEncoder, RISING);

  Serial.println("Ready. Send target speed in m/s (e.g. 0.3).");
  Serial.println("Send 'c' to calculate encoder CPR manually.");
}

void loop() {
  unsigned long currentMillis = millis();

  // === Every 100ms, calculate speed and adjust PWM ===
  if (currentMillis - lastMillis >= 100) {
    long deltaTicks = encoderTicks - lastEncoderTicks;
    lastEncoderTicks = encoderTicks;

    float revs = (float)deltaTicks / encoderCPR;
    float distance = revs * wheelCircumference;
    currentSpeed = distance / 0.1;  // in m/s

    // === P-Control ===
    float error = targetSpeed - currentSpeed;
    float Kp = 300; // Tune as needed
    pwmValue += Kp * error;
    pwmValue = constrain(pwmValue, 0, 255);
    driveMotor(pwmValue);

    Serial.print("Target: ");
    Serial.print(targetSpeed);
    Serial.print(" m/s | Current: ");
    Serial.print(currentSpeed);
    Serial.print(" m/s | PWM: ");
    Serial.println(pwmValue);

    lastMillis = currentMillis;
  }

  // === Handle serial input ===
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input == "c") {
      calculateEncoderCPR();
    } else {
      float spd = input.toFloat();
      if (spd >= 0.0) {
        targetSpeed = spd;
        Serial.print("Set target speed to: ");
        Serial.print(targetSpeed);
        Serial.println(" m/s");
      }
    }
  }
  Serial.print("Ticks: ");
Serial.println(encoderTicks);
}

// === Encoder interrupt handler ===
void readEncoder() {
  if (digitalRead(ENCODER_B) == LOW)
    encoderTicks++;
  else
    encoderTicks--;
}

// === Motor driver function ===
void driveMotor(int pwm) {
  analogWrite(RPWM, pwm);
  analogWrite(LPWM, 0); // Forward only
}

// === Measure encoder CPR by rotating one full wheel turn ===
void calculateEncoderCPR() {
  encoderTicks = 0;
  Serial.println("Rotate wheel 1 full turn by hand...");
  delay(5000);
  noInterrupts();
  int countedTicks = encoderTicks;
  interrupts();
  Serial.print("Measured CPR: ");
  Serial.println(countedTicks);
  Serial.println("Update 'encoderCPR' in code to this value.");
}
