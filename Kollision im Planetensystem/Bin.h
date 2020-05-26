#pragma once
#include <vector>
#include "Teilchen.h"
class Bin
{
public:
	Bin(double bereich);
	Bin(double bereich, std::vector<Teilchen> teilchen);

	std::vector<Teilchen> teilchen;
	/*
	Is used to determin the specific interval used by this bin
	*/
	double bereich;
	void addTeilchen(Teilchen teilchen);
	void removeTeilchen(Teilchen teilchen);
	double getGesMasse();
};

