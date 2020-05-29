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
	//this->bin_list = new std::vector<Bin>();
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
		totalMass = totalMass + x->getGesMasse();	// Aufsummierung der Gesamtmassen der einzelnen Bins
		if(x->getGesMasse() >0)
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

			} // bef�lle Bin mit n(m)^(-11/6) Teilchen}

		}
	}
}
//PROBLEM ZU GROSSE MENGEN -> WEIL SCHIRTTE NICHT GUT UND MUSS NEXT BIN NEHMEN
void PlanetSystem::potenzGesetztVerteilung(double start, double end, double gesMass, double dichte) {
	double vergebene_Masse = 0;
	int i = 0;
	while (vergebene_Masse < gesMass) {
		Bin* x = bin_list[i];
		double anzahl = 0;
		while (anzahl < pow(x->massenWert, -11.0 / 6.0)) {

			x->addTeilchen(new Teilchen(x->massenWert, dichte, true));
			vergebene_Masse += x->massenWert;
			std::cout << " added a teilchen with mass: " << x->massenWert << std::endl;

			anzahl++;
		}
		i++;
	}
	std::cout << this->bin_list.size();
	



}

/*
Verteilt die Teilchen singulaer
binNumber gibt das Bin an, welches mit Teilchen gef�llt werden soll

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