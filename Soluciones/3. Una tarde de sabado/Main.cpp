#include "Cartelera.h"
#include <vector>

bool res() {
	int numPelis; std::cin >> numPelis;
	if (numPelis == 0) return false;

	Cartelera c(numPelis);
	std::cin >> c;
	c.ordenar();
	std::cout << c;

	return true;
}

int main() {
	while (res());
	return 0;
}