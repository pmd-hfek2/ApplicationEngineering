//--- PRECISION MICRODRIVES ---
//-- OPP 1066 - AddHaptics
//- Tristan Cool
//- November, 2019

//*** This program reads accelerometer axis***//
//*** TODO ***//


//-------------- Libraries ----------------------------------
#include "Accelerometer.h"

//--------------- Arduino pins -----------------------------

//--- ACCELEROMETER:
#define pinX  A4        //X axis
#define pinY  A2        //Y axis
#define pinZ  A0        //Z axis


//-------------- Variables ----------------------------------
//Accelerometer accelerometer();
Accelerometer accelerometer(183,182,198,0.0303,0.0303,0.0303); // xyz threshold, xyz gain

//************************************ SETUP ******************************************
void setup()
{
  //Serial Monitor [Ctrl + Shift + m]
  Serial.begin (9600);
  Serial.println(F("**** PRECISION MICRODRIVES - Tristan Cool - Nov,2019 ****"));

  accelerometer.init(pinX,pinY,pinZ);
  accelerometer.auto_calibrate();
  //accelerometer.manual_calibrate(6,6,6);

} //END: setup

//******************************* LOOP ***************************************
void loop()
{
  accelerometer.start(true);
} //END: loop


//************** FUNCTIONS ***********************
void debug()
{
  
}
