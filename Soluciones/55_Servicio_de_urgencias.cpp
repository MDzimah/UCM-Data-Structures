#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <list>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

// Elige el tipo representante adecuado para el TAD AcademiaChino e
// implementa sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente.
//@ <answer>

using nombre = string;

class TAD {
    struct Paciente {
        int gravedad;
        list<nombre>::iterator pos;
    };
    unordered_map<nombre, Paciente> pacientes;
    vector<list<nombre>> colasDeGravedad;
    set<nombre> recs;
public:

    //O(1)
    TAD() {
        for (int i = 0; i < 3; ++i)
            colasDeGravedad.push_back({});
    }

    //O(1) porque operaciones elementales sobre mapas desordenados tiene coste amortizado constante
    void nuevo_paciente(nombre n, int g) {
        if (pacientes.count(n)) throw domain_error("Paciente repetido");
        if (1 > g || g > 3) throw domain_error("Gravedad incorrecta");

        --g;
        colasDeGravedad[g].push_back(n);
        pacientes[n] = { g, --colasDeGravedad[g].end() };
    }

    //O(1) ídem
    int gravedad_actual(nombre n) const {
        if (!pacientes.count(n)) throw domain_error("Paciente inexistente");
        return pacientes.at(n).gravedad + 1;
    }

    //O(1) ídem, además, teniendo el iterador eliminar de una lista tiene coste constante
    nombre siguiente() {
        int g = -1;

        for (int i = 2; i >= 0 && g == -1; --i) {
            if (!colasDeGravedad[i].empty()) g = i;
        }

        if (g == -1) throw domain_error("No hay pacientes");

        nombre pacienteAtendido = colasDeGravedad[g].front();

        colasDeGravedad[g].pop_front();
        pacientes.erase(pacienteAtendido);

        return pacienteAtendido;
    }

    //O(log n) en los n recuperados (se inserta en mapa ordenado)
    void mejora(nombre n) {
        if (!pacientes.count(n)) throw domain_error("Paciente inexistente");

        int newG = pacientes[n].gravedad - 1;

        if (newG >= 0) {
            colasDeGravedad[pacientes[n].gravedad].erase(pacientes[n].pos);
            colasDeGravedad[newG].push_front(n);
            pacientes[n].pos = colasDeGravedad[newG].begin();
            pacientes[n].gravedad = newG;
        }
        else {
            colasDeGravedad[0].erase(pacientes[n].pos);
            pacientes.erase(n);
            recs.insert(n);
        }
    }

    //O(n) en los n recuperados
    list<nombre> recuperados() const {
        list<nombre> l;
        for (auto const& it : recs) {
            l.push_back(it);
        }
        return l;
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

    nombre n;
    int g;

    TAD urg;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo_paciente") {
                cin >> n >> g;
                urg.nuevo_paciente(n, g);
            }
            else if (orden == "gravedad_actual") {
                cin >> n;
                g = urg.gravedad_actual(n);
                cout << "La gravedad de " << n << " es " << g << '\n';
            }
            else if (orden == "siguiente") {
                n = urg.siguiente();
                cout << "Siguiente paciente: " << n << '\n';
            }
            else if (orden == "mejora") {
                cin >> n;
                urg.mejora(n);
            }
            else {
                cout << "Lista de recuperados:";
                list<nombre> l= urg.recuperados();
                for (auto const& it : l) {
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
