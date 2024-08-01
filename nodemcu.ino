#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHT11_PIN D4
#define WATER_SENSOR_PIN A0

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht11(DHT11_PIN, DHT11);

// WiFi bağlantı bilgileri
const char* ssid = "your_ssid";
const char* password = "your_password";
// Sunucu URL'si
const char* serverUrl = "your_server_url";

void sendPostRequest(String postData) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverUrl);  // Yeni API kullanımı

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    String response = http.getString();
    //Serial.println(httpResponseCode);
    Serial.println(response);  // Sunucudan gelen cevabı seri portta göster
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void connectToWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    lcd.print("Wifi bekleniyor");
    delay(1000);
    lcd.clear();
  }

  Serial.println("Wifi baglandi");
}

void setup() {
  Serial.begin(9600);
  dht11.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED)
    connectToWiFi();

  // Nem okumayı yap
  float humidity = dht11.readHumidity();
  // Sıcaklığı Celsius olarak oku
  float temperatureC = dht11.readTemperature();
  // Su seviyesi okumayı yap
  int waterLevel = analogRead(WATER_SENSOR_PIN);

  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println("DHT11 sensöründen okuma yapılamadı!");
  } else {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Nem:");
    lcd.print(humidity);
    lcd.print("% ");
    lcd.print(waterLevel);
    
    lcd.setCursor(0, 1);
    lcd.print("Sicaklik:");
    lcd.print(temperatureC);
    lcd.print("\337C");

    String postData = "humidity=" + String(humidity, 2) + "&temperature=" + String(temperatureC, 2) + "&waterLevel=" + String(waterLevel);
    sendPostRequest(postData);

    delay(2000);
  }
}
