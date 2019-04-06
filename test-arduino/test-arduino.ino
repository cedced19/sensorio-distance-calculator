const byte TRIGGER = 6; 
const byte ECHO = 7; 
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = 8m at 340m/s
const float SOUND_SPEED = 0.34;

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER, OUTPUT);
  digitalWrite(TRIGGER, LOW);
  pinMode(ECHO, INPUT);
}
void loop() {
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
 
  long measure = pulseIn(ECHO, HIGH, MEASURE_TIMEOUT);
  
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  Serial.println("");
  Serial.print(distance_mm / 10.0, 2);
  Serial.print(" cm");
  
  delay(300);
}
