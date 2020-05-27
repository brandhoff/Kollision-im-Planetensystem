#include "Teilchen.h"
#include <cmath>


Teilchen::Teilchen(double radius, double dichte) {

	this->dichte = dichte;
	this->radius = radius;
	this->mass = calcMass(dichte, radius);


}

/*
calculates the mass of the teilchen using its radius and density
*/
double Teilchen::calcMass(double dichte, double radius) {
	return 4.0 / 3.0 * M_PI * pow(radius, 3);
}
/*
Checks whether teilchen are equal TODO implement logic
*/
bool Teilchen::equals(Teilchen teilchen) {
	return true;
}