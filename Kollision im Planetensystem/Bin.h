#pragma once
#include <vector>
#include "Teilchen.h"
class Bin
{
public:
	Bin(double massenWert,double anzahl);	// Teilchen werden entsprechend ihrer Masse den Bins zugeordnet
	double anzahl;

	/*
	wenn man nicht gerade 10^11 teilchen in ein bin schmeissen wuerde, waere das auch kein problem
	aber ab jetzt verwenden wir lieber zahl der teilchen als zahl und nicht als anzahl von instanzen eines objektes
	das ist ungesund
	*/
	std::vector<Teilchen*> teilchenList;
	/*
	Is used to determin the specific interval used by this bin
	*/
	double massenWert;
	void addTeilchen(Teilchen* teilchen);
	void removeTeilchen(double anzahl);
	double getGesMasse();

	double getRadius(double dichte);
	void addAnzahlTeilchen(double anzahl);
};

