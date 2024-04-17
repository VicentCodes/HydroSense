#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "TDS.h"
#include "MotorControl.h"
#include "TempSensor.h"
#include "pHSensor.h"


const char* ssid = "INFINITUM17E6_2.4";
const char* password = "Telmexclave23";
const char* serverUrl = "https:/";

// TDS Pins
const int pinTDS = 10;  // Pin TDS
TDS tdsSensor(pinTDS);

// Pump Water Pins
const int ENA = 10;
const int IN1 = 11;
const int IN2 = 12;
MotorControl motor(ENA, IN1, IN2);

// DS18B20 Temp pins
const int pinDatosDQ = 11;
TempSensor temperatureSensor(pinDatosDQ);

// pH sensor pins
const int analogInPin = 12;
pHSensor pH_Sensor(analogInPin);

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  motor.setupMotor();               //motor Setup
  temperatureSensor.setupSensor();  // DS18B20 Setup
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    const int numReadings = 2;  // Número de lecturas a promediar
    float temperatureSum = 0;

    float tdsSum = 0;
    float pHSum = 0;

    for (int i = 0; i < numReadings; ++i) {
      float temperature = temperatureSensor.readTemperature();
      float tdsValue = tdsSensor.readTDS();
      float pHValue = pH_Sensor.readpHValue();

      temperatureSum += temperature;
      tdsSum += tdsValue;
      pHSum += pHValue;

      Serial.print("Lectura numero: ");
      Serial.println(i);
      Serial.print("PH: ");
      Serial.println(pHValue);
      Serial.print("TDS: ");
      Serial.println(tdsValue);
      Serial.print("Temp: ");
      Serial.println(temperature);


      delay(5000);  // Esperar 5 segundos entre cada lectura
    }

    float avgTemperature = temperatureSum / numReadings;
    float avgTDS = tdsSum / numReadings;
    float avgPH = pHSum / numReadings;

    sendDataToServer(avgTemperature, avgTDS, avgPH);

    delay(1000);  // Wait for 60 seconds before sending next data
  } else {
    connectToWiFi();  // Reconnect to WiFi if connection is lost
  }
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void sendDataToServer(float temperature, float tdsValue, float pHValue) {
  WiFiClient client;
  HTTPClient http;

  DynamicJsonDocument doc(2048);
  doc["temp"] = temperature;
  doc["TDS"] = tdsValue;
  doc["pH"] = pHValue;

  String json;
  serializeJson(doc, json);

  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(json);

  if (httpResponseCode == 200) {
    Serial.println("Data sent successfully!");
  } else {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.print("Error in HTTP request: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
