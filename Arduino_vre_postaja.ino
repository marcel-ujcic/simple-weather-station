#include <DHT.h>
#include <DHT_U.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
/* Declare LCD object for software SPI
 Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);*/
 
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

#define PIN 8
#define TYPE DHT11  
// Prototype Declartion  
DHT dht(PIN, TYPE);   

int led = 13; // define the LED pin
int digitalPin = 2; // KY-028 digitalna povezava
int analogPin = A1; // KY-028 analogna povezava
int digitalVal; // digitalne vrednosti
int temp; //analogne vrednosti



void setup ()
{
  pinMode(led, OUTPUT);
  pinMode(digitalPin, INPUT);
  display.begin ();
  display.setContrast(57);
  
  /* Praznenje bufferja */
  display.clearDisplay();
  
  display.setTextColor(BLACK);
    display.setCursor(4,8);
   display.setTextSize(1);
  dht.begin(); 
  delay(1000);    
}

void loop ()
{
	// zakasnitev 3s 
  delay(3000); 
  display.clearDisplay();
  
  /* Prikaz teksta */
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.print("Temp zunaj:");
  temp = analogRead(analogPin); temp = temp * 0.48828125;
  display.print(temp); // print analog value to serial
  display.println("C");
  display.display();
  display.setCursor(0,10);
  display.print("Znotraj");
  display.setCursor(0,15);
 // delay(100);
    //  
    float humidity = dht.readHumidity();  
    float temp_cel = dht.readTemperature(); // in Clecius  
    // v primeru ne uspešnega branja podatkov 
    if (isnan(humidity) || isnan(temp_cel)) {  
        
        display.println("# Neuspešno branje iz DHT modula");  
        display.display();
        return;  
    } else { 
        // Izpis vlažnosti
        display.setCursor(0,20);
        display.print("Vlaznost: ");  
        display.print(round(humidity));
        display.println("%");  
        // Izpis temperature
        display.setCursor(0,28);
        display.print("Temp: ");  
        display.print(round(temp_cel));  
        display.print(" C - ");  
        display.display();
        //delay(2000); 
        
    }   
}
