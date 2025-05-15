#include <SoftwareSerial.h>

// Configuración de pines para el módulo Bluetooth
SoftwareSerial bluetooth(11, 13);  // RX, TX

// Pin del LED interno
const int ledPin = 13;

// Definición de pines para el motor
#define EN_A 6
#define IN_1 4
#define IN_2 5
// Definición de pines para el segundo motor
#define EN_B 10
#define IN_3 9
#define IN_4 8

// Función para controlar el motor
void setMotor(int speed, int in1, int in2, int ena) {
    if (speed > 0) {
        // Movimiento hacia adelante
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    } else if (speed < 0) {
        // Movimiento hacia atrás
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        speed = -speed;  // Convertir a positivo para PWM
    } else {
        // Detener el motor
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    }

    // Aplicar velocidad con PWM
    analogWrite(ena, constrain(map(speed, 0, 100, 0, 255), 0, 255));
}

void setMotors(int speed1, int speed2) {
    setMotor(speed1, IN_1, IN_2, EN_A);
    setMotor(speed2, IN_3, IN_4, EN_B);
}

void setup() {
    // Inicializar comunicación serial
    Serial.begin(9600);
    bluetooth.begin(9600);

    // Configurar el pin del LED como salida
    pinMode(ledPin, OUTPUT);
    // Configurar el pin de habilitación del motor como salida
    pinMode(EN_A, OUTPUT);
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(EN_B, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);
}

void loop() {
    if (!bluetooth.available()) return;  // Si no hay datos, salir de la función
    char command = bluetooth.read();     // Leer el comando recibido
    switch (command) {
        case 'F':  // Avanzar
            setMotors(100, 100);
            break;
        case 'B':  // Retroceder
            setMotors(-100, -100);
            break;
        case 'S':  // Detener
            setMotors(0, 0);
            break;
        case 'L':  // Girar a la izquierda
            setMotors(-100, 100);
            break;
        case 'R':  // Girar a la derecha
            setMotors(100, -100);
            break;
        case 'G':  // Avanzar hacia la izquierda
            setMotors(50, 100);
            break;
        case 'I':  // Avanzar hacia la derecha
            setMotors(100, 50);
            break;
        case 'H':  // Retroceder hacia la izquierda
            setMotors(-50, -100);
            break;
        case 'J':  // Backward Right
            setMotors(-100, -50);
            break;
        default:
            break;
    }
}