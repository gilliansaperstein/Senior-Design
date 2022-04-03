const int xpin = A1;
const int ypin = A2;
const int zpin = A3;
int sampleDelay = 100;

float avg_x;
float avg_y;
float avg_z;

float xval[100] = {0};
float yval[100] = {0};
float zval[100] = {0};
float xavg, yavg, zavg;

bool flag = false;

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
  Serial.print("Time Stamp: ");
  Serial.print('\t');
  Serial.print("Acceleration: ");
}

unsigned long timeStart = millis();
unsigned long currTime;
void loop() {
  int acc = 0;
  float totvect[100] = {0};
  float totave[100] = {0};
  float xaccl[100] = {0};
  float yaccl[100] = {0};
  float zaccl[100] = {0};
  int steps = 0;
  float zero_G =512;
  float scale =102.3; 

  float threshold = 0.5;

  for (int a = 0; a < 100; a++) {
    int x_reading = analogRead(xpin);
    float x_adjust = (float(x_reading) - zero_G)/scale;
    float x_calib = x_adjust - avg_x;
    delay(1); 
  
    int y_reading = analogRead(ypin);
    float y_adjust = (float(y_reading) - zero_G)/scale;
    float y_calib = y_adjust - avg_y;
  
    int z_reading = analogRead(zpin);
    float z_adjust = (float(z_reading) - zero_G)/scale;
    float z_calib = z_adjust - avg_z;
    
    xaccl[a] = x_calib;
    delay(1);
    yaccl[a] = y_calib;
    delay(1);
    zaccl[a] = z_calib;
    delay(1);
  
    totvect[a] = sqrt(((xaccl[a] - xavg) * (xaccl[a] - xavg)) + ((yaccl[a] - yavg) * (yaccl[a] - yavg)) + ((zval[a] - zavg) * (zval[a] - zavg)));
    totave[a] = (totvect[a] + totvect[a - 1]) / 2 ;
    currTime = millis() - timeStart;
    Serial.print(currTime);
    Serial.print('\t');
    Serial.println(totave[a]);
  
//  if (totave[a] > threshold && !flag)
//  {
//    steps = steps + 1;
//    flag = 1; }
//
////  else if (totave[a] > threshold && flag)
////  {
////    // Don’t Count
////  }
//
//  if (totave[a] < threshold  && flag)
//  {
//    flag = false;
//  }
//
//    Serial.println(steps);
//  }

    
//   if (absX > threshold || absY > threshold || absZ > threshold) {
//      int currentTime = millis() - timeStart;
//      float move_accel = max3(absX, absY, absZ);
//      Serial.print("Movement Detected - Acceleration = ");
//      Serial.println(move_accel);
//
////        Serial.print("X:");
////        Serial.println(absX);
////        Serial.print("Y:");
////        Serial.println(absY);
////        Serial.print("Z:");
////        Serial.println(absZ);
//   }
   
   //
   // delay before next reading:
   delay(sampleDelay);
   
}
}
