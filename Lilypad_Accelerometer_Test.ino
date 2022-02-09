
const int xpin = A1;
const int ypin = A2;
const int zpin = A3;
int sampleDelay = 100;

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL); //3.3V pin
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
}

void loop() {
    int x = analogRead(xpin);
   //
   //add a small delay between pin readings.  I read that you should
   //do this but haven't tested the importance
   delay(1); 
   //
   int y = analogRead(ypin);
   //
   //add a small delay between pin readings.  I read that you should
   //do this but haven't tested the importance
   delay(1); 
   //
   int z = analogRead(zpin);
     float zero_G =512; 
   //
   //scale is the number of units we expect the sensor reading to
   //change when the acceleration along an axis changes by 1G.
   //Divide the shifted sensor reading by scale to get acceleration in Gs.
   float scale =102.3;
   //
   Serial.print(((float)x - zero_G)/scale);
   Serial.print("\t");
   //
   Serial.print(((float)y - zero_G)/scale);
   Serial.print("\t");
   //
   Serial.print(((float)z - zero_G)/scale);
   Serial.print("\n");
   //
   // delay before next reading:
   delay(sampleDelay);
}
