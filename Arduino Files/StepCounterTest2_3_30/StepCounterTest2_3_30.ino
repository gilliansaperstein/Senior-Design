const int xpin = A1;
const int ypin = A2;
const int zpin = A3;
int sampleDelay = 100;

float avg_x;
float avg_y;
float avg_z;

float xval;
float yval;
float zval;
float xavg, yavg, zavg;

float threshold = 0.6;
float timeThreshold = 1000;

bool flag = false;

void calibrate() {
  Serial.println("Hold still for 5 seconds");
  Serial.println("Begin calibrating");
  
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
  Serial.print('\t');
  Serial.print("Steps:");
  Serial.println("");
  
  Serial.println("Calibration Complete: Begin Moving");
}

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL); //3.3V pin
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
  calibrate();
}

unsigned long timeStart = millis();
unsigned long currTime;
int steps = 0;

float baseline = 0;
float baseCounter = 0;

void loop() {
  int acc = 0;

  float totvect;
  float totave;
  float xaccl;
  float yaccl;
  float zaccl;
  float zero_G =512;
  float scale =102.3; 

unsigned long timeOfCrossThreshold = 0;
    int x_reading = analogRead(xpin);
    float x_adjust = (float(x_reading) - zero_G)/scale;
    float x_accl = x_adjust - avg_x;
    delay(1); 
  
    int y_reading = analogRead(ypin);
    float y_adjust = (float(y_reading) - zero_G)/scale;
    float y_accl = y_adjust - avg_y;
    
    delay(1);
    int z_reading = analogRead(zpin);
    float z_adjust = (float(z_reading) - zero_G)/scale;
    float z_accl = z_adjust - avg_z;


    totave = sqrt(((xaccl - xavg) * (xaccl - xavg)) + ((yaccl - yavg) * (yaccl - yavg)) + ((zval - zavg) * (zval - zavg)));
    currTime = millis() - timeStart;
  
//   if (totave[a] < totave[a - 1] + 0.02 && totave[a] > totave[a - 1] - 0.02) {
//      baseline = baseline + totave[a];
//      baseCounter = baseCounter + 1;
//  
//      if (baseCounter >= 1000) {
//        float avg = baseline / baseCounter;
//        Serial.print("New baseline is:");
//        Serial.println(avg);
//        baseline = 0;
//        baseCounter = 0;
//        threshold = 10* baseline;
//      }
//  }
  
  if (totave > threshold && timeOfCrossThreshold == 0)
  {
    steps = steps + 1;
    Serial.println("Movement Detected!");
    timeOfCrossThreshold = millis();
   }

  else if (totave > threshold)
  {
    if (millis() - timeOfCrossThreshold < timeThreshold) {
      
    }
    else {
      steps = steps + 1;
      Serial.println("Movement Detected!");
      timeOfCrossThreshold = 0;
    }
  }

  else
  {
    timeOfCrossThreshold = 0;
  }

    Serial.print(currTime);
    Serial.print('\t');
    Serial.print(totave);
    Serial.print('\t');
    Serial.println(steps);

   delay(sampleDelay);
   
}
