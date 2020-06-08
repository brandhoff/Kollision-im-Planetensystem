#pragma once
#include "Teilchen.h"
#include <vector>
#include "Bin.h"
class PlanetSystem
{
	public:
		std::vector<Bin*> bin_list;
		double relGeschwindigkeit;
		double volumen;
		double q;
		double dichte;

		PlanetSystem();
		PlanetSystem(double relGeschwindigkeit, double volumen, double q, double dichte, std::vector<Bin*> bin_list);
		
		
		std::vector<Teilchen> getAllTeilchenWithin(double min, double max);
		void collide(Teilchen partner1, Teilchen partner2);
		void potenzGesetztVerteilung(double start, double end, double gesMass, double dichte);
		Bin* findNextBinUnderMass(double mass);
		int findNextBinIndexUnderMass(double mass);

		void singularVerteilung(int binNumber, double gesMass, double start, double end);
		double calcKollisionsrate(int i);
		double calcKollisionsLebensdauer(int i);
		double getTotalMass();
		double lokalerGewinn(int j, int k, double factor);
		void zeitEntwicklung(int schritte, double time);
		double lokaleKollision(int i, int j);
		double calcGewinnTerme(double i);
	private:
		void emptyAllBins();
};

