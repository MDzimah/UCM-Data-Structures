#include <iostream>
#include <stack>
#include <queue>

/*
* Vuelo: camino entre dos pilares con alturas decrecientes de izq. a dcha.

LLevo un stack con orden creciente (desde la cima hasta el fondo de la pila).

Si no tengo elementos en la pila, entonces no hay elementos anteriores que permitan hacer
el vuelo. Imprimo para dicha altura le�da "no hay"

Si el elemento actual le�do es >= que pila.top(), entonces busco dentro de mi
pila ordenada de menor a mayor alg�n pilar estrictamente m�s alto que el elemento le�do. Puedo eliminar o desapilar definitivamente
todos los pilares que no sean m�s altos que el elemento actual debido a que, para cualquier pilar posterior al actual, ninguno de los anteriores 
eliminados puede ser soluci�n ya que no son ni m�s altos ni est�n m�s cerca que el actual a los pilares que lo sigan. Si 
encuentro un pilar en mi pila m�s alto que el actual, entonces es un vuelo posible. En caso contrario, "no hay"

Si el elemento actual le�do es menor que el que est� en mi cima, he encontrado un vuelo v�lido. S� que es el mejor posible
por el TAD elegido y porque garantizo el invariante de que el stack est� ordenado de menor a mayor altura, luego todos los elementos anteriores
a la cima de la pila tienen que ser obligatoriamente mayores (estrictamente) que el elemento actual.

Coste del algoritmo: O(n) donde n = num_pilares. Cada elemento le�do se apila y desapila una vez como mucho, luego el coste en el caso peor
es O(2n). Sin embargo, este coste sigue siendo lineal respecto del n�mero de pilares.
*/

bool res() {
	int aux;
	std::cin >> aux;
	if (aux == -1) return false;
	std::queue<int> datos;
	datos.push(aux);

	std::cin >> aux;
	while (aux != -1) {
		datos.push(aux);
		std::cin >> aux;
	}

	std::stack<int> alt;
	while (!datos.empty()) {
		if (alt.empty()) {
			std::cout << "NO HAY\n";
		}
		else {
			if (alt.top() > datos.front()) {
				std::cout << alt.top() << '\n';
			}
			else {
				while (!alt.empty() && alt.top() <= datos.front()) {
					alt.pop();
				}
				if (alt.empty()) std::cout << "NO HAY\n";
				else std::cout << alt.top() << '\n';
			}
		}
		alt.push(datos.front());

		datos.pop();
	}

	std::cout << "---\n";

	return true;
}


int main() {
	while (res());
	return 0;
}