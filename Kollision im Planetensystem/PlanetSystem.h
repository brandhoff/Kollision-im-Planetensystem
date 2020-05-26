#pragma once
#include "Teilchen.h"
#include <vector>
#include "Bin.h"
class PlanetSystem
{
	public:
		std::vector<Teilchen> AlleTeilchen;
		PlanetSystem();
		PlanetSystem(double relGeschwindigkeit, double volumen, double q, std::vector<Bin> bin_list);
		std::vector<Teilchen> getAllTeilchenWithin(double min, double max);
		void collide(Teilchen partner1, Teilchen partner2);
};

