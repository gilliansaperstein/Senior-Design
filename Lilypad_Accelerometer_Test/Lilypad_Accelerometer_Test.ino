//https://www.geeetech.com/wiki/index.php/LilyPad_Accelerometer_ADXL335
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

//Testing to see if I can send data to PHP
void calculation() {
  if (client.connect("http://ec2-13-58-190-43.us-east-2.compute.amazonaws.com", 80)) 
        {
            Serial.println("connected");
//            client.print("POST /test/test.php?");
//            client.print("rpm=");
//            client.print(REV);
//            client.print("&Lengths=");
//            client.print(Length);
//            client.println("");
//            client.println("  HTTP/1.1");
            //client.stop();
        }
        else {
             // If Arduino can't connect to the server (your computer or web page)
            Serial.println("--> connection failed\n");
              }[code]
}
