
#include <Third_Order_Command_Prefilter.h>

// Parameters Set Up for Third-Order Command Prefilter
void THIRD_ORDER_COMMAND_PREFILTER::Setup(double Cutoff_Freq, double Sample_Interval)
{
    fc = Cutoff_Freq;
    dt = Sample_Interval;

    tau = 1.0 / (2.0 * PI * fc);    // Time Constant
    a[0] = 1.0 / (tau * tau * tau); // Coefficients
    a[1] = 3.0 / (tau * tau);
    a[2] = 3.0 / (tau);

    // Initial Conditions for Command Prefilter's States
    for (int i = 0; i < 3; i++)
    {
        xf[i] = 0.0;
        y[i] = 0.0;
        F[i] = 0.0;
    }
}

// Algorithm of Third-Order Command Prefilter
void THIRD_ORDER_COMMAND_PREFILTER::Update(double *Input_Sig, double *pos_f, double *vel_f, double *acc_f)
{
    // Command Input Signal
    r = *Input_Sig;

    // Model Equations
    F[0] = xf[1];
    F[1] = xf[2];
    F[2] = -a[0] * xf[0] - a[1] * xf[1] - a[2] * xf[2] + r;

    // State-space equations
    for (int i = 0; i < 3; i++)
    {
        y[i] = a[0] * xf[i]; // output equation
        xf[i] += dt * F[i];  // update (state) equation
    }

    // Filtered Postion, Velocity, and Acceleration Commands
    *pos_f = y[0];
    *vel_f = y[1];
    *acc_f = y[2];
}
