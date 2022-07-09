#pragma once

// Algorithm of Command Prefilter (Third-Order)
// 2021-02-27 結構變數版本
// 2021-10-06 class 版本

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

class THIRD_ORDER_COMMAND_PREFILTER
{
public:
    void Setup(double Cutoff_Freq, double Sample_Interval);
    void Update(double *Input_Sig, double *pos_f, double *vel_f, double *acc_f);
    void Update(double *Input_Sig, double *Filtered_Sig)
    {
        Update(Input_Sig, &Filtered_Sig[0], &Filtered_Sig[1], &Filtered_Sig[2]);
    }

private:
    double T;                 // Sample Interval
    double fc;                // Cut-off frequency
    double tau;               // Time constant
    double a[3];              // Coefficient Array
    double r;                 // Filter Input
    double xf[3], F[3], y[3]; // States, ODEs, Outputs.
};