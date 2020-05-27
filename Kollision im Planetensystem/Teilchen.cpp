#include "Teilchen.h"
#include <cmath>


Teilchen::Teilchen(){}

Teilchen::Teilchen(double radius, double dichte) {

	this->dichte = dichte;
	this->radius = radius;
	this->mass = calcMass(dichte, radius);
}

Teilchen::Teilchen(double mass, double dichte, bool withMass) {
	
	this->dichte = dichte;
	this->mass = mass;
	this->radius = calcRadius(dichte, mass);
}

/*
calculates the mass of the teilchen using its radius and density
*/
double Teilchen::calcMass(double dichte, double radius) {
	return 4.0 / 3.0 * M_PI * pow(radius, 3);
}

/*
calculates the radius of the teilchen using its mass and density
*/
double Teilchen::calcRadius(double dichte, double mass) {
	return pow(3.0 / (4.0 * M_PI) * mass, 1.0 / 3.0);
}

/*
Checks whether teilchen are equal TODO implement logic
*/
bool Teilchen::equals(Teilchen teilchen) {

	return true;
}