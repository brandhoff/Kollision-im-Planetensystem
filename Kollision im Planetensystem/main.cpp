#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

#include <vector>
#include <string>
#include <cmath>
using namespace std;

int gesMasse;
double relGeschwindigkeit;
double q;
int sMin, sMax;
int dichte;
double volumen;

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
		if (pos != std::string::npos) {
			stringstream iss;
			output = (line.substr(pos + key.size()));
			break;
		}
	}
	return output;
}

/*
liest alle fuer den Start benoetigten Werte aus einer Datei filename

*/
void readValuesFromFile(string filename, int &sMin, int &sMax, int &dichte, double& q, int &gesMasse, double &relGeschwindigkeit, double &volumen, int &gitterMax, int &schritte) {



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
	 int gitterMax;
	 int schritte;
	 readValuesFromFile("anfangswerte.txt", sMin, sMax, dichte, q, gesMasse, relGeschwindigkeit, volumen, gitterMax, schritte);
	 //vector<double> logspace = createLogSpace(0, gitterMax, schritte);

	 cout << readValueFromKey("C:\\Users\\hi84qur\\source\\repos\\Kollision im Planetensystem\\Kollision im Planetensystem\\anfagswerte.txt","gitterMax:") << " ";
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