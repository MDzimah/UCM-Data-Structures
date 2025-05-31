#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <vector>


class Autoescula {
public:
	void alta(std::string const& A, std::string const& P) {
		if (alumAPtos.count(A)) {
			std::string oldP = alumAProfe[A];
			alumAProfe[A] = P;
			profeAAlumnos[oldP].erase(A);
			profeAAlumnos[P].insert(A);
		}
		else {
			alumAPtos[A] = 0;
			alumAProfe[A] = P;
			profeAAlumnos[P].insert(A);
		}
	}

	bool es_alumno(std::string const& A, std::string const& P) { return alumAProfe[A] == P; }

	int puntuacion(std::string const& A) {
		if (alumAPtos.count(A)) return alumAPtos[A];
		else throw std::domain_error("El alumno " + A + " no esta matriculado");
	}

	void actualizar(std::string A, int N) {
		if (alumAPtos.count(A)) alumAPtos[A] += N;
		else throw std::domain_error("El alumno " + A + " no esta matriculado");
	}

	std::vector<std::string> examen(std::string const& P, int N) {
		std::vector<std::string> presentan;
		for (std::string const& s : profeAAlumnos[P]) {
			if (alumAPtos[s] >= N) 
				presentan.push_back(s);
		}
		std::sort(presentan.begin(), presentan.end());
		return presentan;
	}

	void aprobar(std::string const& A) {
		auto it = alumAPtos.find(A);
		if (alumAPtos.count(A)) {
			std::string profe = alumAProfe[A];
			alumAPtos.erase(A);
			alumAProfe.erase(A);
			profeAAlumnos[profe].erase(A);
		}
		else throw std::domain_error("El alumno " + A + " no esta matriculado");
	}

private:
	std::unordered_map<std::string, std::string> alumAProfe;
	std::unordered_map<std::string, int> alumAPtos;
	std::unordered_map<std::string, std::unordered_set<std::string>> profeAAlumnos;
};


bool res() {
	std::string op; std::cin >> op;

	if (!std::cin) return false;

	Autoescula a;
	while (op != "FIN") {
		try {
			if (op == "alta") {
				std::string A, P; std::cin >> A >> P;
				a.alta(A, P);
			}
			else if (op == "es_alumno") {
				std::string A, P; std::cin >> A >> P;
				std::string aux = "";

				if (!a.es_alumno(A, P)) aux = " no";

				std::cout << A << aux << " es alumno de " << P << '\n';
			}
			else if (op == "puntuacion") {
				std::string A; std::cin >> A;
				int p = a.puntuacion(A);
				std::cout << "Puntuacion de " << A << ": " << p << '\n';
			}
			else if (op == "actualizar") {
				int N;
				std::string A; std::cin >> A >> N;
				a.actualizar(A, N);
			}
			else if (op == "examen") {
				int N;
				std::string P; std::cin >> P >> N;

				std::vector<std::string> v = a.examen(P, N);
				std::cout << "Alumnos de " << P << " a examen:\n";
				for (std::string const& s : v) {
					std::cout << s << '\n';
				}
			}
			else {
				std::string A; std::cin >> A;
				a.aprobar(A);
			}
		}
		catch (std::domain_error& e) { std::cout << "ERROR\n"; }
		std::cin >> op;
	}
	std::cout << "---\n";

	return true;
}

int main() {
	while (res());
	return 0;
}