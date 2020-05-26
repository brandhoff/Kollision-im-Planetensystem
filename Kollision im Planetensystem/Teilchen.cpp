#include "Teilchen.h"
#include <math.h>

double calcMass(double dichte, double radius) {
	return 4 / 3 * M_PI * pow(radius, 3);
}