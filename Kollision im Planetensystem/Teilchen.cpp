#include "Teilchen.h"
#include <math.h>


Teilchen::Teilchen(double radius, double dichte) {

	this->dichte = dichte;
	this->radius = radius;
	this->mass = calcMass(dichte, radius);


}

double Teilchen::calcMass(double dichte, double radius) {
	return 4 / 3 * M_PI * pow(radius, 3);
}

bool Teilchen::equals(Teilchen teilchen) {

}