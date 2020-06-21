#pragma once
#include "Teilchen.h"
#include <vector>
#include "Bin.h"
class PlanetSystem
{
	public:
		std::vector<Bin*> bin_list;
		std::vector<double> kollisionsRaten;
		std::vector<double> wachstumBins;


		double relGeschwindigkeit;
		double volumen;
		double q;
		double dichte;




		PlanetSystem();
		PlanetSystem(double relGeschwindigkeit, double volumen, double q, double dichte, std::vector<Bin*> bin_list);
		
		double scalingFactor(double m_min, double m_max, double gesMass);



		void potenzGesetztVerteilung(double start, double end, double gesMass, double dichte);
		Bin* findNextBinUnderMass(double mass);
		int findNextBinIndexUnderMass(double mass);

		void singularVerteilung(int binNumber, double gesMass, double start, double end);
		double calcKollisionsrate(int i);
		double calcKollisionsLebensdauer(int i);
		double getTotalMass();
		void zeitEntwicklung(double schritte, double time);
		double lokaleKollision(int i, int j);
		double calcGewinnTerme(double i);
		
		void zerstKollision(int i, int j, int anzahlFragmente);

		void calcALLGewinnTerme();
		void calcALLKollisionsrate();

		double findGelichgewicht();

	private:
		void emptyAllBins();
};

