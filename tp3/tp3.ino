#include <SoftwareSerial.h>

// Hacer interprete de comandos por bluetooth:
// - F ejecuta setMotor(100)
// - R ejecuta setMotor(-100)
// - S ejecuta setMotor(0)
// - W enciende el led interno (pin 13)
// - w apaga el led interno (pin 13)

// Configuración de pines para el módulo Bluetooth
SoftwareSerial bluetooth(10, 11); // RX, TX

// Pin del LED interno
const int ledPin = 13;
// Definición de pines para el motor
#define EN_A 6 
#define IN_1 4
#define IN_2 5

// Función para controlar el motor
void setMotor(int speed) {
  if (speed > 0) {
    // Movimiento hacia adelante
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
  } else if (speed < 0) {
    // Movimiento hacia atrás
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    speed = -speed; // Convertir a positivo para PWM
  } else {
    // Detener el motor
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
  }

  // Aplicar velocidad con PWM
  analogWrite(EN_A, constrain(speed, 0, 255));

  Serial.print("Motor speed set to: ");
  Serial.println(speed);
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

    Serial.println("Esperando comandos por Bluetooth...");
}

void loop() {
    if (!bluetooth.available()) return; // Si no hay datos, salir de la función
    char command = bluetooth.read(); // Leer el comando recibido
    switch (command) {
        case 'F': // Avanzar
            setMotor(100);
            break;
        case 'R': // Retroceder
            setMotor(-100);
            break;
        case 'S': // Detener
            setMotor(0);
            break;
        case 'W': // Encender LED
            digitalWrite(ledPin, HIGH);
            Serial.println("LED encendido");
            break;
        case 'w': // Apagar LED
            digitalWrite(ledPin, LOW);
            Serial.println("LED apagado");
            break;
        default:
            Serial.println("Comando no reconocido");
            break;
    }
}