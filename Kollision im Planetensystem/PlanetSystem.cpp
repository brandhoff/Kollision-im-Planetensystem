#include "PlanetSystem.h"
#include <vector>
#include "Bin.h"
#include "Teilchen.h"
#include <iostream>
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
	double totalMass = 1.0;
	for (auto &x : this->bin_list) {
		totalMass += x->getGesMasse();	// Aufsummierung der Gesamtmassen der einzelnen Bins

		if(x->getGesMasse() > 0)
		std::cout << "total mass jetzt: " << totalMass << std::endl;
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

//TODO DER MUSS NEU GESCHRIEBEN WERDEN DAS IST NONSENS WAS PASSIERT --> zu wenig bins im bereich fuehrt dazu dass zu wenig teilchen gefuellt 
//werden und so nur ein oder zwei teilchen mit masse 1 oder weniger in dem Bereich landen. moeglicher fix: mehr bins-> mehr rechnung mehr gitter doof; 
//anderer fix teilchen in intervallen zu bins zuordnen, dafuer 1D abstaende zsischen benachbarten bins anschauen

//WEITERER LOGIK FEHLER: problem teilchen anzahl wird nicht erhoeht wenn dann wird immer nur ein teilchen mit anderer masse hinzugefuegt was bedeutetnd anders ist als teilchenanzahl
void PlanetSystem::potenzGesetztVerteilung(double start, double end) {
	for (auto &x : this->bin_list) {
		if (end < x->massenWert) continue;
		if (start < x->massenWert) {
			for (double i = 0; i < pow(x->massenWert, -11.0 / 6.0); i++) {
				//x.addTeilchen(Teilchen::Teilchen(x.massenWert, dichte, true));
				//std::cout << "added teilchen mass: " << x.massenWert;

			} // befülle Bin mit n(m)^(-11/6) Teilchen}

		}
	}
}
//Implementiert idee von gross zu kleinen massen
//TODO end stimmt nicht ganz wes werden alle 
void PlanetSystem::potenzGesetztVerteilung(double start, double end, double gesMass, double dichte) {
	double restMasse = gesMass;
	int index = findNextBinIndexUnderMass(restMasse);
	while (restMasse > 0.001) {
		Bin* x = bin_list[index];
		double anzahl = 0;
		while (anzahl < 20*pow(x->massenWert, -11.0 / 6.0)) {

			x->addTeilchen(new Teilchen(x->massenWert, dichte, true));
			restMasse -= x->massenWert;
			std::cout << " added a teilchen with mass: " << x->massenWert << std::endl;
			anzahl++;
		}
		if (index > 0) {
			index--;
		}
		else break;
	}

}

/*
	findet das nachste Bin unterhalb (<=) der gegebenen masse
	might return a NullPointer  nullCheck first
*/
Bin* PlanetSystem::findNextBinUnderMass(double mass) {
	Bin* aktuell = new Bin(mass);
	for (auto& x : bin_list) {
		if (x->massenWert <= mass) {
			aktuell = x;
		}
	}
	return aktuell; // Might return a nullPointer. 
}
/*
Findet den naechsten bin list index unterhalb (<=) der gegebenen masse
*/
int PlanetSystem::findNextBinIndexUnderMass(double mass) {
	int aktuell;
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
void PlanetSystem::singularVerteilung(int binNumber) {
	
}

/*
Berechnet die Kollisionsrate fuer die momentane konfiguration an Teilchen und derer Verteilung
*/
double PlanetSystem::calcKollisionsrate() {

	return 0.0;
}

/*
Berechent die Lebensdauer einer Kollision fuer die momentane konfiguration an Teilchen und derer Verteilung
*/
double PlanetSystem::calcKollisionsLebensdauer() {

	return 0.0;
}


/*
leert alle Bins im System
*/
void PlanetSystem::emptyAllBins() {
	for (auto& x : this->bin_list) {

	}
}