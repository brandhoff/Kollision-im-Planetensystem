#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

#include <vector>
#include <string>
#include <cmath>

#include "Bin.h"
#include "PlanetSystem.h"
#include "Teilchen.h"
#define M_PI       3.14159265358979323846   // pi

using namespace std;

double gesMasse;
double relGeschwindigkeit;
double q;
double sMin, sMax;
double dichte;
double volumen;
/*
gibt den absolut pfad zur config datei, in der die startwerte gespeichert sind an.
*/
const string config_filename = "anfagswerte.txt";
PlanetSystem* main_system;





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
	try{
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
	catch (const std::invalid_argument& ia) {
		cerr << "Konvertierungsfehler " << ia.what() << std::endl;

	}
	
}





 //--------------------------------------------------------------------------------------------------------------------------------------
 //------------------------------------------------  MATHE TOOLS ETC  -------------------------------------------------------------------
 //--------------------------------------------------------------------------------------------------------------------------------------
/*
returns the log to base basis of x
*/
double log_basis(double basis, double x) {
	if (basis <= 0 || x <= 0) {
		cout << "Negative logarithmen sind nicht gut";
		cin;
	}
		
	return (log(x) / log(basis));
}


/**
Erzeugt ein logarithmisches Gitter im Bereich min bis basis^max mit anzahl schritten. Basis gibt dabei die log scala an mit default=10

*/
vector<double> createLogSpace(double min, double max, int schritte, double basis = 10) {
	vector<double> logspace;
	logspace.reserve(schritte);
	double sc = schritte;
	double exponent = (max - min) / (sc - 1); // Abastand zwischen zwei Punkten
	for (int i = 0; i < schritte; i++) {
		logspace.push_back(pow(basis, i * exponent + log_basis(basis, min)));
	}
	return logspace;
}


 /*
 Bildet die Ableitung einer Funktion an der stelle x mit schrittweite dx. Die ableitung konvergiert in 6.Ordnung 
 */
template<typename function_type>
 double derivative(double x, float dx, function_type funktion)
 {
	 const double dx1 = dx;
	 const double dx2 = dx1 * 2;
	 const double dx3 = dx1 * 3;

	 const double m1 = (funktion(x + dx1) - funktion(x - dx1)) / 2;
	 const double m2 = (funktion(x + dx2) - funktion(x - dx2)) / 4;
	 const double m3 = (funktion(x + dx3) - funktion(x - dx3)) / 6;

	 const double fifteen_m1 = 15 * m1;
	 const double six_m2 = 6 * m2;
	 const double ten_dx1 = 10 * dx1;

	 return ((fifteen_m1 - six_m2) + m3) / ten_dx1;
 }

 /*converts a radius to a mass given a dichte*/
 double radiusToMass(double r, double dichte) {
	 return 4.0 / 3.0 * M_PI * pow(r, 3) * dichte;
 }

 /*converts a mass to a radius given a dichte*/
  double massToRadius(double mass, double dichte) {
	 return pow(mass * (3.0 / 4.0) * (1 / M_PI) * (1 / dichte), 1.0 / 3.0);
 }


 /*
 INITALIESIERUNG von variablen, einlesen der Daten

 */
 void INIT() {
	 double gitterMax = 0;
	 double schritte = 0;
	 sMin = 0;
	 readValuesFromFile(config_filename, sMin, sMax, dichte, q, gesMasse, relGeschwindigkeit, volumen, gitterMax, schritte);
	
	 vector<double> gitter = createLogSpace(sMin, gitterMax, schritte*20);
	 vector<Bin*> bins;
	 for (auto &x : gitter) {
		
		 Bin* bin =  new Bin(x, 0); // in Bin wird der massenWert gespeichert dem später Teilchen zugeordnet werden
		 bins.push_back(bin);
	 }

	 //create the main PlanetSystem
	 main_system = new PlanetSystem(relGeschwindigkeit, volumen, q, dichte, bins);
 }

/*
Main funktion zum code ausfuehren
*/
int main(int argc, char* argv[])
{
	//initialisieren
	INIT();

	//ruft die gewuenschte verteilung im system auf
	main_system->potenzGesetztVerteilung(radiusToMass(sMin, dichte), radiusToMass(sMax, dichte), gesMasse, dichte);
	cout << " Gesamte masse des Systems: " << main_system->getTotalMass() << endl;
	

	
	return 0;
}