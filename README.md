# Command prefilter

```cpp
#include <Arduino.h>
#include <command_prefilter.h>

#define TASK_PERIOD_MICROS 10000

const double T = (double)(TASK_PERIOD_MICROS) / 1000000.0;
const double fc = 1.0;

CommandPrefilter cmd_filter;

double t = 0.0;
double y = 0.0;
double yf[3] = { 0.0 };

unsigned long t_enter;

double sign(const double& u_in)
{
	if (u_in > 0.0)
		return 1.0;
	else if (u_in < 0.0)
		return -1.0;
	return 0.0;
}

void task()
{
	static int idx;
	t = (double)(idx)*T;

	y = sign(sin(2.0 * PI / 5.0 * t));
	cmd_filter.update(y, yf[0], yf[1], yf[2]);

	Serial.print(y);
	Serial.print(" ");
	Serial.print(yf[0]);
	Serial.print(" ");
	Serial.println();

	idx++;
}



void setup()
{
	Serial.begin(115200);

	cmd_filter.init(fc, T);

	t_enter = micros();
}

void loop()
{
	if (micros() - t_enter >= TASK_PERIOD_MICROS)
	{
		t_enter = micros();

		task();
	}
}
```
