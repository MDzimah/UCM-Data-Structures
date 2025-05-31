/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1:
  Estudiante 2:


  Dad una explicación de la solución y justificad su coste.

  @ </answer> */


#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <set>
using namespace std;

// Elige el tipo representante adecuado para el TAD e implementa
// sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente.
//@ <answer>
using DNI = string;

class carnet_puntos {
    unordered_map<DNI, int> alums;
    unordered_map<int, list<DNI>> alumsConXptos;
    unordered_map<int, unordered_map<DNI, list<DNI>::iterator>> posInList;
    int const MAX = 15;
    int const MIN = 0;
public:
    carnet_puntos() {}

    //O(1)
    void nuevo(DNI conductor) {
        if (!alums.count(conductor)) {
            alums[conductor] = MAX;
            alumsConXptos[MAX].push_front(conductor);
            posInList[MAX][conductor] = alumsConXptos[MAX].begin();
        }
        else throw std::domain_error("Conductor duplicado");
    }

    //O(1)
    void quitar(DNI conductor, int puntos) {
        if (alums.count(conductor)) {
            if (puntos > 0) {
                int oldPtos = alums[conductor];
                if (oldPtos > 0) {
                    //Acción de quitar ptos y quitarle de donde no pertenece
                    alumsConXptos[oldPtos].erase(posInList[oldPtos][conductor]);
                    posInList[oldPtos].erase(conductor);
                    alums[conductor] -= std::min(oldPtos, puntos);

                    int newPtos = alums[conductor];
                    //Acción de reinsertar en otro sitio
                    alumsConXptos[newPtos].push_front(conductor);
                    posInList[newPtos][conductor] = alumsConXptos[newPtos].begin();
                }
            }
        }
        else throw std::domain_error("Conductor inexistente");
    }

    //O(1)
    void recuperar(DNI conductor, int puntos) {
        if (alums.count(conductor)) {
            if (puntos > 0) {
                int oldPtos = alums[conductor];
                if (oldPtos < 15) {
                    //Acción de sumar ptos y quitarle de donde no pertenece
                    alumsConXptos[oldPtos].erase(posInList[oldPtos][conductor]);
                    posInList[oldPtos].erase(conductor);
                    alums[conductor] = std::min(alums[conductor] + puntos, MAX);

                    int newPtos = alums[conductor];
                    //Acción de reinsertar en otro sitio
                    alumsConXptos[newPtos].push_front(conductor);
                    posInList[newPtos][conductor] = alumsConXptos[newPtos].begin();
                }
            }
        }
        else throw std::domain_error("Conductor inexistente");
    }

    //O(1)
    int consultar(DNI conductor) const {
        if (alums.count(conductor)) {
            return alums.at(conductor);
        }
        else throw std::domain_error("Conductor inexistente");
    }

    //O(1)
    int cuantos_con_puntos(int puntos) const {
        if (MIN <= puntos && puntos <= MAX) {
            return alumsConXptos.count(puntos) ? alumsConXptos.at(puntos).size() : 0;
        }
        else throw std::domain_error("Puntos no validos");
    }

    //O(1)
    list<DNI> const& lista_por_puntos(int puntos) const {
        if (MIN <= puntos && puntos <= MAX) {
            static const list<DNI> na;
            return alumsConXptos.count(puntos) ? alumsConXptos.at(puntos) : na; //Dangling reference problem if not puttins "static const"
        }
        else throw std::domain_error("Puntos no validos");
    }
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;

    carnet_puntos dgt;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                cin >> dni;
                dgt.nuevo(dni);
            }
            else if (orden == "quitar") {
                cin >> dni >> punt;
                dgt.quitar(dni, punt);
            }
            else if (orden == "recuperar") {
                cin >> dni >> punt;
                dgt.recuperar(dni, punt);
            }
            else if (orden == "consultar") {
                cin >> dni;
                punt = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << punt << '\n';
            }
            else if (orden == "cuantos_con_puntos") {
                cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            }
            else if (orden == "lista_por_puntos") {
                cin >> punt;
                auto const& lista = dgt.lista_por_puntos(punt);
                cout << "Tienen " << punt << " puntos:";
                for (auto const& dni : lista)
                    cout << ' ' << dni;
                cout << '\n';
            }
            else
                cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error& e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
