#include <Arduino.h>
#include "Third_Order_Command_Prefilter.h"

// Sample Code for utilizing the 'THIRD_ORDER_COMMAND_PREFILTER' ...
THIRD_ORDER_COMMAND_PREFILTER Cmd_Prefilter;

double dt = 0.001; // Sample Interval (Time interval of internal interrupt)
double r = 0.0;    // Command Signal (Before filtering)
double t = 0.0;
int idx = 0;

double pos_f = 0.0, vel_f = 0.0, acc_f = 0.0;

double sign(double u_in);

void setup()
{
    Serial.begin(115200);

    double fc = 0.75;
    Cmd_Prefilter.Setup(fc, dt);

    delay(3000);
}

void loop()
{
    t = (double)idx * dt;
    r = sign(sin(2.0 * PI / 5.0 * t));

    // Update the filtered command signals
    Cmd_Prefilter.Update(&r, &pos_f, &vel_f, &acc_f);

    Serial.flush();
    Serial.print(r, 4);
    Serial.print(" ");
    Serial.print(pos_f, 4);
    Serial.print(" ");
    Serial.print(vel_f, 4);
    Serial.print(" ");
    Serial.print(acc_f, 4);
    Serial.print("\n");

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