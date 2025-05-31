#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>

//Ventana deslizante
void resuelveCaso() {
    int n;
    std::cin >> n;
    std::vector<int> caps(n);

    for (int i = 0; i < n; i++)
        std::cin >> caps[i];

    std::unordered_set<int> capsVistos;
    int indL = 0, maxLength = 0;
    for (int indR = 0; indR < caps.size(); ++indR) {
        while (capsVistos.count(caps[indR])) {
            capsVistos.erase(caps[indL]);
            ++indL;
        }
        capsVistos.insert(caps[indR]);
        maxLength = std::max(maxLength, indR - indL + 1);
    }

    /* CON UN SOLO MAPA (UNORDERED)
        std::unordered_map<int, int> capsVistos;
        int max = 0, pos = 0;
        for (int i = 0; i < capitulos; ++i){
            std::cin >> cap;
            if (capsVistos.count(cap) && capsVistos[cap] >= pos) {
                pos = capsVistos[cap] + 1;
            }
            max = std::max(max, i - pos + 1);
            capsVistos[cap] = i;
        }
    
    */

    std::cout << maxLength << '\n';
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int casos;
    std::cin >> casos;
    std::cin.ignore(1);
    while (casos--) {
        resuelveCaso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
