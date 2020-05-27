#include "PlanetSystem.h"
#include <vector>
#include "Bin.h"
//DIESE KLASSE WIRD GENUTZT UM MEHRERE SYSTEM GLEICHZEITIG ZU MODDELIEREN UND ZU CONFIGURIEREN

PlanetSystem::PlanetSystem(){
}

PlanetSystem::PlanetSystem(double relGeschwindigkeit, double volumen, double q, std::vector<Bin> bin_list){
}

/*
gets the total mass of the system. 
*/
double PlanetSystem::getTotalMass() {
	for (auto& x : this->bin_list) {

	}
	return 0.0;
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
	for(auto &x : this->bin_list)
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