#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED D4 // Use built-in LED which connected to D4 pin or GPIO 2
#define NETWORK_NAME "network name" 
#define PASSWORD "network password"
#define MQTT_SERVER "broker.mqttdashboard.com"
#define MQTT_CLIENT_ID "your client id"
#define MEASURE_PERIOD 10000
#define PORT 80
#define ANA A0
#define DIGI D5
#define POMPOUT D6

long now = millis();
long lastMeasure = 0;

double analogValue = 0.0;
int digitalValue = 0;


void setup() {
  pinMode(ANA, INPUT);
  pinMode(DIGI, INPUT);
  pinMode(POMPOUT, OUTPUT);
  
  Serial.begin(115200);
  
  setup_wifi();
  
  client.setServer(MQTT_SERVER, 1883);
  client.setCallback(callback);
  
  setupServer();
}

void loop() {
  server.handleClient();

  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect(MQTT_CLIENT_ID);

  now = millis();
  // Publishes new temperature and humidity every 30 seconds
  if (now - lastMeasure > MEASURE_PERIOD) {
    lastMeasure = now;
    analogValue = analogRead(ANA);
    digitalValue = digitalRead(DIGI);
    // Serial data
    Serial.print("Analog raw: ");
    Serial.println(analogValue);
    Serial.print("Digital raw: ");
    Serial.println(digitalValue);
    Serial.println(" ");
    if (digitalValue == 0) {
      digitalWrite(POMPOUT, false);
    } else {
      Serial.println("PUMPIN");
      digitalWrite(POMPOUT, true);
    }

    static char humidityTemp[7];
    dtostrf(analogValue, 6, 2, humidityTemp);

    sprintf(buffer, "%.0f;%d\n", analogValue, digitalValue);

    // Publishes Temperature and Pump values
    client.publish("plant-data", buffer);
  }

  delay(1000);
}


}
