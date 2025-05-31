#include <list>
#include <iostream>

using mL = std::list<std::list<int>>;

bool es_toeplitz(mL const& matriz) {
	auto filaAct = matriz.cbegin();
	auto filaNext = ++matriz.cbegin();

	while (filaNext != matriz.cend()) {
		auto colAct = filaAct->cbegin();
		auto colNext = ++filaNext->cbegin();
		
		while (colNext != filaNext->cend()) {
			if (*colAct != *colNext) return false;
			++colNext;
			++colAct;
		}
		++filaAct;
		++filaNext;
	}
	return true;
}

std::list<int> leerFila() {
	int aux;
	std::cin >> aux;
	std::list<int> l;
	while (aux != 0) {
		l.push_back(aux);
		std::cin >> aux;
	}
	return l;
}

void leerMatriz(mL& matriz) {
	std::list<int> filaAct = leerFila();
	while (!filaAct.empty()) {
		matriz.push_back(filaAct);
		filaAct = leerFila();
	}
}

bool res() {
	mL mat;
	leerMatriz(mat);

	if (mat.empty()) return false;

	if (es_toeplitz(mat)) std::cout << "SI\n";
	else std::cout << "NO\n";

	return true;
}

int main() {
	while (res());
	return 0;
}