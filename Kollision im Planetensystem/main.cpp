#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

#include <vector>
#include <string>
#include <cmath>

//Boost abhaegigkeiten
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>

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





 //--------------------------------------------------------------------------------------------------------------------------------------
 //------------------------------------------------  MATHE TOOLS ETC  -------------------------------------------------------------------
 //--------------------------------------------------------------------------------------------------------------------------------------

/**
Erzeugt ein logarithmisches Gitter im Bereich min bis basis^max mit anzahl schritten. Basis gibt dabei die log scala an mit default=10

*/
vector<double> createLogSpace(double min, double max, int schritte, double basis = 10) {
	vector<double> logspace;
	logspace.reserve(schritte);
	const auto exponent = (max - min) / (schritte - 1); // bastand zwischen zwei Punkten
	for (int i = 0; i < schritte; i++) {
		logspace.push_back(pow(basis, i * exponent));
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



	return 0;
}