#include "Teilchen.h"
#include <math.h>


Teilchen::Teilchen(double radius, double dichte) {

	this->dichte = dichte;
	this->radius = radius;
	this->mass = calcMass(dichte, radius);


}

/*
calculates the mass of the teilchen using its radius and density
*/
double Teilchen::calcMass(double dichte, double radius) {
	return 4 / 3 * M_PI * pow(radius, 3);
}
/*
Checks weather teilchen are equal TODO implement logic
*/
bool Teilchen::equals(Teilchen teilchen) {
	return true;
}