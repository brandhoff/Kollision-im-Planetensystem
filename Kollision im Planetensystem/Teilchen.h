#pragma once
#define M_PI       3.14159265358979323846   // pi

class Teilchen
{

public:
	double mass;
	double dichte;
	double radius;
	Teilchen(double radius, double dichte);
	Teilchen(double mass, double dichte, bool withMass); // bool withMass zur Unterscheidung der Signatur der Konstruktoren
	double calcMass(double dichte, double radius);
	double calcRadius(double dichte, double mass);
	bool equals(Teilchen teilchen);
};

