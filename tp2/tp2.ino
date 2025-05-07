#define EN_A 6
#define IN_1 4
#define IN_2 5

void forward() {
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
}

void backward() {
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
}

void setMotor(int speed) {
    speed > 0 ? forward() : backward();
    analogWrite(EN_A, abs(speed));
}

void setup() {
    pinMode(EN_A, OUTPUT);
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    Serial.begin(2000000);
}

void loop() {
    if (!Serial.available()) return;
    String command = Serial.read();  // Es mala práctica readString() pq lee
                                     // hasta el final de la línea (muy pesado)
    long speed = (command.toInt() * 0xFF) / 100;
    setMotor(speed);
    Serial.print("Set speed ");
    Serial.println(speed);
}
