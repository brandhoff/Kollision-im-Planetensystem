#include "PlanetSystem.h"
#include <vector>
#include "Bin.h"
//DIESE KLASSE WIRD GENUTZT UM MEHRERE SYSTEM GLEICHZEITIG ZU MODDELIEREN UND ZU KONFIGURIEREN

PlanetSystem::PlanetSystem(){
}

PlanetSystem::PlanetSystem(double relGeschwindigkeit, double volumen, double q, double dichte, std::vector<Bin> bin_list){
}

/*
gets the total mass of the system. 
*/
double PlanetSystem::getTotalMass() {
	double totalMass = 0;
	for (auto &x : this->bin_list) {
		totalMass += x.massenWert;
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
	Teilchen teilchen();		// geht nicht, wie Initialisierung von teilchen????
	for (auto &x : this->bin_list) {
		teilchen(x.massenWert, dichte, true);	// Importierung von dichte funktioniert nicht
		for (int i=0; i < pow(x.massenWert, -11.0 / 6.0); i++) x.addTeilchen(teilchen); // -11/6 für Massenverteilung
	}
}

/*
Verteilt die Teilchen singulaer
TODO: implimentieren der teilchenanzahl und deren verteilung

*/
void PlanetSystem::singularVerteilung() {


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