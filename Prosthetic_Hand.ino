#define ACTUATOR_DRIVER 7                   // Actuator driver pin
#define ACTUATORS_IN1 6                     // Input 1 for the actuator driver
#define ACTUATORS_IN2 5                     // Input 2 for the actuator driver 
#define EMG_PIN A0                          // EMG sensor ping
#define EMG_TO_ACTUATOR_SPEED 255/1023      // Convert EMG to actuator speed
#define EMG_THRESHOLD 20.46                 // EMG Threshold to close hand

double EMG_Curr = 0.0;                      // Current EMG Reading
double EMG_Prev = 0.0;                      // Previous EMG reading
double actuator_speed = 0.0;                // absolute val of the difference between curr and prev EMG vals

void setup() {
  // Set pins
  pinMode(ACTUATOR_DRIVER, OUTPUT);
  pinMode(ACTUATORS_IN1, OUTPUT);
  pinMode(ACTUATORS_IN2, OUTPUT);

  Serial.begin(9600);

  // Initialize actuator speed to max
  digitalWrite(ACTUATOR_DRIVER, 255);

  // Get initial EMG value
  delay(1000);
  EMG_Curr = analogRead(EMG_PIN);
}

void loop() {
  // EMG Range between 0 - 1023
  EMG_Prev = EMG_Curr;
  EMG_Curr = analogRead(EMG_PIN);

  // Actuator speed range = 0 to 255
  actuator_speed = abs(EMG_Prev - EMG_Curr) * EMG_TO_ACTUATOR_SPEED;

  Serial.println("EMG Value: " + String(EMG_Curr) + " Actuator Speed: " + String(actuator_speed));

  // Close hand
  if(EMG_Curr >= EMG_THRESHOLD){
    digitalWrite(ACTUATOR_DRIVER, actuator_speed);

    analogWrite(ACTUATORS_IN1, HIGH);
    analogWrite(ACTUATORS_IN2, LOW);
  }

  // Open
  else {
    digitalWrite(ACTUATOR_DRIVER, actuator_speed);

    analogWrite(ACTUATORS_IN1, LOW);
    analogWrite(ACTUATORS_IN2, HIGH);
  }

  // Wait 20 ms before next reading
  delay(20);
}
