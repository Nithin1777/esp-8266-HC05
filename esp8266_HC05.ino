#define ledPin 2  // Built-in LED on ESP8266

// Using hardware UART for HC-05 Bluetooth module
// HC-05 TX connects to ESP8266 RX (GPIO3)
// HC-05 RX connects to ESP8266 TX (GPIO1)

// Define motor control pins for ESP8266
// Left motor (simplified with parallel connection)
// D1:GPIO5	
// D2:GPIO4					
// D3:GPIO0				
// D4:GPIO2				
// D5:GPIO14
//https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/(for more info)
const int leftMotorPin1 = 5;  // IN1 on L298N
const int leftMotorPin2 = 4;  // IN2 on L298N
const int leftMotorPWM = 0;   // ENA on L298N

// Right motor (simplified with parallel connection)
const int rightMotorPin1 = 2; // IN3 on L298N
const int rightMotorPin2 = 14; // IN4 on L298N
const int rightMotorPWM = 12;  // ENB on L298N

int valSpeed = 200;     // Default motor speed (0-1023 for ESP8266)
int minTurnSpeed = 100; // Minimum speed for effective turning

bool isConnected = false;
unsigned long lastBlinkTime = 0;
bool ledState = false;

void setup() {
    Serial.begin(9600); // This will communicate with HC-05
    Serial.println("ESP8266 CarBot with HC-05 started!");
    
    // Set up motor control pins
    pinMode(leftMotorPin1, OUTPUT);
    pinMode(leftMotorPin2, OUTPUT);
    pinMode(rightMotorPin1, OUTPUT);
    pinMode(rightMotorPin2, OUTPUT);
    pinMode(leftMotorPWM, OUTPUT);
    pinMode(rightMotorPWM, OUTPUT);
    
    // Initialize LED
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    
    // Stop all motors initially
    stopMotors();
    
    Serial.println("Ready to receive commands...");
}

void loop() { 
    char command = 0;

    // Blink LED while not connected
    if (!isConnected) {
        unsigned long currentMillis = millis();
        if (currentMillis - lastBlinkTime >= 300) { // Blink every 300ms
            lastBlinkTime = currentMillis;
            ledState = !ledState;
            digitalWrite(ledPin, ledState);
        }
    }

    // Check HC-05 Bluetooth via hardware UART
    if (Serial.available() > 0) {
        command = Serial.read();
        
        if (!isConnected) {
            isConnected = true;
            digitalWrite(ledPin, HIGH);  // Solid LED once connected
            Serial.println("Connected to ESP8266 CarBot!");
        }
    }

    // Process command
    if (command != 0) {
        processCommand(command);
    }
}

void processCommand(char command) {
    switch(command) {
        case 'F': {  // Move forward
            leftMotorForward();
            rightMotorForward();
            setMotorSpeeds(valSpeed, valSpeed);
            Serial.println("Moving Forward");
            break;
        }
        case 'B': {  // Move backward
            leftMotorBackward();
            rightMotorBackward();
            setMotorSpeeds(valSpeed, valSpeed);
            Serial.println("Moving Backward");
            break;
        }
        case 'R': {   // Turn right
            // Use higher speed for turning if current speed is too low
            int rightTurnSpeed = max(valSpeed, minTurnSpeed);
            leftMotorForward();
            rightMotorBackward();
            setMotorSpeeds(rightTurnSpeed, rightTurnSpeed);
            Serial.println("Turning Right");
            break;
        }
        case 'L': {   // Turn left
            // Use higher speed for turning if current speed is too low
            int leftTurnSpeed = max(valSpeed, minTurnSpeed);
            leftMotorBackward();
            rightMotorForward();
            setMotorSpeeds(leftTurnSpeed, leftTurnSpeed);
            Serial.println("Turning Left");
            break;
        }
        case 'G': {   // Forward left (curve)
            leftMotorForward();
            rightMotorForward();
            setMotorSpeeds(valSpeed/2, valSpeed);
            Serial.println("Curving Forward Left");
            break;
        }
        case 'H': {   // Forward right (curve)
            leftMotorForward();
            rightMotorForward();
            setMotorSpeeds(valSpeed, valSpeed/2);
            Serial.println("Curving Forward Right");
            break;
        }
        case 'S': {   // Stop all motors
            stopMotors();
            Serial.println("Motors Stopped");
            break;
        }
        
        // LED control commands (from your HC-05 example)
        case 'O': {   // LED ON
            digitalWrite(ledPin, HIGH);
            Serial.println("LED is now ON!");
            break;
        }
        case 'X': {   // LED OFF
            digitalWrite(ledPin, LOW);
            Serial.println("LED is now OFF!");
            break;
        }

        // Set motor speed using single characters (0-9)
        case '0': valSpeed = 0; Serial.println("Speed: 0%"); break;
        case '1': valSpeed = 100; Serial.println("Speed: 10%"); break;
        case '2': valSpeed = 200; Serial.println("Speed: 20%"); break;
        case '3': valSpeed = 300; Serial.println("Speed: 30%"); break;
        case '4': valSpeed = 400; Serial.println("Speed: 40%"); break;
        case '5': valSpeed = 500; Serial.println("Speed: 50%"); break;
        case '6': valSpeed = 600; Serial.println("Speed: 60%"); break;
        case '7': valSpeed = 700; Serial.println("Speed: 70%"); break;
        case '8': valSpeed = 850; Serial.println("Speed: 80%"); break;
        case '9': valSpeed = 1023; Serial.println("Speed: 100%"); break;
        
        default: {
            Serial.println("Unknown command. Use F/B/L/R/G/H/S for movement, 0-9 for speed, O/X for LED");
            break;
        }
    }
}

// Function to set individual motor speeds
void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    analogWrite(leftMotorPWM, leftSpeed);
    analogWrite(rightMotorPWM, rightSpeed);
}

// Simplified setSpeed function for forward/backward movement
void setSpeed(int speed) {
    valSpeed = speed;
    setMotorSpeeds(speed, speed);
}

void leftMotorForward() {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
}

void leftMotorBackward() {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
}

void rightMotorForward() {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
}

void rightMotorBackward() {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
}

void stopMotors() {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
    setMotorSpeeds(0, 0);
}