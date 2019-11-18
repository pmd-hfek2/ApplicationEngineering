//--- PRECISION MICRODRIVES ---
//-- OPP 1066 - AddHaptics
//- Tristan Cool
//- November, 2019

//*** This program reads accelerometer axis***//
//*** TODO ***//


//-------------- Libraries ----------------------------------


//--------------- Arduino pins -----------------------------

//--- ACCELEROMETER:
#define pinX  A4        //X axis
#define pinY  A2        //Y axis
#define pinZ  A0        //Z axis


//-------------- Variables ----------------------------------
uint16_t X_read,Y_read,Z_read;      //10 bit accelerometer signal (raw)
float X_G,Y_G,Z_G;                  //Accelerometer axis in G (gain)

float X_gain,Y_gain,Z_gain;         //Accelerometer calibration factor (~80mV/G)
int X_th,Y_th,Z_th;                 //Accelerometer threshold (noise)
int X_bias,Y_bias,Z_bias;           //Accelerometer calibrate (bias)
float X_max,Y_max,Z_max;            //G value



//************************************ SETUP ******************************************
/*
 * CALIBRATE:
 * Lay accelerometer flat, print values of 1 axis, record min value (threshold)
 * Flip accelerometer, record values
 * Calculate difference, this is the value of 1G (Gain is 1/difference)
 * Divide reading of accelerometer flat by this difference, this is the bias factor
 * The absolute value for axis in G is: Reading/Gain - Bias
 * 
 * Z: 165,198 --> 1G = 33 --> 1/33 = 0.0303 --> 198/33 = 6G ==> Z = (read*0.0303)-6
 * Y: 165,198 --> 1G = 33 --> 1/33 = 0.0303 --> 198/33 = 6G ==> Y = (read*0.0303)-6
 * X: 167,200 --> 1G = 33 --> 1/33 = 0.0303 --> 200/33 = 6G ==> X = (read*0.0303)-6
*/

void setup()
{
  Serial.begin(9600);
  
  //init (pins)
  pinMode(pinX,INPUT);
  pinMode(pinY,INPUT);
  pinMode(pinZ,INPUT);

  //init (gain, threshold)
  X_th = 183;//182
  X_gain = 0.0303; 
  X_bias = 6;
  X_max = 0;
  Y_th = 182; //182
  Y_gain = 0.0303;
  Y_bias = 6;
  Y_max = 0;
  Z_th = 198; //197
  Z_gain = 0.0303;
  Z_bias = 6;
  Z_max = 0;

  auto_calibrate();
  //manual_calibrate(6,6,6);
  

} //END: setup

//******************************* LOOP ***************************************
void loop()
{
  //RUN
  read_accel();
  if(X_read > X_th && Y_read > Y_th && Z_read > Z_th)
  {
    //Serial.println(F("*** ACCEL. X-Y-Z (raw)   ***"));
    Serial.println(F("*** ACCEL. X-Y-Z (G)     ***"));
    while(X_read > X_th || Y_read > Y_th || Z_read > Z_th)
    {
      //print_raw();
      print_accel();
      read_accel();
    }
    print_max();
  }
  X_max = Y_max = Z_max = 0;
  
} //END: loop


//************** FUNCTIONS ***********************
void debug()
{
  //DEBUG
}

void read_accel()
{
  X_read = analogRead(pinX);
  Y_read = analogRead(pinY);
  Z_read = analogRead(pinZ);

  X_G = abs((X_read*X_gain)-X_bias);
  Y_G = abs((Y_read*Y_gain)-Y_bias);
  Z_G = abs((Z_read*Z_gain)-Z_bias);

  if(X_G > X_max)
    X_max = X_G;
  if(Y_G > Y_max)
    Y_max = Y_G;
  if(Z_G > Z_max)
    Z_max = Z_G;
}

void auto_calibrate()
{
  read_accel();
  //set threshold to base values + small tolerance
  X_th = X_read + 3;
  Y_th = Y_read + 3;
  Z_th = Z_read + 3;
  //(DC)bias is initial reading with gain (in G)
  X_bias = X_read*X_gain;
  Y_bias = Y_read*Y_gain;
  Z_bias = Z_read*Z_gain;
  Serial.println(F("*** CALIBRATION X-Y-Z (Bias G) ***"));
  Serial.print(X_bias);
  Serial.print(F("G ; "));
  Serial.print(Y_bias);
  Serial.print(F("G ; "));
  Serial.print(Z_bias);
  Serial.println(F("G"));
}

void manual_calibrate(int x_bias, int y_bias, int z_bias)
{
  X_bias = x_bias;
  Y_bias = y_bias;
  Z_bias = z_bias;
  Serial.println(F("*** AUTO-CALIBRATION X-Y-Z (Bias G) ***"));
  Serial.print(X_bias);
  Serial.print(F("G ; "));
  Serial.print(Y_bias);
  Serial.print(F("G ; "));
  Serial.print(Z_bias);
  Serial.println(F("G"));
}

void print_raw()
{
  Serial.print(X_read);
  Serial.print(F("   ; "));
  Serial.print(Y_read);
  Serial.print(F("   ; "));
  Serial.println(Z_read);
}

void print_accel()
{
  Serial.print(X_G);
  Serial.print(F("G ; "));
  Serial.print(Y_G);
  Serial.print(F("G ; "));
  Serial.print(Z_G);
  Serial.println(F("G"));
}

void print_max()
{
  Serial.println(F("*** ACCEL. X-Y-Z (Max. G) ***"));
  Serial.print(X_max);
  Serial.print(F("G ; "));
  Serial.print(Y_max);
  Serial.print(F("G ; "));
  Serial.print(Z_max);
  Serial.println(F("G"));
}
