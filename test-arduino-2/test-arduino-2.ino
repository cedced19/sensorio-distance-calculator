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
  m = m/N;;
  
  
  Serial.println("");
  Serial.print(m);
  Serial.print(" cm");
  
  delay(3000);
}
