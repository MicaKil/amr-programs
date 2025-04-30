#define LED_PIN 9
#define pinEcho 11
#define pinTrig 12
#define SOUND_SPEED 0.034

long duration;
float distance;
int i = 0;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(pinTrig, OUTPUT);
    pinMode(pinEcho, INPUT);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(pinTrig, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig, LOW);
    duration = pulseIn(pinEcho, HIGH);
    distance = (duration*SOUND_SPEED)/2;
    Serial.print("Distance: ");
    Serial.println(distance);
    if (distance < 255) {
        analogWrite(LED_PIN, 255-distance);
    } else {
        analogWrite(LED_PIN, 0);
    };
    delay(100);
}