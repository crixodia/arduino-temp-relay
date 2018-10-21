#include <LiquidCrystal.h>//Librería Liquid Crystal
#include "DHT.h"//Librería DHT11 de Adafruit
#define DHTPIN 2 //Pin de sensor de DHT11
#define DHTTYPE DHT11 //Tipod e sensor
const int rele=3, led=4; //Pin para relé | pin para led
long varPot, varPot2; //potenciómetros
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(7, 8, 9, 10, 11 , 12); //pines para LCD
void setup(){
  Serial.begin(9600);
  Serial.println("Prueba DHT11");
  pinMode(rele,OUTPUT);
  pinMode(led,OUTPUT);
  dht.begin();
  lcd.begin(16,2);//LCD 16x2
  lcd.setCursor(0,0); 
  lcd.write("Espere...."); 
  }

void loop(){
  delay(2000);
  varPot = analogRead(A0);//Pot
  varPot2= analogRead(A1);//Pot
  varPot2=varPot2/20;//Se divide para 20 para tomar valores correctos
  varPot=varPot/20;
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Esperando DHT11...");
    return;
  }
  
    if(t<=varPot2){
      //Activa relé y led
      digitalWrite(rele,HIGH);
      digitalWrite(led,HIGH);
    }
    else if(t>=varPot){
      //desactiva relé y led
      digitalWrite(rele,LOW);
      digitalWrite(led,LOW);
    }
  //Imprime la temperatura actual en la primera fila de LCD
  lcd.begin(16, 2); 
  lcd.setCursor(0,0); 
  lcd.write("Temperatura: "); 
  lcd.setCursor(12,0); 
  lcd.print(t);
  lcd.setCursor(14,0); 
  lcd.write((char)223);
  lcd.setCursor(15,0); 
  lcd.write("C");

  //Imprime los límites de temperatura en la segunda fila LCD
  lcd.setCursor(0,1); 
  //lcd.write("Humedad: ");
  lcd.write("MIN: "); 
  lcd.setCursor(4,1); 
  //lcd.print(h);
  lcd.print(varPot);
  lcd.setCursor(8,1);
  lcd.print("MAX: ");
  lcd.print(varPot2);
  lcd.setCursor(14,1);
  //lcd.write("%");
} 
