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
std::ofstream filevor("nach500kEntwicklung.txt");
std::ofstream filenach500k("nach500kEntwicklung.txt");
std::ofstream filenach1mio("nach1mioEntwicklung.txt");

/*
gibt den absolut pfad zur config datei, in der die startwerte gespeichert sind an.
*/
const string config_filename = "anfagswerte.txt";

const string smallSystemFilename = "smallSystem.txt";

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
	double exponent = (log_basis(basis,max) - log_basis(basis, min)) / (sc - 1); // Abastand zwischen zwei Punkten
	for (int i = 0; i < schritte; i++) {
		double wert = pow(basis, i * exponent + log_basis(basis, min));

		logspace.push_back(wert);
	}
	return logspace;
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

	readValuesFromFile(smallSystemFilename, sMin, sMax, dichte, q, gesMasse, relGeschwindigkeit, volumen, gitterMax, schritte);
	

	 vector<double> gitter = createLogSpace(sMin, gitterMax, schritte);
	 vector<Bin*> bins;
	 for (auto &x : gitter) {
		
		 Bin* bin =  new Bin(radiusToMass(x, dichte), 0);
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
//	cout << " Gesamte masse des Systems: " << main_system->getTotalMass() << endl;


	
	main_system->singularVerteilung(gesMasse, radiusToMass(sMin, dichte), radiusToMass(sMax, dichte));
	cout << " Gesamte masse des Systems: " << main_system->getTotalMass() << endl;
	
	main_system->calcALLKollisionsrate();
	main_system->calcALLLebensdauer();
	main_system->calcALLGewinnTerme();
	main_system->zeitEntwicklung(500000);

	for (auto bin : main_system->bin_list) {
		cout << "Bin masse " << bin->anzahl * bin->massenWert << endl;
		filenach500k << bin->massenWert << "\t" << bin->anzahl * bin->massenWert << std::endl;

	}
	cout << " Gesamte masse des Systems: " << main_system->getTotalMass() << endl;
	return 0;
}