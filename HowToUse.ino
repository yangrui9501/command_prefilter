#include <Arduino.h>
#include "Third_Order_Command_Prefilter.h"

// Sample Code for utilizing the 'THIRD_ORDER_COMMAND_PREFILTER' ...
THIRD_ORDER_COMMAND_PREFILTER Cmd_Prefilter;

int idx = 0;
double T = 0.001; // Sample Interval (Time interval of internal interrupt)
double t = 0.0;
double cmd_pos = 0.0; // Command Signal (Before filtering)

double cmd_f[3];
double pos_f = 0.0, vel_f = 0.0, acc_f = 0.0;

/* Function Declaration */
double sign(double u_in);

/* Main Program */
void setup()
{
  Serial.begin(115200);

  double fc = 2.5;
  Cmd_Prefilter.Setup(fc, T);

  delay(3000);
}

void loop()
{
  t = (double)idx * T;
  cmd_pos = sign(sin(2.0 * PI / 5.0 * t));

  // Update the filtered command signals
  Cmd_Prefilter.Update(&cmd_pos, cmd_f);
  pos_f = cmd_f[0];
  vel_f = cmd_f[1];
  acc_f = cmd_f[2];

  Serial.print(String() + cmd_pos + " " + pos_f + " " + vel_f + " " + acc_f);
  Serial.println();
  Serial.flush();

  idx++;

  delay(1);
}

double sign(double u_in)
{
  if (u_in > 0.0)
    return 1.0;
  else if (u_in < 0.0)
    return -1.0;
  return 0.0;
}
