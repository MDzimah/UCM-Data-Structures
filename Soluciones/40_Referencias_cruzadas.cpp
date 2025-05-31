#include <map>
#include <iostream>
#include <string>
#include <vector>

//Coste O(n*log n) en el número de ejercicios ya que es un bucle for de tamaño numLin y en cada iteración hacemos una operación de coste log numLin 

void lowerCaseString(std::string& s) {
	for (char& c : s) {
		c = std::tolower(c);
	}
}

void insertarEnAlfabeto(std::map<std::string, std::vector<int>>& alf, std::string& aux1, int i) {
	if (aux1.size() > 2) {
		lowerCaseString(aux1);
		auto it = alf.find(aux1);
		if (it != alf.end()) {
			if (it->second.empty() || it->second[it->second.size() - 1] != i) it->second.push_back(i);
		}
		else {
			std::vector<int> v;
			v.push_back(i);
			alf.insert({ aux1,v });
		}
	}
}

bool res() {
	int numLin;
	std::cin >> numLin;
	if (numLin == 0) return false;

	std::map<std::string, std::vector<int>> alf;

	for (int i = 1; i <= numLin; ++i) {
		std::string aux1; char aux;

		std::cin >> aux1;
		std::cin.get(aux);
		while (aux != '\n') {
			insertarEnAlfabeto(alf, aux1, i);
			std::cin >> aux1;
			std::cin.get(aux);
		}
		insertarEnAlfabeto(alf, aux1, i);
	}

	for (auto const& p : alf) {
		std::cout << p.first;
		for (int i : p.second)
			std::cout << ' ' << i;
		std::cout << '\n';
	}
	std::cout << "---\n";

	return true;
}


int main() {
	while (res());
	return 0;
}