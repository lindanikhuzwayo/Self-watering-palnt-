# Self-watering-palnt
-----------------------------------------------------------------------
Created at self watering plant on the project event hosted by Ozzow payments 
------------------------------------------------------------------------

Code used :  
This code was implemented in Aurdiono IDE 
![WhatsApp Image 2022-08-20 at 9 22 43 PM](https://user-images.githubusercontent.com/88977605/185763258-6a18e216-e684-45ca-b30d-422651e80e4b.jpeg)


#define LED D4 // Use built-in LED which connected to D4 pin or GPIO 2
#define MEASURE_PERIOD 10000 //measure period to prevent instant start/stops 
#define ANA A0 //analog input
#define DIGI D5 //digital input
#define POMPOUT D6 //pump output

long now = millis();
long lastMeasure = 0;

double analogValue = 0.0;
int digitalValue = 0;

void setup() {
  pinMode(ANA, INPUT);
  pinMode(DIGI, INPUT);
  pinMode(POMPOUT, OUTPUT);
  
  Serial.begin(115200);
}

void loop() {
  now = millis();
  // Publishes new temperature and humidity every 30 seconds
  if (now - lastMeasure > MEASURE_PERIOD) {
    lastMeasure = now;
    analogValue = analogRead(ANA);
    digitalValue = digitalRead(DIGI);
    
    Serial.print("Analog raw: ");
    Serial.println(analogValue);
    Serial.print("Digital raw: ");
    Serial.println(digitalValue);
    Serial.println(" ");
    
    if (digitalValue == 0) {
      digitalWrite(POMPOUT, false); //stop pumping water
    } else {
      Serial.println("PUMPIN");
      digitalWrite(POMPOUT, true); //start/continue pumping water
    }
  }
 
  
  
  
}




