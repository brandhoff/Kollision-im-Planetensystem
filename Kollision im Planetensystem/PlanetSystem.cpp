#include "PlanetSystem.h"
#include <vector>
#include "Bin.h"
#include "Teilchen.h"
#include <iostream>
#include <fstream>
//DIESE KLASSE WIRD GENUTZT UM MEHRERE SYSTEM GLEICHZEITIG ZU MODDELIEREN UND ZU KoNFIGURIEREN

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
		
		totalMass += x->getGesMasse();	// Aufsummierung der Gesamtmassen der einzelnen Bins
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


double sclaingFactor(double m_min, double m_max, double gesMass) {
	return (gesMass) / (6 * pow((m_max - m_min), (1 / 6)));
}
//Implementiert idee von gross zu kleinen massen
//TODO end stimmt nicht ganz wes werden alle 
void PlanetSystem::potenzGesetztVerteilung(double start, double end, double gesMass, double dichte) {
	double restMasse = gesMass;
	int index = findNextBinIndexUnderMass(end);
	std::ofstream ofs("Massenverteilung.txt");
	while (restMasse > 0.001) {
		Bin* x = bin_list[index];
		double anzahl = sclaingFactor(start,end,gesMass)*pow(x->massenWert, -5.0 / 6.0 );
		x->addAnzahlTeilchen(anzahl);
		std::cout << "added " << anzahl << " Teilchen mit masse " << x->massenWert << std::endl;
		ofs << x->massenWert << "\t" << anzahl << std::endl;
		restMasse -= x->massenWert * anzahl;
		
		if (index > 0) {
			index--;
		}
		else break;
	}
	ofs.close();
}

/*
	findet das nachste Bin unterhalb (<=) der gegebenen masse
	might return a NullPointer  nullCheck first
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
			std::cout << "abbruch bei masse von " << mass << " untersuchtes bin: " << bin_list[aktuell]->massenWert;
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
//TODO multi ist schneller als potenz
double PlanetSystem::lokaleKollision(int i, int j) {
	return M_PI* std::pow((this->bin_list[i]->getRadius(this->dichte) + this->bin_list[j]->getRadius(this->dichte)), 2)* relGeschwindigkeit / this->volumen;
}

/*
beschreibt wie viele Teilchen bei einer kollision von j und k an der stelle i entstehen

*/
double PlanetSystem::lokalerGewinn(int i, int j, int k) {

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

	return calcKollisionsrate(i)/this->bin_list[i]->massenWert;
}

/*
*/
double PlanetSystem::calcGewinnTerme(double i) {
	double gewinn = 0.0;
	for (int j = 0; j < this->bin_list.size(); j++) {
		for (int k = 0; k < this->bin_list.size(); k++) {
			gewinn += this->bin_list[k]->anzahl * this->bin_list[j]->anzahl;
		}
	}
}

/*
leert alle Bins im System
*/
void PlanetSystem::emptyAllBins() {
	for (auto& x : this->bin_list) {

	}
}