//Jersson Oswaldo Sierra & Juan david Sotelo Rozo
// Definición de pines
const int velocidadPin = 10;     // PWM para velocidad
const int motorPin1 = 9;        // Dirección 1
const int motorPin2 = 8;        // Dirección 2
const int botonPin = 2;         // Botón para invertir giro

const int encoderPinA = 2;      // Señal A del encoder
const int encoderPinB = 3;      // Señal B del encoder

// Variables globales
bool sentidoHorario = true;
volatile int contadorPulsos = 0;
int pulsosPorVuelta = 20;
unsigned long tiempoAnterior = 0;

int velocidad = 0;
bool motorActivo = false;
String comandoSerial = "";

void setup() {
    pinMode(velocidadPin, OUTPUT);
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(botonPin, INPUT_PULLUP);
    pinMode(encoderPinA, INPUT_PULLUP);
    pinMode(encoderPinB, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(botonPin), cambiarDireccion, FALLING);
    attachInterrupt(digitalPinToInterrupt(encoderPinA), encoderISR, RISING);

    Serial.begin(9600);
    Serial.println("Sistema iniciado, 'a' para arrancar, 'b' para detener.");
}

void loop() {
    // Leer comandos del puerto serie
    while (Serial.available()) {
        char c = Serial.read();
        if (c == '\n' || c == '\r') {
            procesarComando(comandoSerial);
            comandoSerial = "";
        } else {
            comandoSerial += c;
        }
    }

    // Control del sentido de giro
    if (motorActivo) {
        if (sentidoHorario) {
            digitalWrite(motorPin1, HIGH);
            digitalWrite(motorPin2, LOW);
        } else {
            digitalWrite(motorPin1, LOW);
            digitalWrite(motorPin2, HIGH);
        }
        analogWrite(velocidadPin, velocidad);
    } else {
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
        analogWrite(velocidadPin, 0);
    }

    // Cálculo de RPM cada segundo
    unsigned long tiempoActual = millis();
    if (tiempoActual - tiempoAnterior >= 1000) {
        noInterrupts();
        int pulsos = contadorPulsos;
        contadorPulsos = 0;
        interrupts();

        float rps = (float)pulsos / (pulsosPorVuelta * 48);
        float rpm = rps * 60.0;

        Serial.println(pulsos + 10000);

        tiempoAnterior = tiempoActual;
    }
}

// Procesa comandos recibidos por el puerto serie
void procesarComando(String comando) {
    if (comando.startsWith("c")) {
        int valor = comando.substring(1).toInt();
        velocidad = constrain(valor, 0, 255);
    } else if (comando == "a") {
        motorActivo = true;
    } else if (comando == "b") {
        motorActivo = false;
    }
}

// Cambiar sentido de giro con botón
void cambiarDireccion() {
    sentidoHorario = !sentidoHorario;
    delay(200); 
}

// Contador de pulsos del encoder
void encoderISR() {
    contadorPulsos++;
}
