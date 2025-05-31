#include "Hora.h"
#include <vector>

bool res() {
	int nT, nH; std::cin >> nT >> nH;
	if (nT == 0 && nH == 0) return false;

	std::vector <Hora> horario(nT);

	for (Hora& h : horario)
		std::cin >> h;

	for (int j = 0; j < nH; ++j) {
		Hora c; std::cin >> c;
		int i = -1, d = horario.size();
		while (i + 1 != d) {
			int m = (i + d) / 2;
			if (horario[m] < c) i = m;
			else d = m;
		}

		if (d != horario.size()) std::cout << horario[d] << '\n';
		else std::cout << "NO\n";
	}
	std::cout << "---\n";

	return true;
}

int main() {
	while (res());
	return 0;
}