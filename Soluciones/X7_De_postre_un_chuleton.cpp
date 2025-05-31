#include <iostream>
#include <list>
#include <string>
#include <fstream>

enum class Categoria { Primero, Segundo, Postre };
struct Plato {
	Categoria categoria;
	std::string nombre;
};

//Coste O(platos.size()) ya que insertar y eliminar en una lista doblemente enlazada (dado el iterador al sitio donde insertar/eliminar)
//tiene coste cte, luego en cada iteración se realizan solamente operaciones de coste cte
void ordenar_menu(std::list<Plato>& platos) {
	auto curr = platos.begin();
	auto _primer0 = platos.end();
	auto _primer1 = platos.end();
	auto _primer2 = platos.end();

	//Podría ocurrir que no hay primeros o segundos
	while (curr != _primer0 && curr != _primer1 && curr != _primer2) {
		switch (curr->categoria) {
		case Categoria::Primero: {
			if (_primer1 == platos.end()) {
				auto aux = platos.insert(_primer2, { curr->categoria, curr->nombre });
				_primer0 = (_primer0 == platos.end() ? aux : _primer0);
			}
			else {
				auto aux = platos.insert(_primer1, { curr->categoria, curr->nombre });
				_primer0 = (_primer0 == platos.end() ? aux : _primer0);
			}
			break;
		}
		case Categoria::Segundo: {
			auto aux = platos.insert(_primer2, { curr->categoria, curr->nombre });
			_primer1 = (_primer1 == platos.end() ? aux : _primer1);
			break;
		}
		case Categoria::Postre: {
			platos.push_back({ curr->categoria, curr->nombre });
			_primer2 = (_primer2 == platos.end() ? --platos.end() : _primer2);
			break;
		}
		}
		curr = platos.erase(curr);
	}
}

bool res() {
	int N; std::cin >> N;

	if (N == 0) return false;

	std::list<Plato> platos;

	while (N--) {
		Plato p;
		char aux; std::cin >> aux;
		switch (aux) {
		case '1': p.categoria = Categoria::Primero; break;
		case '2': p.categoria = Categoria::Segundo; break;
		default: p.categoria = Categoria::Postre; break;
		}

		std::getline(std::cin, p.nombre);
		platos.push_back(p);
	}

	ordenar_menu(platos);

	for (Plato const& p : platos) {
		if (p.categoria == Categoria::Primero) std::cout << '1';
		else if (p.categoria == Categoria::Segundo) std::cout << '2';
		else std::cout << 'P';

		std::cout << p.nombre << '\n';
	}
	std::cout << "---\n";

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (res());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}