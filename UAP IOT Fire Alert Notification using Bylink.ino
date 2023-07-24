#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL6i095OVyr"
#define BLYNK_TEMPLATE_NAME "UAP"
#define BLYNK_AUTH_TOKEN "x9iG5HugQBfc964NNSpriAVB3HCD6R0o"

char ssid[] = "POCO M4 Pro";
char pass[] = "11111111";
char auth[] = BLYNK_AUTH_TOKEN;

int flameSensorPin = 4;
int buzzerPin = 5;
int ledbiru = 21;
int ledmerah = 22;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(flameSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledbiru, OUTPUT);
  pinMode(ledmerah, OUTPUT);
  
  Blynk.virtualWrite(V0, "Sensor Status: Offline");
}

void loop() {
  Blynk.run();
  int flameState = digitalRead(flameSensorPin);
  Serial.println(flameState);

  if (flameState  == 0) {
    Blynk.virtualWrite(V0, "Sensor Status: Flame detected");
    // Blynk.notify("Flame detected! Take immediate action.");
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledmerah, HIGH);
    digitalWrite(ledbiru, LOW);
    Blynk.logEvent("sensor_api", "Api Terdeteksi");
  } else {
    Blynk.virtualWrite(V0, "Sensor Status: No flame");
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledbiru, HIGH);
    digitalWrite(ledmerah, LOW);
  }

  delay(100); // Delay for stability
}
