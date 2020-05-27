#pragma once
#include "Teilchen.h"
#include <vector>
#include "Bin.h"
class PlanetSystem
{
	public:
		std::vector<Bin> bin_list;
		double relGeschwindigkeit;
		double volumen;
		double q;
		double dichte;

		PlanetSystem();
		PlanetSystem(double relGeschwindigkeit, double volumen, double q, double dichte, std::vector<Bin> bin_list);
		std::vector<Teilchen> getAllTeilchenWithin(double min, double max);
		void collide(Teilchen partner1, Teilchen partner2);
		void potenzGesetztVerteilung();
		void singularVerteilung();
		double calcKollisionsrate();
		double calcKollisionsLebensdauer();
		double getTotalMass();
};

