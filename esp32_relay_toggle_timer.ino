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

  Serial.begin(9600);

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
}

void loop() {

  int currentButtonState = digitalRead(buttonPin);

  // 🔘 Detect button press (edge)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    systemOn = !systemOn; // toggle
    Serial.println(systemOn ? "System ON" : "System OFF");

    if (systemOn) {
      previousMillis = millis(); // start timer
    }
  }

  lastButtonState = currentButtonState;

  // 🔁 SYSTEM RUN
  if (systemOn) {

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 5000) { // test 5 sec
      previousMillis = currentMillis;
      state = !state;
    }

    if (state == 0) {
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, HIGH);
      Serial.println("Relay1 ON");
    } else {
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, LOW);
      Serial.println("Relay2 ON");
    }

  } 
  else {
    // 🔴 SYSTEM OFF
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
  }

  delay(200);
}