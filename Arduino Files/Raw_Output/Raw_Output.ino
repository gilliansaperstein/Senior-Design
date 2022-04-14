const int xpin = A1;
const int ypin = A2;
const int zpin = A3;
int sampleDelay = 100;

const int sampleSize = 10;
int RawMin = 0;
int RawMax = 1023;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogReference(EXTERNAL); //3.3V pin
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
  Serial.print("Time:");
  Serial.print('\t');
  Serial.print("X Output:");
  Serial.print('\t');
  Serial.print("Y Output:");
  Serial.print('\t');
  Serial.print("Z Output:");
  Serial.print('\t');
  Serial.println();
}

unsigned long timeStart = millis();

void loop() {
  // put your main code here, to run repeatedly:
//float x_reading = analogRead(xpin);
//float y_reading = analogRead(ypin);
//float z_reading = analogRead(zpin);

float x_reading = ReadAxis(xpin);
float y_reading = ReadAxis(ypin);
float z_reading = ReadAxis(zpin);

long xScaled = map(x_reading, RawMin, RawMax, -3000, 3000);
long yScaled = map(y_reading, RawMin, RawMax, -3000, 3000);
long zScaled = map(z_reading, RawMin, RawMax, -3000, 3000);

float xAccel = xScaled / 1000.0;
float yAccel = yScaled / 1000.0;
float zAccel = zScaled / 1000.0;

unsigned long currTime = millis() - timeStart;
Serial.print(currTime);
Serial.print('\t');
Serial.print(xAccel);
Serial.print('\t');
Serial.print(yAccel);
Serial.print('\t');
Serial.print(zAccel);
Serial.print('\t');
Serial.println();
}

float ReadAxis(int axisPin) {
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i=0; i < sampleSize; i++) {
    reading += analogRead(axisPin);
  }
  return reading / sampleSize;
 
}
