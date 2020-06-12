#include "Bin.h"
#include <iostream>

Bin::Bin(double massenWert, double anzahl) {
	
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

void Bin::addAnzahlTeilchen(double anzahl) {
	this->anzahl += anzahl;
}

/*
removes the specific teilchen from the teilchen in this bin
*/
void Bin::removeTeilchen(double anzahl) {
	this->anzahl -= anzahl;
}

/*
returns the sum of all masses from all teilchen
*/
double Bin::getGesMasse() {
	double masse = this->massenWert;
	int anzahl = this->anzahl;
	if(anzahl != 0){
		return masse * anzahl;
	}
	return 0.0;	
}

double Bin::getRadius(double dichte) {
	return pow(this->massenWert * (3.0 / 4.0) * (1 / M_PI) * (1 / dichte), 1.0 / 3.0);
}