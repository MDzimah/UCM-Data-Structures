#include "TADmulticonj.h"

using Resultado = std::vector <char>;
using Conjunto = std::vector <long long int>;


int main() {

	int numElems;
	std::cin >> numElems;

	while (numElems != 0) {
		TADmulticonj multiConj;
		Conjunto conj1 (numElems), conj2(numElems);

		for (int i = 0; i < numElems; ++i) {
			std::cin >> conj1[i];
			multiConj.insertar(conj1[i]);
		}
		
		for (int i = 0; i < numElems; ++i) 
			std::cin >> conj2[i];

		Resultado res(numElems);
		for (int i = 0; i < numElems; ++i) {
			if (conj1[i] == conj2[i]) { 
				res[i] = '#'; 
				multiConj.eliminar(conj1[i]);
			}
		}

		for (int i = 0; i < numElems; ++i) {
			if (res[i] != '#') {
				if (multiConj.pertenece(conj2[i])) {
					res[i] = 'O';
					multiConj.eliminar(conj2[i]);
				}
				else res[i] = '.';
			}
		}
		
		for (int i = 0; i < numElems; ++i)
			std::cout << res[i];

		std::cout << '\n';

		std::cin >> numElems;
	}

	return 0;
}