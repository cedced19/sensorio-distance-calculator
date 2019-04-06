#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const byte TRIGGER = 5; // D1
const byte ECHO = 4; // D2
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = 8m at 340m/s
const float SOUND_SPEED = 0.34;

// Upload Speed: 115200
// Flash Size: 4M(3M SPIFFS)

const char *ssid = "claire";
const char *password = "26afaf2004";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(TRIGGER, OUTPUT);
  digitalWrite(TRIGGER, LOW);
  pinMode(ECHO, INPUT);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }
  WiFi.mode(WIFI_STA);
  pinMode(12,INPUT);
  Serial.println(WiFi.localIP());
}

void loop() {
     if (WiFi.status() == WL_CONNECTED) {
       int N = 0;
       int values[10];
     
       while (N < 10) {
        digitalWrite(TRIGGER, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIGGER, LOW);
        long measure = pulseIn(ECHO, HIGH, MEASURE_TIMEOUT);
        float distance_cm = measure / 20.0 * SOUND_SPEED;
        if (distance_cm != 0.0) {
          values[N] = distance_cm;
          N++;
        }
       }
       float m = 0;
       int i;
       for (i = 0; i < N; i = i + 1) {
          m+=values[i];
       }
       m = m/N;
  
       Serial.println("");
       Serial.print(m);
       Serial.print(" cm");

 
       HTTPClient http;
       http.begin("http://192.168.0.47:8000/"); // specifie the address
       http.addHeader("Content-Type", "application/x-www-form-urlencoded");
       http.POST("distance=" + String(m));
       http.end();
     }
     delay(10000);
}
