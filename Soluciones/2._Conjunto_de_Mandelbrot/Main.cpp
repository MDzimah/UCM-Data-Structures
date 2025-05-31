#include "Complejo.h"

void res() {
	Complejo c; int it;
	std::cin >> c >> it;
	if (c.isInMandelbrot(it)) std::cout << "SI\n";
	else std::cout << "NO\n";
}

int main() {
	int nc; std::cin >> nc;
	for (int i = 0; i < nc; ++i)
		res();
	return 0;
}