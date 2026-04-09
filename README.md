# ESP32-Relay-Toggle-Timer
ESP32 based relay control using push button toggle and timer automation
This project demonstrates controlling a 2-channel relay module using ESP32 with a push button toggle and timer-based automation.

---

## Features

- Toggle system using push button  
- Timer-based relay switching  
- Alternating relay logic  
- Real-time serial monitoring  
- Beginner to intermediate embedded project  

---

## Components Used

- ESP32
- 2-Channel Relay Module (5V)
- Push Button
- Jumper Wires
- Breadboard (optional)

---

## Connections

### Relay Module → ESP32

| Relay Pin | ESP32 Pin |
|----------|----------|
| VCC      | VIN (5V) |
| GND      | GND      |
| IN1      | GPIO 26  |
| IN2      | GPIO 27  |

### Push Button → ESP32

| Button Pin | ESP32 Pin |
|-----------|----------|
| One side  | GPIO 25  |
| Other side| GND      |

---

## Working

### Button Logic
- First press → System ON  
- Second press → System OFF  

### Relay Logic (When ON)
- Relay 1 ON, Relay 2 OFF  
- After fixed time → Relay 1 OFF, Relay 2 ON  
- Loop continues  

### System OFF
- Both relays OFF  

---

## Code

```cpp
int relay1 = 26;
int relay2 = 27;
int buttonPin = 25;

bool systemOn = false;
bool lastButtonState = HIGH;

unsigned long previousMillis = 0;
int state = 0;

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(115200);

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
}

void loop() {

  int currentButtonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    systemOn = !systemOn;

    if (systemOn) {
      previousMillis = millis();
    }
  }

  lastButtonState = currentButtonState;

  if (systemOn) {

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 5000) {
      previousMillis = currentMillis;
      state = !state;
    }

    if (state == 0) {
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, HIGH);
    } else {
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, LOW);
    }

  } else {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
  }

  delay(200);
}
