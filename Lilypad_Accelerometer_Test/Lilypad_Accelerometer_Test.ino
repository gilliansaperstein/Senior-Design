//https://www.geeetech.com/wiki/index.php/LilyPad_Accelerometer_ADXL335
const int xpin = A1;
const int ypin = A2;
const int zpin = A3;
int sampleDelay = 100;

float avg_x;
float avg_y;
float avg_z;

float max3(float a, float b, float c)
{
   float maxguess;

   maxguess = max(a,b);  // biggest of A and B
   maxguess = max(maxguess, c);  // but maybe C is bigger?

   return(maxguess);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Hold still for 5 seconds");
  Serial.println("Begin calibrating");
  analogReference(EXTERNAL); //3.3V pin
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
  int timeStart = millis();
  int counter = 0;
  float x = 0;
  float y = 0;
  float z = 0;
  float zero_G =512;
  float scale =102.3; 
  while (timeStart < 5000) {
    int x_raw = analogRead(xpin);
    float x_adjust = (float(x_raw) - zero_G)/scale;
    x = x + x_adjust;
    delay(1);
    int y_raw = analogRead(ypin);
    float y_adjust = (float(y_raw) - zero_G)/scale;
    y = y + y_adjust;
    delay(1);
    int z_raw = analogRead(zpin);
    float z_adjust = (float(z_raw) - zero_G)/scale;
    z = z + z_adjust;
    delay(1);
    timeStart = millis();
    counter++;
  }
  Serial.println("Calibration Complete: Begin Moving");
  avg_x = x/counter;
  avg_y = y/counter;
  avg_z = z/counter;
  Serial.print("X offset: ");
  Serial.print(avg_x);
  Serial.print("\t");
  Serial.print("Y offset: ");
  Serial.print(avg_y);
  Serial.print("\t");
  Serial.print("Z offset: ");
  Serial.print(avg_z);
  Serial.println();
}

int timeStart = millis();
void loop() {
  float zero_G =512;
  float scale =102.3; 
  
  int x_reading = analogRead(xpin);
  float x_adjust = (float(x_reading) - zero_G)/scale;
  float x_calib = x_adjust - avg_x;
   //
   //add a small delay between pin readings.  I read that you should
   //do this but haven't tested the importance
   delay(1); 

  int y_reading = analogRead(ypin);
  float y_adjust = (float(y_reading) - zero_G)/scale;
  float y_calib = y_adjust - avg_y;

//   //add a small delay between pin readings.  I read that you should
//   //do this but haven't tested the importance
//   delay(1); 
//   //
  int z_reading = analogRead(zpin);
  float z_adjust = (float(z_reading) - zero_G)/scale;
  float z_calib = z_adjust - avg_z;
   
   //
   //scale is the number of units we expect the sensor reading to
   //change when the acceleration along an axis changes by 1G.
   //Divide the shifted sensor reading by scale to get acceleration in Gs.

   float absX = abs(x_calib);
   float absY = abs(y_calib);
   float absZ = abs(z_calib);

   float threshold = 0.5;

    
   if (absX > threshold || absY > threshold || absZ > threshold) {
      int currentTime = millis() - timeStart;
      float move_accel = max3(absX, absY, absZ);
      Serial.print("Movement Detected - Acceleration = ");
      Serial.println(move_accel);

//        Serial.print("X:");
//        Serial.println(absX);
//        Serial.print("Y:");
//        Serial.println(absY);
//        Serial.print("Z:");
//        Serial.println(absZ);
   }
   
//   Serial.print(x_calib);
//   Serial.print("\t");
//   
//   Serial.print(y_calib);
//   Serial.print("\t");
// 
//   Serial.print(z_calib);
//   Serial.print("\n");
   //
   // delay before next reading:
   delay(sampleDelay);
   
}
