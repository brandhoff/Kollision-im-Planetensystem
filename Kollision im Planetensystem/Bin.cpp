#include "Bin.h"
#include <iostream>

Bin::Bin(double massenWert,long int anzahl) {
	this->massenWert = massenWert;
	this->anzahl = anzahl;
}



/**
addes the teilchen to the teilchen in this bin
*/
[[deprecated("verwendet nurnoch die anzahl der teilchen als zahl und nicht als vector aus teilchen")]]
void Bin::addTeilchen(Teilchen *teilchen){
	this->teilchenList.push_back(teilchen);

}

void Bin::addAnzahlTeilchen(long int anzahl) {
	this->anzahl += anzahl;
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
		double masse = this->massenWert;
		int anzahl = this->anzahl;
		if(anzahl != 0){
			std::cout << " call der ges masse mit masse in Bin :" << masse << std::endl;
			return masse * anzahl;
		}
		return 0.0;
		
	}

