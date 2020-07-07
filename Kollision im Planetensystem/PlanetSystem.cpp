#include "PlanetSystem.h"
#include <vector>
#include "Bin.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm> 
#include <vector>
//DIESE KLASSE WIRD GENUTZT UM MEHRERE SYSTEM GLEICHZEITIG ZU MODDELIEREN UND ZU KoNFIGURIEREN


std::ofstream fileKollisionsLebensdauer("Lebensdauer_singular.txt");
std::ofstream fileKollisionsrate("Kollisionsrate_singular.txt");
std::ofstream fileMassenverteilung("Massenverteilung_singular.txt");
std::ofstream fileZeitEntwicklung("Zeitentwicklung_singular.txt");
std::ofstream fileFragmenteVerteilung("Fragmente_singular.txt");


PlanetSystem::PlanetSystem(){
	this->relGeschwindigkeit = 0;
	this->volumen = 0;
	this->q = 0;
	this->dichte = 0;
		
}

PlanetSystem::PlanetSystem(double relGeschwindigkeit, double volumen, double q, double dichte, std::vector<Bin*> bin_list){
	this->relGeschwindigkeit = relGeschwindigkeit;
	this->volumen = volumen;
	this->q = q;
	this->dichte = dichte;
	this->bin_list = bin_list;
	this->wachstumBins.reserve(this->bin_list.size()); // gleiche laenge sicherstellen
	this->verluste.reserve(this->bin_list.size()); // gleiche laenge sicherstellen
	this->wachstumBins.resize(this->bin_list.size());
	this->verluste.resize(this->bin_list.size());

}




/*
gets the total mass of the system. 
*/
double PlanetSystem::getTotalMass() {
	double totalMass = 0.0;
	for (auto &x : this->bin_list) {
		double werte = x->massenWert * x->anzahl;
		totalMass += werte;	// Aufsummierung der Gesamtmassen der einzelnen Bins

	}
	return totalMass;
}

/*
verteilt die teilchen gemaess des potenzgesetzes fuer massen
im bereich start und end
*/
double PlanetSystem::scalingFactor(double m_min, double m_max, double gesMass) {
	return (gesMass) / (6.0 * pow(m_max, (1.0 / 6.0))- (6.0 * pow(m_min, (1.0 / 6.0))));
}


void PlanetSystem::singularVerteilung(double BinMassenWert, double gesMass) {
	int index = findNextBinIndexUnderMass(BinMassenWert);
	bin_list[index]->addAnzahlTeilchen(gesMass / BinMassenWert);
}

void PlanetSystem::potenzGesetztVerteilung(double start, double end, double gesMass, double dichte) {
	double restMasse = gesMass;
	int index = findNextBinIndexUnderMass(end);
	while (true) { // restMasse > 0.00001
		Bin* x = bin_list[index];
		Bin* unter = bin_list[index - 1];
		double oberMass;
		if (index + 1 < bin_list.size()) {
			oberMass = bin_list[index + 1]->massenWert;
		}
		else {
			oberMass = bin_list[index]->massenWert+unter->massenWert;
		}
		double anzahl = scalingFactor(start, end, gesMass)*(pow((oberMass-x->massenWert)-(x->massenWert-unter->massenWert), -5.0 / 6.0 ));
		x->addAnzahlTeilchen(anzahl);
		//std::cout << x->massenWert << "\t" << anzahl << std::endl;
		//fileMassenverteilungInitial << x->massenWert << "\t" << anzahl << std::endl;
		restMasse -= x->massenWert * anzahl;
		
		if (index > 1) {
			index--;
		}
		else break; // wird meistens nicht gecallt meistens bricht die masse ab
		
	}
}

/*
	findet das nachste Bin unterhalb (<=) der gegebenen masse
*/
Bin* PlanetSystem::findNextBinUnderMass(double mass) {
	Bin* aktuell = new Bin(mass, 0);
	for (auto& x : bin_list) {
		if (x->massenWert <= mass) {
			aktuell = x;
		}
	}
	return aktuell; 
}
/*
Findet den naechsten bin list index unterhalb (<=) der gegebenen masse
*/
int PlanetSystem::findNextBinIndexUnderMass(double mass) {
	int aktuell = 0;
	for (int i = 0; i < bin_list.size(); i++) {
		if (bin_list[i]->massenWert <= mass) {
			aktuell = i;
		}
		else {
			break;
		}
	}
	return aktuell; 
}




/*
berechnet L ij
*/
double PlanetSystem::lokaleKollision(int i, int j) {
	return M_PI* std::pow((this->bin_list[i]->getRadius(this->dichte) + this->bin_list[j]->getRadius(this->dichte)), 2)* relGeschwindigkeit / this->volumen * bin_list[j]->anzahl * bin_list[i]->anzahl;
}



/*
Berechnet die Kollisionsrate fuer die momentane konfiguration an Teilchen und derer Verteilung
*/
double PlanetSystem::calcKollisionsrate() {
	double kollision = 0.0;
		for (int j = 0; j < this->bin_list.size(); j++) {
			for (int k = 0; k < this->bin_list.size(); k++) {

				verluste[k] += this->bin_list[k]->anzahl * this->bin_list[j]->anzahl * lokaleKollision(k, j);
			}
		}
	
	
	return kollision;
}


/*
Berechent die Lebensdauer einer Kollision fuer die momentane konfiguration an Teilchen und derer Verteilung
*/
double PlanetSystem::calcKollisionsLebensdauer(int i) {

	return verluste[i]/this->bin_list[i]->massenWert;
}

