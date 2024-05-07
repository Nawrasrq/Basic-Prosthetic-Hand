#define ACTUATOR_DRIVER 7                   // Actuator driver pin
#define ACTUATORS_IN1 6                     // Input 1 for the actuator driver
#define ACTUATORS_IN2 5                     // Input 2 for the actuator driver 
#define EMG_PIN A0                          // EMG sensor ping
#define EMG_THRESHOLD 20.46                 // Threshold to close hand before converting to milli volts
#define EMG_TO_MV 5/1023*1000               // Convert EMG to milli volts

double EMG_Curr = 0.0;                      // Current EMG Reading
double EMG_Prev = 0.0;                      // Previous EMG reading

void setup() {
  // Set pins
  pinMode(ACTUATOR_DRIVER, OUTPUT);
  pinMode(ACTUATORS_IN1, OUTPUT);
  pinMode(ACTUATORS_IN2, OUTPUT);

  Serial.begin(9600);

  // Initialize actuator speed to max
  digitalWrite(ACTUATOR_DRIVER, HIGH);

  // Get initial EMG value
  delay(1000);
  EMG_Curr = analogRead(EMG_PIN);
}

void loop() {
  // EMG range = 0 to 1023
  EMG_Prev = EMG_Curr;
  EMG_Curr = analogRead(EMG_PIN);

  Serial.println("EMG Value: " + String(EMG_Curr * EMG_TO_MV) + "mV");

  // Close hand
  if(EMG_Curr >= EMG_THRESHOLD){
    analogWrite(ACTUATORS_IN1, HIGH);
    analogWrite(ACTUATORS_IN2, LOW);
  }

  // Open
  else {
    analogWrite(ACTUATORS_IN1, LOW);
    analogWrite(ACTUATORS_IN2, HIGH);
  }

  // Wait 20 ms before next reading
  delay(20);
}