#pragma once
#define M_PI       3.14159265358979323846   // pi

class Teilchen
{

public:
	double radius, mass, dichte;

	Teilchen(double radius, double dichte) {
		this->radius = radius;
		this->dichte = dichte;
		this->mass = 0;
		//this->mass = calcMass(dichte, radius);
	}

};

