#include "PlanetSystem.h"
#include <vector>
#include "Bin.h"
#include "Teilchen.h"
#include <iostream>
#include <fstream>
#include <cmath>
//DIESE KLASSE WIRD GENUTZT UM MEHRERE SYSTEM GLEICHZEITIG ZU MODDELIEREN UND ZU KoNFIGURIEREN

std::ofstream fileKollisionsLebensdauer("Lebensdauer.txt");
std::ofstream fileMassenverteilung("Massenverteilung.txt");


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
}




/*
gets the total mass of the system. 
*/
double PlanetSystem::getTotalMass() {
	double totalMass = 0.0;
	for (auto &x : this->bin_list) {
		double werte = x->massenWert;
		totalMass += werte;	// Aufsummierung der Gesamtmassen der einzelnen Bins

	}
	return totalMass;
}

std::vector<Teilchen> PlanetSystem::getAllTeilchenWithin(double min, double max){
	return std::vector<Teilchen>();
}

void PlanetSystem::collide(Teilchen partner1, Teilchen partner2){
}


/*
verteilt die teilchen gemaess des potenzgesetzes fuer massen
im bereich start und end
*/
double PlanetSystem::scalingFactor(double m_min, double m_max, double gesMass) {
	return (gesMass) / (6.0 * pow((m_max - m_min), (1.0 / 6.0)));
}
//Implementiert idee von gross zu kleinen massen
//TODO end stimmt nicht ganz wes werden alle 
void PlanetSystem::potenzGesetztVerteilung(double start, double end, double gesMass, double dichte) {
	double restMasse = gesMass;
	int index = findNextBinIndexUnderMass(end);
	while (true) { // restMasse > 0.00001
		Bin* x = bin_list[index];
		double anzahl = scalingFactor(start, end, gesMass)*pow(x->massenWert, -5.0 / 6.0 );
		x->addAnzahlTeilchen(anzahl);
		//std::cout << x->massenWert << "\t" << anzahl << std::endl;
		fileMassenverteilung << x->massenWert << "\t" << anzahl << std::endl;
		restMasse -= x->massenWert * anzahl;
		
		if (index > 0) {
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
	for (int i = 0; i <= bin_list.size(); i++) {
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
Verteilt die Teilchen singulaer
binNumber gibt das Bin an, welches mit Teilchen gefüllt werden soll

*/
void PlanetSystem::singularVerteilung(int binNumber, double gesMass, double start, double end) {
	double anzahl = (gesMass / (end - start)) * pow(bin_list[binNumber]->massenWert, -5.0 / 6.0); 
	bin_list[binNumber]->addAnzahlTeilchen(anzahl);
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
//TODO auf eine index lose version umsteigen
double PlanetSystem::calcKollisionsrate(int i) {
	double kollision = 0.0;
		for (int j = 0; j < this->bin_list.size(); j++) {
			kollision += this->bin_list[i]->anzahl * this->bin_list[j]->anzahl * lokaleKollision(i, j);
		}
	

	return kollision;
}


/*
Berechent die Lebensdauer einer Kollision fuer die momentane konfiguration an Teilchen und derer Verteilung
*/
double PlanetSystem::calcKollisionsLebensdauer(int i) {
	fileKollisionsLebensdauer << calcKollisionsrate(i) / this->bin_list[i]->massenWert << std::endl;
	return calcKollisionsrate(i)/this->bin_list[i]->massenWert;
}

/*

*/
double PlanetSystem::calcGewinnTerme(double i) {
	double wachstum = 0.0;
	for (int j = 0; j < this->bin_list.size(); j++) {
		for (int k = 0; k < this->bin_list.size(); k++) {

			double neueMasse = bin_list[i]->massenWert + bin_list[j]->massenWert;
			zielBinIndex = findNextBinIndexUnderMass(neueMasse);
			wachstum += lokaleKollision(i,j) * bin_list[i]->anzahl / bin_list[j]->anzahl * (bin_list[i]->massenWert / bin_list[j]->massenWert)

		}
	}

	return wachstum;
}



void PlanetSystem::zeitEntwicklung(double schritte, double time) {
	double aenderung = 0.0;
	
	time = time * 365.25*86400;
	while (time > 0) {


		for (int i = 0; i < this->bin_list.size(); i++) {
			aenderung += this->calcKollisionsrate(i) - this->calcGewinnTerme(i);
		}

		
		time = time - schritte;
		time / 365.25*86400;
	}
}


/*
leert alle Bins im System
*/
void PlanetSystem::emptyAllBins() {
	for (auto& x : this->bin_list) {

	}
}