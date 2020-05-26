#pragma once
#define M_PI       3.14159265358979323846   // pi

class Teilchen
{

public:
	double mass;
	double dichte;
	double radius;
	Teilchen(double radius, double dichte);
	double calcMass(double dichte, double radius);

};

