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
Erzeugt ein logarithmisches Gitter im Bereich min bis max mit schritte als diskreten abstand
*/
 vector<int> createLogSpace(int min, int max, int schritte) {

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


	return 0;
}