#include <map>
#include <iostream>
#include <string>

//Coste O(n*log n) en el número de ejercicios ya que es un bucle for de tamaño numEj y en cada iteración hacemos una operación de coste log numEj 
bool res() {
	int numEj;
	std::cin >> numEj; 
	if (numEj == 0) return false;
	std::string aux;
	std::getline(std::cin, aux);

	std::map<std::string, int> cals;
	while (numEj--) {
		std::string nom, calificacion;
		std::getline(std::cin, nom);
		std::getline(std::cin, calificacion);

		calificacion == "CORRECTO" ? ++cals[nom] : --cals[nom];
	}

	for (auto const& p : cals) {
		if (p.second != 0) std::cout << p.first << ", " << p.second << '\n';
	}
	std::cout << "---\n";

	return true;
}


int main() {
	while (res());
	return 0;
}