// Εισαγωγή στα Ενσωματωμένα Συστήματα - Φαρούπος Χρυσόστομος
// Κουμπί + LED: κάθε πάτημα = ακριβώς μία αλλαγή (toggle)

const int buttonPin = 2;              // Κουμπί στο D2 (INPUT_PULLUP, άλλο άκρο στο GND)
const int ledPin = 8;                 // LED (+220Ω) στο D8 (κανονικό digital pin, χωρίς ~)
const unsigned long debounceDelay = 40; // Χρόνος προστασίας αναπήδησης σε ms

bool ledState = false;                // Τρέχουσα κατάσταση LED
int lastReading = HIGH;               // Προηγούμενη "ωμή" ανάγνωση του κουμπιού
int stableState = HIGH;               // Σταθερή (φιλτραρισμένη) κατάσταση κουμπιού
unsigned long lastChangeTime = 0;     // Πότε άλλαξε τελευταία φορά η ωμή ανάγνωση

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);   // Ελεύθερο = HIGH, πατημένο = LOW
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);          // Αρχικά σβηστό
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Αν η ανάγνωση άλλαξε (πάτημα ή θόρυβος), ξαναρχίζει το χρονόμετρο
  if (reading != lastReading) {
    lastChangeTime = millis();
  }
  lastReading = reading;

  // Αν η τιμή μένει ίδια πάνω από 40ms, θεωρείται σταθερή
  if ((millis() - lastChangeTime) > debounceDelay && reading != stableState) {
    stableState = reading;

    // Ενεργούμε ΜΟΝΟ τη στιγμή του πατήματος (HIGH -> LOW), όχι όσο κρατιέται
    if (stableState == LOW) {
      ledState = !ledState;                 // toggle
      digitalWrite(ledPin, ledState);
      if (ledState) {
        Serial.println("ΠΑΤΑΞ → LED ΑΝΑΜΜΕΝΟ");
      } else {
        Serial.println("ΠΑΤΑΞ → LED ΣΒΗΣΤΟ");
      }
    }
  }
}
