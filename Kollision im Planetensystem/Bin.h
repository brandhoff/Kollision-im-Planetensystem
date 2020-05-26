#pragma once
#include <vector>
#include "Teilchen.h"
class Bin
{
public:
	std::vector<Teilchen> teilchen;
	double address;
	void addTeilchen(Teilchen teilchen);
	void removeTeilchen(Teilchen teilchen);
	double getGesMasse();
};

