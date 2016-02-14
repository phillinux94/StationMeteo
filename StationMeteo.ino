// Import de la bibliothèque DHT
#include "DHT.h"

// Import de la bibliothèque de l'afficheur LCD
#include <LiquidCrystal.h>


// Définition du port numérique de la sonde température + humidité
#define DHTPIN 6

// Définition du type DHT 22
#define DHTTYPE DHT22

// Initialisation de la sonde DHT 22
DHT dht22(DHTPIN, DHTTYPE);

// Initialisation de l'affichage
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


// Définition des variables de la sonde
// Humidité
float humidite;

// Température celsius
float temperature;

void setup() {

  // Lancement de la sonde DHT 22
  dht22.begin();

  // Définition des caractéristiques de l'affichage
  lcd.begin(16, 2);

  // Définition des led's de tendance de température
  pinMode(8, OUTPUT); // Baisse
  pinMode(9, OUTPUT); // Hausse

  // Première lecture de la température en Celsius
  temperature = dht22.readTemperature();
  

}

void loop() {
  // Une lecture toutes les 3 secondes
  delay(3000);

  if (dht22.readTemperature() > temperature) {
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
  }
  else if (dht22.readTemperature() < temperature) {
    digitalWrite(9, LOW);
    digitalWrite(8, HIGH);
  }
  else {
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
  }

  // Lecture de l'humidité
  humidite = dht22.readHumidity();

  // Lecture de la température en Celsius
  temperature = dht22.readTemperature();

  // Test de présence de la sonde
  if (isnan(humidite) || isnan(temperature)) {
    Serial.println("Impossible de lire la sonde DHT22");
    return;
  }

  // Positionnement du curseur colonne 0 ligne 0 pour l'humidité
  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.print(humidite);
  lcd.print("%  ");

  // Positionnement du curseur colonne 0 ligne 1 pour la température
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("   ");
}
