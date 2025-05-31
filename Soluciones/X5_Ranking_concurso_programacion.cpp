#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

struct Equipo {
	std::string nom;
	int t_tot;
	int p_solved;
	std::unordered_map<std::string, std::pair<int,bool>> nomP_a_Envio;
};

bool comp(Equipo const& e1, Equipo const& e2) {
	if (e1.p_solved > e2.p_solved) return true;
	else if (e1.p_solved < e2.p_solved) return false;
	else {
		if (e1.t_tot < e2.t_tot) return true;
		else if (e1.t_tot > e2.t_tot) return false;
		else return e1.nom < e2.nom;
	}
}

void res() {
	std::unordered_map<std::string, Equipo> clas;
	std::string linea; std::getline(std::cin, linea);
	while (linea != "FIN") {
		std::string nomEq, nomP, vere;
		int t;
		std::istringstream l(linea);
		l >> nomEq >> nomP >> t >> vere;

		bool v = (vere == "AC");

		//Primer envío de un equipo
		if (!clas.count(nomEq)) {
			std::unordered_map<std::string, std::pair<int,bool>> aux;
			aux[nomP] = { v ? 0 : 1 , v };
			clas[nomEq] = { nomEq, v ? t : 0, v ? 1 : 0, aux };
		}
		//Segundo o más envío de un equipo
		else {
			auto& m = clas[nomEq].nomP_a_Envio;

			int pena = (v ? 0 : 1);

			if (!m.count(nomP)) {
				m[nomP] = { pena, v };
				if (v) {
					++clas[nomEq].p_solved;
					clas[nomEq].t_tot += t;
				}
			}
			else {
				if (!m[nomP].second) {
					m[nomP] = { m[nomP].first + pena, v};
					if (v) {
						++clas[nomEq].p_solved;
						clas[nomEq].t_tot += (20 * m[nomP].first + t);
					}
				}
			}
		}
		
		std::getline(std::cin, linea);
	}
	std::vector<Equipo> clasFinal;
	for (auto const& it : clas) {
		clasFinal.push_back(it.second);
	}
	std::sort(clasFinal.begin(), clasFinal.end(), comp);

	for (Equipo const& e : clasFinal) {
		std::cout << e.nom << ' ' << e.p_solved << ' ' << e.t_tot << '\n';
	}
	std::cout << "---\n";
}

int main() {
	int nc; std::cin >> nc;
	std::cin.ignore();
	while (nc--) res();
	return 0;
}