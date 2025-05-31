#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

void leerJugs(std::unordered_map<int, std::vector<std::string>>& nC_Js, std::unordered_map<std::string, int>& J_nQ) {
    std::string nom; std::cin >> nom;
    J_nQ[nom] = 0;
    int aux; std::cin >> aux;
    while (aux != 0) {
        nC_Js[aux].push_back(nom);
        ++J_nQ[nom];
        std::cin >> aux;
    }
}

bool res() {
    int N; std::cin >> N;
    if (N == 0) return false;
    
    //Pares número_carta - jugadores_q_tienen_el_número
    std::unordered_map<int, std::vector<std::string>> nC_Js;
    //Pares nombre_jugador - números_q_le_quedan_para_ganar_bingo
    std::unordered_map<std::string, int> J_nQ;

    while (N--) leerJugs(nC_Js, J_nQ);

    bool bingo = false;
    std::vector<std::string> ganadores;
    while (!bingo) {
        int b; std::cin >> b;
        if (nC_Js.count(b) == 1) {
            for (std::string const& nom : nC_Js[b]) {
                --J_nQ[nom];
                if (J_nQ[nom] == 0) {
                    ganadores.push_back(nom);
                    bingo = true;
                }
            }
        }
    }

    std::sort(ganadores.begin(), ganadores.end());

    std::cout << ganadores[0];
    for (int i = 1; i < ganadores.size(); ++i) {
        std::cout << ' ' << ganadores[i];
    }
    std::cout << '\n';
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
