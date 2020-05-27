#include "PlanetSystem.h"
#include <vector>
#include "Bin.h"
#include "Teilchen.h"
//DIESE KLASSE WIRD GENUTZT UM MEHRERE SYSTEM GLEICHZEITIG ZU MODDELIEREN UND ZU KoNFIGURIEREN

PlanetSystem::PlanetSystem(){
}

PlanetSystem::PlanetSystem(double relGeschwindigkeit, double volumen, double q, double dichte, std::vector<Bin> bin_list){
}

/*
gets the total mass of the system. 
*/
double PlanetSystem::getTotalMass() {
	double totalMass = 0.0;
	for (auto &x : this->bin_list) {
		totalMass += x.getGesMasse();	// Aufsummierung der Gesamtmassen der einzelnen Bins
	}
	return totalMass;
}

std::vector<Teilchen> PlanetSystem::getAllTeilchenWithin(double min, double max){
	return std::vector<Teilchen>();
}

void PlanetSystem::collide(Teilchen partner1, Teilchen partner2){
}


/*
verteilt die teilchen gemaess des potenzgesetzes
TODO: implimentieren der teilchenanzahl und deren verteilung
*/
void PlanetSystem::potenzGesetztVerteilung() {
	Teilchen teilchen;
	for (auto &x : this->bin_list) {
		teilchen = Teilchen::Teilchen(x.massenWert, dichte, true);
		for (int i=0; i < pow(x.massenWert, - 11.0 / 6.0); i++) x.addTeilchen(teilchen); // befülle Bin mit n(m)^(-11/6) Teilchen
	}
}
/*
Verteilt die Teilchen singulaer
binNumber gibt das Bin an, welches mit Teilchen gefüllt werden soll

*/
void PlanetSystem::singularVerteilung(int binNumber) {
	Teilchen teilchen(bin_list[binNumber].massenWert, dichte, true);
	for (int i = 0; i < pow(bin_list[binNumber].massenWert, -11.0 / 6.0); i++) bin_list[binNumber].addTeilchen(teilchen);
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