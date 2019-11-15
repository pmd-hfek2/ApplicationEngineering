#include "Accelerometer.h"

#include <stdio.h>
#include <string.h>
#include "Arduino.h"

Accelerometer::Accelerometer()
{
}

Accelerometer::Accelerometer(int x_threshold,int y_threshold, int z_threshold, float x_gain,float y_gain,float z_gain)
{
	X_th = x_threshold;
	Y_th = y_threshold;
	Z_th = z_threshold;
	X_gain = x_gain;
	Y_gain = y_gain;
	Z_gain = z_gain;
}

void Accelerometer::init(uint8_t X, uint8_t Y, uint8_t Z)
{
	pinX = X;
	pinY = Y;
	pinZ = Z;

  pinMode(pinX,INPUT);
  pinMode(pinY,INPUT);
  pinMode(pinZ,INPUT);

  Serial.println(F("Accelerometer.....initialised."));
}

void Accelerometer::read_data()
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

void Accelerometer::auto_calibrate()
{
	read_data();
	X_bias = X_read*X_gain;
	Y_bias = Y_read*Y_gain;
	Z_bias = Z_read*Z_gain;
	Serial.println(F("*** AUTO-CALIBRATION X-Y-Z (Bias G) ***"));
	Serial.print(X_bias);
	Serial.print(F("G ; "));
	Serial.print(Y_bias);
	Serial.print(F("G ; "));
	Serial.print(Z_bias);
	Serial.println(F("G"));
	Serial.println(F("Accelerometer.....calibrated."));
}

void Accelerometer::manual_calibrate(int x_bias, int y_bias, int z_bias)
{
	X_bias = x_bias;
	Y_bias = y_bias;
	Z_bias = z_bias;
	Serial.println(F("*** CALIBRATION X-Y-Z (Bias G) ***"));
	Serial.print(X_bias);
	Serial.print(F("G ; "));
	Serial.print(Y_bias);
	Serial.print(F("G ; "));
	Serial.print(Z_bias);
	Serial.println(F("G"));
	Serial.println(F("Accelerometer.....calibrated."));
}

void Accelerometer::print_raw()
{
	//Serial.println(F("*** ACCEL. X-Y-Z (raw)   ***"));
	Serial.print(X_read);
	Serial.print(F("   ; "));
	Serial.print(Y_read);
	Serial.print(F("   ; "));
	Serial.println(Z_read);
}

void Accelerometer::print_accel()
{
	//Serial.println(F("*** ACCEL. X-Y-Z (G)     ***"));
	Serial.print(X_G);
	Serial.print(F("G ; "));
	Serial.print(Y_G);
	Serial.print(F("G ; "));
	Serial.print(Z_G);
	Serial.println(F("G"));
}

void Accelerometer::print_max()
{
	Serial.println(F("*** ACCEL. X-Y-Z (Max. G) ***"));
	Serial.print(X_max);
	Serial.print(F("G ; "));
	Serial.print(Y_max);
	Serial.print(F("G ; "));
	Serial.print(Z_max);
	Serial.println(F("G"));
}

void Accelerometer::start(bool run)
{
	if(run)
	{
		read_data();
		if(X_read > X_th && Y_read > Y_th && Z_read > Z_th)
		{
			//Serial.println(F("*** ACCEL. X-Y-Z (raw)   ***"));
			Serial.println(F("*** ACCEL. X-Y-Z (G)     ***"));
			while(X_read > X_th || Y_read > Y_th || Z_read > Z_th)
			{
				//print_raw();
				print_accel();
				read_data();
			}
			print_max();
		}
		X_max = Y_max = Z_max = 0;
	}
}
