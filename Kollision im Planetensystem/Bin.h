#pragma once
#include <vector>
#define M_PI       3.14159265358979323846   // pi
class Bin
{
public:
	Bin(double massenWert,double anzahl);	// Teilchen werden entsprechend ihrer Masse den Bins zugeordnet
	double anzahl;
		
	/*
	Is used to determin the specific interval used by this bin
	*/
	double massenWert;

	void removeTeilchen(double anzahl);
	double getGesMasse();
	double getRadius(double dichte);
	void addAnzahlTeilchen(double anzahl);
};

