﻿#include "PlanetSystem.h"
#include <vector>
#include "Bin.h"
#include "Teilchen.h"
#include <iostream>
#include <fstream>
#include <cmath>
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
	this->kollisionsRaten.reserve(this->bin_list.size()); // gleiche laenge sicherstellen
	this->wachstumBins.resize(this->bin_list.size());
	this->kollisionsRaten.resize(this->bin_list.size());

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

/*
Verteilt die Teilchen singulaer
binNumber gibt das Bin an, welches mit Teilchen gefüllt werden soll

*/
/*void PlanetSystem::singularVerteilung(double gesMass, double start, double end) {
	int end_index = findNextBinIndexUnderMass(end);
	int start_index = findNextBinIndexUnderMass(start);
	double anzahl_imGebiet = end_index - start_index;
	double masseProBin = gesMass / anzahl_imGebiet;
	
	std::cout << "anzahl im gebiet " << anzahl_imGebiet << std::endl;
	std::cout << "masseProBin im gebiet " << masseProBin << std::endl;

	for (int i = start_index; i <= end_index; i++) {
		double teilchen = masseProBin / bin_list[i]->massenWert;
		bin_list[i]->addAnzahlTeilchen(teilchen);
		std::cout << "Added " << teilchen << " To " << bin_list[i]->massenWert << std::endl;
		//fileMassenverteilungInitial << bin_list[i]->massenWert << "\t" << teilchen << std::endl;
	}

}*/

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
	return M_PI* std::pow((this->bin_list[i]->getRadius(this->dichte) + this->bin_list[j]->getRadius(this->dichte)), 2)* relGeschwindigkeit / this->volumen;
}



/*
Berechnet die Kollisionsrate fuer die momentane konfiguration an Teilchen und derer Verteilung
*/
double PlanetSystem::calcKollisionsrate() {
	double kollision = 0.0;
		for (int j = 0; j < this->bin_list.size(); j++) {
			for (int k = 0; k < this->bin_list.size(); k++) {

				kollisionsRaten[k] += this->bin_list[k]->anzahl * this->bin_list[j]->anzahl * lokaleKollision(k, j);
			}
		}
	
	
	return kollision;
}


/*
Berechent die Lebensdauer einer Kollision fuer die momentane konfiguration an Teilchen und derer Verteilung
*/
double PlanetSystem::calcKollisionsLebensdauer(int i) {

	return kollisionsRaten[i]/this->bin_list[i]->massenWert;
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
			if (zielBinIndex == k) {

			}
			else if (zielBinIndex == j) {

			}

			double NeueAnzahl = neueMasse / bin_list[zielBinIndex]->massenWert;
			//wachstum in den passenden Vector schreiben
			this->wachstumBins[zielBinIndex] += 0.5 * lokaleKollision(j, k) * (bin_list[j]->massenWert / bin_list[k]->massenWert) * NeueAnzahl;
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
	this->kollisionsRaten.clear();

	this->wachstumBins.reserve(this->bin_list.size()); // gleiche laenge sicherstellen
	this->wachstumBins.resize(this->bin_list.size());
	this->kollisionsRaten.reserve(this->bin_list.size()); // gleiche laenge sicherstellen
	this->kollisionsRaten.resize(this->bin_list.size());


}



void PlanetSystem::zeitEntwicklung(double Weite) {
	double ZeitSchritt = 0.1 * Weite/this->relGeschwindigkeit;
	Weite = Weite * 365.25*86400;
	int vergangene_zeit = 0;
	ZeitSchritt = ZeitSchritt * 365.25 * 86400;
	while (Weite > 0) {
		//resetten der Vektoren kollisionsRaten und wachstumsBins
		VecReset();

		//beechnung der wachstumsraten fuer diesen Zeitschritt
		calcGewinnTerme();
		calcKollisionsrate();
		for (int i = 0; i < this->bin_list.size(); i++) {
			double aenderung = (this->wachstumBins[i]- this->kollisionsRaten[i]) * ZeitSchritt;
			bin_list[i]->addAnzahlTeilchen(aenderung);
		}

		vergangene_zeit += ZeitSchritt;
		Weite -= ZeitSchritt;
		vergangene_zeit = vergangene_zeit / 365.25 * 86400;
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


double PlanetSystem::findGelichgewicht() {
	return 1.0;
}

/*
leert alle Bins im System
*/
void PlanetSystem::emptyAllBins() {
	for (auto& x : this->bin_list) {

	}
}