#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int gesMasse;
double relGeschwindigkeit;
double q;
int sMin, sMax;
int dichte;
double volumen;

/*
liest alle fuer den Start benoetigten Werte aus einer Datei filename

*/
void readValuesFromFile(string filename, int &sMin, int &sMax, int &dichte, double& q, int &gesMasse, double &relGeschwindigkeit, double &volumen, int &gitterMax, int &schritte) {
//hsllo
}

/**
Erzeugt ein logarithmisches Gitter im Bereich min bis basis^max mit anzahl schritten. Basis gibt dabei die log scala an mit default=10
TODO: macht noch nicht ganz was wir wollen: in der main wird ein beispiel geprintet zu viele gleiche punkte was sinnlos ist.
*/
 vector<double> createLogSpace(int min, int max, int schritte, int basis=10) {
	 vector<double> logspace;
	 for (int i = 0; i < schritte; i++) {
		 logspace.push_back(pow(basis, i * (max - min) / (schritte - 1)));
	 }
	 return logspace;
}


 /*
 INITALIESIERUNG von variablen, einlesen der Daten
 */
 void INIT() {
	 int gitterMax;
	 int schritte;
	 readValuesFromFile("anfangswerte.txt", sMin, sMax, dichte, q, gesMasse, relGeschwindigkeit, volumen, gitterMax, schritte);

 }

/*
Main funktion zum code ausfuehren
*/
int main(int argc, char* argv[])
{
	//initialisieren
	INIT();

	for (auto& x : createLogSpace(1, 10, 100)) {
		cout << x << " ";
	};

	return 0;
}