#include "Bin.h"

void Bin::addTeilchen(Teilchen teilchen){
	this->teilchen.push_back(teilchen);
}



void Bin::removeTeilchen(Teilchen teilchen) {
	for (auto& x : this->teilchen) {
		if (teilchen.equals(x)) {
			//this->teilchen.erase(x);
		}
	}
}
	double Bin::getGesMasse() {
		double mass = 0;
		for (auto& x : this->teilchen) {
			mass += x.mass;
		}
		return mass;
	}

