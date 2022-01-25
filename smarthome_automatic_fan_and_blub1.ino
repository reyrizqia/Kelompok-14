#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//temp sensor
const int tmpPin = A0;

//Motor Driver
int Enable = 13;
int inp3 = 8;
int inp4 = 9;

int yellowLed = 10; //Lampu Pemanas

//Ldr sensor
const int bulbPin = 7;
const int ldrPin = A1;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  //temp sensor
  pinMode(tmpPin, INPUT);

  //Motor Driver
  pinMode(Enable, OUTPUT);
  pinMode(inp3, OUTPUT);
  pinMode(inp4, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  
  //ldrsensor
  pinMode(bulbPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void loop() {
  //membaca signal analog dari ldr dan temp sensor
  int ldrStatus = analogRead(ldrPin);
  
  int Temp = analogRead(tmpPin);
  
  light(ldrStatus);
  temperature(Temp);

  delay(1000); // 1 jeda detik
}

//Indikator lampu
void light(int ldrStatus){
  if (ldrStatus <= 300) 
  {
  	digitalWrite(bulbPin, HIGH);
  	Serial.print("Ini Gelap, Nyalakan lampu \n");
	lcd.setCursor(10, 1);
    lcd.print("L= ON ");
  } 
  else 
  {
  	digitalWrite(bulbPin, LOW);
    Serial.print("Ini Terang, Matikan Lampu \n");
    lcd.setCursor(10, 1);
    lcd.print("L= OFF");
  }
}

//Kode temperatur
void temperature(int Temp){
  float voltage = Temp * 5.0; //membaca kemudian mengubah voltase 
  voltage /= 1024.0; 
  float c = (voltage - .5) * 100; //mengubah voltase menjadi celcius
  float f = (c * 9 / 5 + 32); //mengubah celcius mejadi farenheit
  Serial.println(c);
  lcd.setCursor(0, 0);
  lcd.print("T=");
  lcd.setCursor(3, 0);
  lcd.print(c);
  lcd.setCursor(8, 0);
  lcd.print("C");
  lcd.setCursor(10, 0);
  lcd.print(f);
  lcd.setCursor(15, 0);
  lcd.print("F");
  
  //temp sensor dan fan
  digitalWrite(inp3, LOW);  // untuk mengarahkan kipas
  digitalWrite(inp4, HIGH);
  
  lcd.setCursor(0, 1);
  
  if(c < 15) {                 // Jika suhu kurang dari 15
      analogWrite(Enable,0);	//Fann OFF
      lcd.print("Heat  ON");
      digitalWrite(yellowLed, HIGH); //heating light
      delay(10);
      Serial.print("Lampu Pemanas menyala, ");
    }
  	else if(c>=15 & c<20) {      // Jika suhu antara 20 & 30
      analogWrite(Enable, 0);  // kekuatan kipas 0% (255). 
      lcd.print("Fan  OFF");
      digitalWrite(yellowLed, LOW);
      delay(10);
    }
    else if(c>=20 & c<30) {      // Jika suhu antara 20 & 30
      analogWrite(Enable, 128);  // Kekuatan kipas 50% (255). 
      lcd.print("Fan: 50%");
      digitalWrite(yellowLed, LOW);
      delay(10);
    }
    else if(c>=30 & c<45) {      // Jika suhu antara 30 & 45
      analogWrite(Enable, 178);  // Kekuatan kipas  70% (255).
      lcd.print("Fan: 70%");
      digitalWrite(yellowLed, LOW);
      delay(10);
    }
    else if(c>=45) {                // Jika suhu di atas 45
      analogWrite(Enable, 255);      // kekuatas kipas 100% (255).
      lcd.print("Fan:100%");
      digitalWrite(yellowLed, LOW);
      delay(10);
    }
}
