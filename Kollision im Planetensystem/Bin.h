#pragma once
#include <vector>
#include "Teilchen.h"
class Bin
{
public:
	Bin(double massenWert);	// Teilchen werden entsprechend ihrer Masse den Bins zugeordnet
	Bin(double massenWert, std::vector<Teilchen> teilchen);

	std::vector<Teilchen> teilchen;
	/*
	Is used to determin the specific interval used by this bin
	*/
	double massenWert;
	void addTeilchen(Teilchen teilchen);
	void removeTeilchen(Teilchen teilchen);
	double getGesMasse();
};

