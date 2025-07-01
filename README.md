# 🔧 Control de Motor DC con Encoder y Cambio de Giro a traves de LABVIEW

Proyecto desarrollado por **Jersson Oswaldo Sierra** y **Juan David Sotelo Rozo**  
Este sistema permite controlar un motor DC mediante comandos seriales, medir su velocidad usando un encoder, y cambiar el sentido de giro con un botón físico.

## 📌 Descripción

El sistema está diseñado para:

- Controlar la velocidad de un motor DC usando señal PWM.
- Medir la velocidad del motor en revoluciones por minuto (RPM) con un encoder.
- Cambiar el sentido de giro del motor usando un botón físico.
- Activar o detener el motor mediante comandos enviados por el monitor serial.

## 🛠️ Componentes

- Arduino UNO (u otro compatible)
- Motor DC
- Encoder rotativo (20 pulsos por vuelta * 48 reducción)
- Driver (L298N, puente H, etc.)
- Fuente de alimentación externa para el motor
- Resistencias Pull-up (si no se usan internas)
- Botón
- Cables Dupont

## ⚙️ Conexiones

| Componente      | Pin Arduino     |
|----------------|-----------------|
| Motor IN1       | 9               |
| Motor IN2       | 8               |
| PWM velocidad   | 10 (PWM)        |
| Botón           | 2 (interrupción)|
| Encoder A       | 2 (interrupción)|
| Encoder B       | 3               |

## 📥 Comandos Seriales

- `a` → Arranca el motor
- `b` → Detiene el motor
- `cXXX` → Cambia la velocidad del motor (valor de 0 a 255). Ejemplo: `c150`

## 💻 Cómo usar

1. Sube el código al Arduino usando el IDE.
2. Abre el Monitor Serial a 9600 baudios.
3. Usa los comandos para interactuar:
   - Escribe `a` para arrancar el motor.
   - Escribe `b` para detenerlo.
   - Escribe `c200` para establecer una velocidad de 200.

Cada segundo, el sistema imprime por el monitor serial la cantidad de pulsos detectados por el encoder, sumado a 10000 (para facilitar la lectura o procesamiento externo).

## 📈 Ejemplo de Salida

```text
Sistema iniciado, 'a' para arrancar, 'b' para detener.
10235
10300
10412
