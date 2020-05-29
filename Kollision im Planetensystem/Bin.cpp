#include "Bin.h"
#include <iostream>

Bin::Bin(double massenWert) {
	this->massenWert = massenWert;

	

}

Bin::Bin(double massenWert, std::vector<Teilchen*> teilchen) {
	this->massenWert = massenWert;
	this->teilchenList = teilchen;
}

/**
addes the teilchen to the teilchen in this bin
*/
void Bin::addTeilchen(Teilchen *teilchen){
	this->teilchenList.push_back(teilchen);

}


/*
removes the specific teilchen from the teilchen in this bin
*/
void Bin::removeTeilchen(Teilchen teilchen) {
	//for (auto& x : this->teilchenList) {
		//if (teilchen.equals(x)) {
			//this->teilchen.erase(x);
		//}
	//}
}
/*
returns the sum of all masses from all teilchen
*/
	double Bin::getGesMasse() {
		double mass = 0.0;
		for (auto &x : this->teilchenList) {
			mass += x->mass;

		}
		if(mass > 0)
		std::cout << "masse die returnt wird : " << mass << std::endl;
		return mass;
	}

