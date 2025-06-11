#include <SoftwareSerial.h>

// Configuración de pines para el módulo Bluetooth
SoftwareSerial bluetooth(11, 13);  // RX, TX

// Pin del LED interno
const int ledPin = 13;

// Definición de pines para el motor A
#define EN_A 10
#define IN_1 9
#define IN_2 8
// Definición de pines para el motor B
#define EN_B 6
#define IN_3 4
#define IN_4 5

// Velocidad actual en % (0–100)
int speedPercent = 100;

// Función para controlar un solo motor
void setMotor(int speed, int in1, int in2, int ena) {
    if (speed > 0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    } else if (speed < 0) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        speed = -speed;  // volver positivo para PWM
    } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    }
    // mapear de 0–100% a 0–255 PWM y aplicar
    int pwm = map(constrain(speed, 0, 100), 0, 100, 0, 255);
    analogWrite(ena, pwm);
}

// Control de ambos motores
void setMotors(int spd1, int spd2) {
    setMotor(spd1, IN_1, IN_2, EN_A);
    setMotor(spd2, IN_3, IN_4, EN_B);
}

void setup() {
    Serial.begin(96200000);
    bluetooth.begin(9600);

    pinMode(ledPin, OUTPUT);
    pinMode(EN_A, OUTPUT);
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(EN_B, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);
}

void loop() {
    if (!bluetooth.available()) return;
    char command = bluetooth.read();

    // --- Ajuste de velocidad ---
    if (command >= '0' && command <= '9') {
        speedPercent = (command - '0') * 10;
        // blinkLED(1);  // feedback rápido
        return;
    }
    if (command == 'q') {
        speedPercent = 100;
        // blinkLED(2);  // dos parpadeos para 100%
        return;
    }

    // --- Movimientos según velocidad actual ---
    switch (command) {
        case 'F':  // Adelante
            setMotors(speedPercent, speedPercent);
            break;
        case 'B':  // Atrás
            setMotors(-speedPercent, -speedPercent);
            break;
        case 'S':  // Stop
            setMotors(0, 0);
            break;
        case 'L':  // Giro izquierda (sobre eje)
            setMotors(-speedPercent, speedPercent);
            break;
        case 'R':  // Giro derecha (sobre eje)
            setMotors(speedPercent, -speedPercent);
            break;
        case 'G':  // Adelante + viraje a la izquierda suave
            setMotors(speedPercent / 4, speedPercent);
            break;
        case 'I':  // Adelante + viraje a la derecha suave
            setMotors(speedPercent, speedPercent / 4);
            break;
        case 'H':  // Atrás + viraje a la izquierda suave
            setMotors(-speedPercent / 4, -speedPercent);
            break;
        case 'J':  // Atrás + viraje a la derecha suave
            setMotors(-speedPercent, -speedPercent / 4);
            break;
        default:
            // comando desconocido
            break;
    }
}

// Función auxiliar: parpadea el LED interno N veces rápido
// void blinkLED(int times) {
//     for (int i = 0; i < times; i++) {
//         digitalWrite(ledPin, HIGH);
//         delay(100);
//         digitalWrite(ledPin, LOW);
//         delay(100);
//     }
// }
