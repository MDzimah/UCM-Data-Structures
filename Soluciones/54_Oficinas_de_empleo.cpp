#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <list>
#include <unordered_map>
#include <vector>
#include <map>

using namespace std;

// Elige el tipo representante adecuado para el TAD AcademiaChino e
// implementa sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente.
//@ <answer>

using Nombre = string;
using Empleo = string;

class OficinaEmpleo {
    unordered_map<Nombre, map<Empleo, list<Nombre>::iterator>> infoPersonas;
    unordered_map<Empleo, list<Nombre>> ofertasEmpleo;
public:

    OficinaEmpleo() {}

    //O(log n) en los n empleos
    void altaOficina(Nombre n, Empleo e) {
        if (!infoPersonas.count(n)) {
            ofertasEmpleo[e].push_back(n);
            infoPersonas[n].insert({ e, --ofertasEmpleo[e].end() });
        }
        else {
            if (!infoPersonas[n].count(e)) {
                ofertasEmpleo[e].push_back(n);
                infoPersonas[n].insert({ e, --ofertasEmpleo[e].end() });
            }
        }
    }

    //O(n) en los n empleos
    string ofertaEmpleo(Empleo e) {
        if (!ofertasEmpleo.count(e)) throw domain_error("No existen personas apuntadas a este empleo");
        string persona = *ofertasEmpleo[e].begin();

        for (auto p : infoPersonas[persona]) {
            ofertasEmpleo[p.first].erase(p.second);
            if (ofertasEmpleo[p.first].empty()) ofertasEmpleo.erase(p.first);
        }        
        infoPersonas.erase(persona);

        return persona;
    }

    //O(n) en los n empleos
    vector<Empleo> listadoEmpleos(Nombre n) const {
        if (!infoPersonas.count(n)) throw domain_error("Persona inexistente");
        vector<Empleo> v;
        for (auto p : infoPersonas.at(n)) {
            v.push_back(p.first);
        }
        return v;
    }
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    string orden;
    cin >> orden;
    if (!cin)
        return false;

    Nombre n;
    Empleo e;

    OficinaEmpleo of;

    while (orden != "FIN") {
        try {
            if (orden == "altaOficina") {
                cin >> n >> e;
                of.altaOficina(n, e);
            }
            else if (orden == "ofertaEmpleo") {
                cin >> e;
                n = of.ofertaEmpleo(e);
                cout << e << ": " << n << '\n';
            }
            else {
                cin >> n;
                vector<Empleo> v;
                v = of.listadoEmpleos(n);
                cout << n << ':';
                for (auto it : v) {
                    cout << " " << it;
                }
                cout << '\n';
            }
        }
        catch (std::domain_error& e) {
            cout << "ERROR: " << e.what() << '\n';
        }

        cin >> orden;
    }
    cout << "---\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
