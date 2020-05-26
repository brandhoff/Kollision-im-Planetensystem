#include "Bin.h"

void Bin::addTeilchen(Teilchen teilchen){
	this->teilchen.push_back(teilchen);
}

void Bin::removeTeilchen(Teilchen teilchen){
	for (auto& x : this->teilchen) {
		if (teilchen.equals(x)) {

		}
	}
}
