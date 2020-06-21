//void setup() {
//  Serial.begin(9600);               // initialize serial communication
//}
//
//void loop() {
//  long randomNumber = random(10500);
//  Serial.println(randomNumber);
//  delay(200);                       // wait 100 ms
//}

// ***********************

char val;
int LED_PIN = 13;
int BLUE_LED = 3;
int RED_LED = 2;
boolean ledState = LOW;

// CHANGE THIS
int datapointsPerSecond = 10;

int dataRate_in_milliseconds = 1000 / datapointsPerSecond;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  Serial.begin(9600);
  establishContact();       // send a byte to establish contact until receiver responds
}

void loop() {
  if (Serial.available() > 0) {
    val = Serial.read();

    if (val == '1') {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    } else if (val == 'R') {
      digitalWrite(RED_LED, HIGH);
    } else if (val == 'N') {
      digitalWrite(RED_LED, LOW);
    } else if (val == 'S') {
      digitalWrite(BLUE_LED, HIGH);
      delay(100);
      digitalWrite(BLUE_LED, LOW);
    }
  } else {
    long randomNumber = random(10500);
    Serial.println(randomNumber);
    delay(dataRate_in_milliseconds);
  }

}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("A");
    delay(300);
  }
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RED_LED, HIGH);
  delay(100);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  delay(100);
}
