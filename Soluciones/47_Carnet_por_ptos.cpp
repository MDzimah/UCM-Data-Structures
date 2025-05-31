#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

//Complejidad resultante: O(1) (ya que todas las operaciones sobre mapas tienen coste O(1) o O(1) amortizado)
class CarnetPuntos {
	using DNI = std::string;
	const int MIN_PTOS = 0, MAX_PTOS = 15;
public:
	
	CarnetPuntos() {
		for (int i = MIN_PTOS; i <= MAX_PTOS; ++i) 
			ptosAPersonas[i] = 0;
	}

	//O(1)
	void nuevo(DNI const& s) {
		if (!dniAPtos.count(s)) {
			dniAPtos[s] = MAX_PTOS; //O(1)
			++ptosAPersonas[MAX_PTOS]; //O(1)
		}
		else throw std::domain_error("Conductor duplicado");
	}

	//O(1)
	void quitar(DNI const& s, int ptos) {
		if (dniAPtos.count(s)) {
			int puntosActuales = dniAPtos[s];
			int puntosRestados = std::min(ptos, puntosActuales);
			--ptosAPersonas[puntosActuales];
			dniAPtos[s] -= puntosRestados;
			++ptosAPersonas[dniAPtos[s]];
		}
		else throw std::domain_error("Conductor inexistente");
	}

	//O(1)
	int consultar(DNI const& s) {
		if (dniAPtos.count(s)) return dniAPtos[s]; //O(1)
		else throw std::domain_error("Conductor inexistente");
	}

	//O(1)
	int cuantos_con_ptos(int ptos) {
		if (MIN_PTOS <= ptos && ptos <= MAX_PTOS) return ptosAPersonas[ptos]; //O(1)
		else throw std::domain_error("Puntos no validos");
	}

private:
	std::unordered_map<DNI, int> dniAPtos;
	std::unordered_map<int, int> ptosAPersonas;
};

//O(C) donde C es el número de consultas que se hacen
bool res() {
	std::string op; std::cin >> op;

	if (!std::cin) return false;

	CarnetPuntos cp;
	while (op != "FIN") {
		try {
			if (op == "nuevo") {
				std::string dni; std::cin >> dni;
				cp.nuevo(dni);
			}
			else if (op == "quitar") {
				std::string dni; int ptos;  std::cin >> dni >> ptos;
				cp.quitar(dni, ptos);
			}
			else if (op == "consultar") {
				std::string dni; std::cin >> dni;
				int ptos = cp.consultar(dni);
				std::cout << "Puntos de " << dni << ": " << ptos << '\n';
			}
			else {
				int ptos; std::cin >> ptos;
				int personas = cp.cuantos_con_ptos(ptos);
				std::cout << "Con " << ptos << " puntos hay " << personas << '\n';
			}
		}
		catch (std::domain_error& e) { std::cout << "ERROR: " << e.what() << '\n'; }
		std::cin >> op;
	}
	std::cout << "---\n";

	return true;
}

int main() {
	while (res());
	return 0;
}