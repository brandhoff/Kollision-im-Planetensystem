#pragma once
#include "Teilchen.h"
#include <vector>
#include "Bin.h"
#include <fstream>
class PlanetSystem
{
	public:
		std::vector<Bin*> bin_list;
		std::vector<double> kollisionsRaten;
		std::vector<double> wachstumBins;
		std::vector<double> LebensdauerBin;


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

		void singularVerteilung(double gesMass, double start, double end);
		double calcKollisionsrate(int i);
		double calcKollisionsLebensdauer(int i);
		double getTotalMass();
		void zeitEntwicklung(double weite);
		double lokaleKollision(int i, int j);
		double calcGewinnTerme();
		
		void zerstKollision(int i, int j, int anzahlFragmente);

		void calcALLGewinnTerme();
		void calcALLKollisionsrate();
		void calcALLLebensdauer();
		void calcALLzerstKollision();

		double findGelichgewicht();

	private:
		void emptyAllBins();
};