/*
Berechnet alle Wachstumstherme
*/
void PlanetSystem::calcGewinnTerme() {
	double wachstum = 0.0;
	for (int j = 0; j < this->bin_list.size(); j++) {
		for (int k = 0; k < this->bin_list.size(); k++) {

			double neueMasse = bin_list[k]->massenWert + bin_list[j]->massenWert;
			int zielBinIndex = findNextBinIndexUnderMass(neueMasse);
			//Falls ins gleiche Bin gelegt wird
			if (zielBinIndex == k && zielBinIndex == j) {
				continue;
			}
			else if (zielBinIndex == k) {
				double NeueAnzahl = bin_list[j]->massenWert / bin_list[zielBinIndex]->massenWert;
				const double aux = 0.5 * lokaleKollision(j, k);
				this->verluste[j] += aux;
				this->wachstumBins[zielBinIndex] += aux * NeueAnzahl;
			}
			else if (zielBinIndex == j) {
				double NeueAnzahl = bin_list[k]->massenWert / bin_list[zielBinIndex]->massenWert;
				const double aux = 0.5 * lokaleKollision(j, k);
				this->verluste[k] += aux;
				this->wachstumBins[zielBinIndex] += aux * NeueAnzahl;
			}
			else {
				double NeueAnzahl = neueMasse / bin_list[zielBinIndex]->massenWert;
				const double aux = 0.5 * lokaleKollision(j, k);
				this->verluste[j] += aux;
				this->verluste[k] += aux;
				this->wachstumBins[zielBinIndex] += aux * NeueAnzahl;
			}
		}
	}
}




void PlanetSystem::calcALLLebensdauer() {
	for (int i = 0; i < bin_list.size(); i++) {

		double lebensDauer = calcKollisionsLebensdauer(i);
		fileKollisionsLebensdauer << lebensDauer;

		this->LebensdauerBin.push_back(lebensDauer);

	}
}


void PlanetSystem::VecReset() {
	this->wachstumBins.clear();
	this->verluste.clear();

	this->wachstumBins.reserve(this->bin_list.size()); // gleiche laenge sicherstellen
	this->wachstumBins.resize(this->bin_list.size());
	this->verluste.reserve(this->bin_list.size()); // gleiche laenge sicherstellen
	this->verluste.resize(this->bin_list.size());


}




void PlanetSystem::zeitEntwicklung(double Weite) {
	// 	double ZeitSchritt = 0.1 * Weite/this->relGeschwindigkeit;
	Weite = Weite * 365.25 * 86400;
	int vergangene_zeit = 0;
	std::vector<std::vector<double>> zeitverlauf;
	std::vector<double> aktuelleAnzahl;
	// 	ZeitSchritt = ZeitSchritt * 365.25 * 86400;
	while (Weite > 0) {
		//resetten der Vektoren kollisionsRaten und wachstumsBins
		this->VecReset();

		//beechnung der wachstumsraten fuer diesen Zeitschritt
		this->calcGewinnTerme();
		std::vector<double> schrittweiten;

		for (int i = 0; i < this->bin_list.size(); i++) {
			//Berechnung der Schrittweite
			if(bin_list[i]->anzahl != 0 && this->verluste[i] > this->wachstumBins[i])
			schrittweiten.push_back(bin_list[i]->anzahl / (this->verluste[i] - this->wachstumBins[i]));

		}
		double ZeitSchritt = 0.1 * *std::min_element(schrittweiten.begin(), schrittweiten.end());

		for (int i = 0; i < this->bin_list.size(); i++) {
			double aenderung = (this->wachstumBins[i] - this->verluste[i]) * ZeitSchritt;
			//Aenderung schreiben
			bin_list[i]->addAnzahlTeilchen(aenderung);
			aktuelleAnzahl.push_back(bin_list[i]->anzahl);
		}
		std::cout << " Gesamte masse des Systems: " << this->getTotalMass() << std::endl;
		zeitverlauf.push_back(aktuelleAnzahl);

		vergangene_zeit += ZeitSchritt;
		Weite -=ZeitSchritt;
		vergangene_zeit = vergangene_zeit / 365.25 * 86400;
	}
	for (int i = 0; i < zeitverlauf.size(); i++) {
		fileZeitEntwicklung << bin_list[i]->massenWert << '\t';
		for (int j = 0; j < zeitverlauf[i].size(); j++) {
			fileZeitEntwicklung << zeitverlauf[i][j] << '\t';
		}
		fileZeitEntwicklung << std::endl;
	}
}



void PlanetSystem::zerstKollision(int i, int j, int anzahlSkalierung){

	double Qcrit = this->q;
	double masse_i = bin_list[i]->massenWert;
	double masse_j = bin_list[j]->massenWert;

	double v = this->relGeschwindigkeit;

	if (v * v * 1.0 / 2.0 * masse_i * masse_j / (masse_i + masse_j) > Qcrit) {
		double anzahl = anzahlSkalierung * lokaleKollision(i, j);
		double neueMasse = (masse_i + masse_j) / anzahl;
		Bin* ziel = bin_list[findNextBinIndexUnderMass(neueMasse)];
		if (ziel != bin_list[i] && ziel != bin_list[j]) {
			ziel->addAnzahlTeilchen(anzahl);
			fileFragmenteVerteilung << ziel->massenWert << "\t" << anzahl << std::endl;
			bin_list[i]->addAnzahlTeilchen(-1);
			bin_list[j]->addAnzahlTeilchen(-1);

		}



	}

}

void PlanetSystem:: calcALLzerstKollision() {
	for (int i = 0; i < bin_list.size(); i++) {
		for (int k = 0; k < bin_list.size(); k++) {
			zerstKollision(i, k, 10);
		}
	}
}

