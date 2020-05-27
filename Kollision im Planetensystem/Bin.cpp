#include "Bin.h"


Bin::Bin(double massenWert) {
	this->massenWert = massenWert;
}

Bin::Bin(double massenWert, std::vector<Teilchen> teilchen) {
	this->massenWert = massenWert;
	this->teilchen = teilchen;
}

/**
addes the teilchen to the teilchen in this bin
*/
void Bin::addTeilchen(Teilchen teilchen){
	this->teilchen.push_back(teilchen);
}


/*
removes the specific teilchen from the teilchen in this bin
*/
void Bin::removeTeilchen(Teilchen teilchen) {
	for (auto& x : this->teilchen) {
		if (teilchen.equals(x)) {
			//this->teilchen.erase(x);
		}
	}
}
/*
returns the sum of all masses from all teilchen
*/
	double Bin::getGesMasse() {
		double mass = 0;
		for (auto& x : this->teilchen) {
			mass += x.mass;
		}
		return mass;
	}

