// ΧΑΛΑΣΜΕΝΗ ΕΚΔΟΣΗ - Φαρούπος Χρυσόστομος
// LED μετακινημένο σε PWM pin (D9) και analogWrite αντί για toggle

const int buttonPin = 2;              // Κουμπί στο D2 (INPUT_PULLUP, άλλο άκρο στο GND)
const int ledPin = 9;                 // LED στο D9 (PWM pin ~)
const unsigned long debounceDelay = 40; // Προστασία αναπήδησης σε ms

int lastReading = HIGH;               // Προηγούμενη "ωμή" ανάγνωση του κουμπιού
int stableState = HIGH;               // Σταθερή (φιλτραρισμένη) κατάσταση κουμπιού
unsigned long lastChangeTime = 0;     // Πότε άλλαξε τελευταία φορά η ωμή ανάγνωση

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 200);           // ΒΛΑΒΗ: το LED ανάβει με σταθερή φωτεινότητα 200/255 ~78% από την αρχή	
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastReading) {
    lastChangeTime = millis();
  }
  lastReading = reading;

  if ((millis() - lastChangeTime) > debounceDelay && reading != stableState) {
    stableState = reading;

    if (stableState == LOW) {
      analogWrite(ledPin, 200);       // ΒΛΑΒΗ: αντί για toggle, σταθερή φωτεινότητα. Το LED δεν αλλάζει ποτέ
      Serial.println("ΠΑΤΑΣ → LED ΑΝΑΜΜΕΝΟ"); // Το LED μένει αναμμένο ό,τι κι αν πατήσεις
    }
  }
}
