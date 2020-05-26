#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

#include <vector>
#include <string>
#include <cmath>
using namespace std;

double gesMasse;
double relGeschwindigkeit;
double q;
double sMin, sMax;
double dichte;
double volumen;
/*
gibt den absolut pfad zur config datei, in der die strat werte gespeichert sind an.
*/
const string config_filename = "C:\\Users\\hi84qur\\source\\repos\\Kollision im Planetensystem\\Kollision im Planetensystem\\anfagswerte.txt";






/*
	sucht in der gegebenen Datei nach einem keyWort und liest den dazugehoerigen Wert aus. Der Wert wird als string returnt
*/
string readValueFromKey(string filename, string key) {
	ifstream inputFile;
	string line;
	inputFile.open(filename);
	string output;
	while (getline(inputFile, line)) {
		auto pos = line.find(key);
		if (pos != std::string::npos) { //linie gefunden und ist nicht leer position
			stringstream iss;
			output = (line.substr(pos + key.size())); //substring zwischen key und value bilden und als output nehmen
			break;
		}
	}
	return output;
}

/*
liest alle fuer den Start benoetigten Werte aus einer Datei, wobei die keys fuer die values festgelegt sind

*/
void readValuesFromFile(string filename, double &sMin, double&sMax, double&dichte, double& q, double&gesMasse, double &relGeschwindigkeit, double &volumen, double&gitterMax, double&schritte) {

	sMin = stod(readValueFromKey(filename, "sMin:"));
	sMax = stod(readValueFromKey(filename, "sMax:"));
	dichte = stod(readValueFromKey(filename, "dichte:"));
	q = stod(readValueFromKey(filename, "qini:"));
	gesMasse = stod(readValueFromKey(filename, "Mges:"));
	relGeschwindigkeit = stod(readValueFromKey(filename, "vrel:"));
	volumen = stod(readValueFromKey(filename, "volumen:"));
	gitterMax = stod(readValueFromKey(filename, "gitterMax:"));
	schritte = stod(readValueFromKey(filename, "schritte:"));
}


/**
Erzeugt ein logarithmisches Gitter im Bereich min bis basis^max mit anzahl schritten. Basis gibt dabei die log scala an mit default=10

*/
 vector<double> createLogSpace(double min, double max, int schritte, double basis=10) {
	 vector<double> logspace;
	 logspace.reserve(schritte);
	 const auto exponent = (max - min) / (schritte-1); // bastand zwischen zwei Punkten
	 for (int i = 0; i < schritte; i++) {
		 logspace.push_back(pow(basis, i * exponent));
	 }
	 return logspace;
}


 /*
 INITALIESIERUNG von variablen, einlesen der Daten
 */
 void INIT() {
	 double gitterMax;
	 double schritte;
	 readValuesFromFile(config_filename, sMin, sMax, dichte, q, gesMasse, relGeschwindigkeit, volumen, gitterMax, schritte);
	
 }

/*
Main funktion zum code ausfuehren
*/
int main(int argc, char* argv[])
{
	//initialisieren
	INIT();

	for (auto& x : createLogSpace(2, 10, 100)) {
	//	cout << x << " ";
	};

	return 0;
}