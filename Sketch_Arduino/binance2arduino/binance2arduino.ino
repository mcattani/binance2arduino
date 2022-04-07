/*
   Este sketch recibe la información enviada por la aplicación Binance2Arduino hecha en Gambas3
   y la despliega en un display LCD (16x2) con interfaz I2C.
   También hay conectado un LED en el pin 13 que se enciende al recibir información del puerto serie
   Para descargar la aplicación y obtener más información visita el blog:
   https://thenerdyapprentice.blogspot.com/ y deja un comentario!
   The Nerdy Apprentice
*/

// Incluimos las librerías necesarias para el LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int LED = 13;

//Seteamos la dirección del LCD -> En mi caso 0x27
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.begin(9600); // Iniciamos el puerto serie
  Serial.println("Hola desde el Arduino!"); // Enviamos mensaje de saludo a la PC

  lcd.begin(16, 2); // Inicializamos el LCD
  lcd.backlight(); // Encendemos la luz de fondo

}

void loop() {

  if (Serial.available()) { // Si el puerto Serial está disponible...
    digitalWrite(LED, HIGH); // Encendemos el LED
    String data = Serial.readString(); // Leemos lo que llega y lo guardamos en la variable data
    // Dividimos los datos recibidos, la PC enviará todos los datos juntos
    String data1 = data.substring(0, 16);
    String data2 = data.substring(16, 32);
    lcd.setCursor(0, 0); // Seteamos la ubicación del cursor en el LCD
    lcd.print(data1); // Mostramos la informacion en el LCD
    Serial.println(data1); // Devuelve la información recibida a la PC.
    delay(320);
    lcd.setCursor(0, 1);
    lcd.print(data2);
    Serial.println(data2); // Devuelve la información recibida a la PC.
  }

  digitalWrite(LED, LOW); // Apagamos el LED (mientras no estemos recibiendo información
}
