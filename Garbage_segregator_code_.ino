#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#define IR_SENSOR_PIN D7
#define RAIN_SENSOR_PIN A0
#define SERVO_PIN D1
#define WET_SIDE_IR_PIN D3
#define trigPin D5
#define echoPin D6

const char* ssid = "Harshit";     // Enter your WiFi SSID
const char* password = "123456789"; // Enter your WiFi password

const int minDistance = 1;
const int maxDistance = 3;

Servo servo;
ESP8266WebServer server(80);

bool wetBinFilled = false;
bool dryBinFilled = false;

void setup() {
  Serial.begin(9600);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(RAIN_SENSOR_PIN, INPUT);
  pinMode(WET_SIDE_IR_PIN, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(SERVO_PIN);
  servo.write(90);
  delay(500);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  
  // Start the web server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  // Read IR sensor to detect garbage on the plate
  int irSensorValue = digitalRead(IR_SENSOR_PIN);

  if (irSensorValue == LOW) {
    // Garbage detected by IR sensor
    // Read rain sensor to determine dry or wet
    Serial.println("Object detected by IR sensor.");
    int rainSensorValue = analogRead(RAIN_SENSOR_PIN);
    if (rainSensorValue > 500) {
      // Rain sensor detects wet
      Serial.println("It's wet. Moving servo to 90 degrees.");

        for (int angle = 90; angle <= 180; angle++) {
          servo.write(angle);
          delay(15);
        }
        delay(2000);

        for (int angle = 180; angle >= 90; angle--) {
          servo.write(angle);
          delay(15);
        }
        delay(2000);
    } else {
      // Rain sensor detects dry
      Serial.println("It's dry. Moving servo to 90 degrees.");
      for (int angle = 90; angle >= 0; angle--) {
        servo.write(angle);
        delay(15);
      }
      delay(2000);
      for (int angle = 0; angle <= 90; angle++) {
        servo.write(angle);
        delay(15);
      }
      delay(2000);
    }
  }
  else{
    // Ultrasonic sensor reading
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;  // Convert time to distance in cm

    // IR sensor reading
    int irValue = digitalRead(WET_SIDE_IR_PIN);

    // Check if object is detected by IR sensor
    if (irValue == LOW) {
      //showing wet dustbin is fill
      Serial.println("wet side dustbin is filled..");
      sendNotification("Wet side dustbin is filled");
      // Add your action here, like triggering an alarm or sending a notification
    }

    // Check if object is detected by ultrasonic sensor within desired range
    if (distance <= maxDistance && distance >= minDistance) {
      //showing dry side dustbin is fill
      Serial.println("dry side dustbin is filled..");
      sendNotification("Dry side dustbin is filled");
      // Add your action here, like triggering an alarm or sending a notification
    }
  }

  delay(1000);  // Delay for stability
}



void handleRoot() {
  String webpage = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"></head>";
  webpage += "<body><h1>Garbage Segregator Control</h1><p>Notifications:</p><div id=\"notifications\"></div>";
  webpage += "<script>function addNotification(message) {var notificationsDiv = document.getElementById('notifications');var notification = document.createElement('p');notification.textContent = message;notificationsDiv.appendChild(notification);}</script>";
  webpage += "</body></html>";
  server.send(200, "text/html", webpage);
}

void sendNotification(String message) {
  server.send(200, "text/plain", message);
  server.client().stop(); // Stop the connection after sending the notification
}

void moveServo(int startAngle, int endAngle, int delayTime) {
  int step = (startAngle < endAngle) ? 1 : -1;
  for (int angle = startAngle; angle != endAngle + step; angle += step) {
    servo.write(angle);
    delay(15);
  }
  delay(delayTime);
}