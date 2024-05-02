#include <Servo.h>

#define IR_SENSOR_PIN D7
#define RAIN_SENSOR_PIN A0
#define SERVO_PIN D1

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(IR_SENSOR_PIN, INPUT);
  servo.attach(SERVO_PIN);
  servo.write(90); // Move servo to initial position (90 degrees)
  delay(500); // Add delay to allow servo to move
}

void loop() {
  // Read IR sensor
  
  int irSensorValue = digitalRead(IR_SENSOR_PIN);

  if (irSensorValue == LOW) {
    // Object detected
    Serial.println("Object detected by IR sensor.");

    // Read rain sensor
    int rainSensorValue = analogRead(RAIN_SENSOR_PIN);

    if (rainSensorValue < 500) {
      // Rain sensor detects dry
      Serial.println("It's wet. Moving servo to 90 degrees.");
      for(int angle = 90; angle <= 180; angle++)  
        {                                  
          servo.write(angle);               
          delay(15);                   
        } 
      delay(2000);
  
      for(int angle = 180; angle >= 90; angle--)    
        {                                
          servo.write(angle);           
          delay(15);       
        } 
      delay(2000);
    } 
    else {
      Serial.println("It's dry. Moving servo to 90 degrees.");
      for(int angle = 90; angle >= 0; angle--)    
        {                                
          servo.write(angle);           
          delay(15);       
        } 
  delay(2000);
      for(int angle = 0; angle <= 90; angle++)  
      {                                  
        servo.write(angle);               
        delay(15);                   
      } 
  delay(2000);
    }
    // Return servo to initial position (90 degrees)
    
  } else {
    // No object detected
    Serial.println("No object detected by IR sensor.");
    // Add any necessary actions here if no object is detected
  }

  delay(1000); // Delay for stability
}


