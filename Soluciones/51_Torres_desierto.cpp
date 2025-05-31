/*@ <authors>
 *
 * ED-DG12 Zipi Zapatilla
 * ED-DG08 Zape Zapatilla
 *
 *@ </authors> */

 /*@ <answer>

  Escribe aquí un comentario general sobre la solución, explicando qué tipos has elegido
  para guardar la información y poder tratarla de forma eficiente, y cuáles son las
  razones de esa elección. Indica al lado de cada operación su coste en función del tamaño
  del problema.

  @ </answer> */


  // Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <stdexcept>

#include <unordered_map>
#include <set>

using namespace std;

// Tipo de datos para representar direcciones
// Para hacer referencia a los elementos de este tipo enumerado se utiliza:
//   Direccion::Norte, Direccion::Sur, etc.
enum class Direccion { Norte, Sur, Este, Oeste };

// Operador para leer una dirección desde un flujo de entrada.
// Ejemplo de uso:
//
// Direccion dir;
// cin >> dir;
//
istream& operator>>(istream& is, Direccion& dir) {
    string palabra; is >> palabra;
    if (palabra == "Norte") dir = Direccion::Norte;
    else if (palabra == "Sur") dir = Direccion::Sur;
    else if (palabra == "Este") dir = Direccion::Este;
    else if (palabra == "Oeste") dir = Direccion::Oeste;
    else throw std::domain_error("Lectura de direccion incorrecta");
    return is;
}

// Implementa a continuación la clase Desierto.
//@ <answer>

using Coor = pair<int, int>;

class Desierto {
public:
    Desierto() { }

    //O(log T) donde T es el número de torres (se pueden colocar todas sobre la misma ordinal, X o Y)
    void anyadir_torre(const string& nombre, int x, int y) {
        if (nombreMap.count(nombre)) {
            throw domain_error("Torre ya existente");
        }
        else {
            auto const& ordinalX = xCoorMap.find(x);
            if (ordinalX != xCoorMap.end()) {
                auto const& t = ordinalX->second.lower_bound({ y,"" }); //Devuelve el primero >= a {y, ""}. "" es el vacío, menor que cualquier otro
                if (t != ordinalX->second.end()) {
                    if (t->first == y) throw domain_error("Posicion ocupada");
                }
            }
            
            nombreMap[nombre] = { x, y };
            xCoorMap[x].insert({ y, nombre });
            yCoorMap[y].insert({ x, nombre });
        }
    }

    //O(log T)
    void eliminar_torre(const string& nombre) {
        if (!nombreMap.count(nombre)) {
            throw domain_error("Torre no existente");
        }
        else {
            xCoorMap[nombreMap[nombre].first].erase({ nombreMap[nombre].second, nombre });
            yCoorMap[nombreMap[nombre].second].erase({ nombreMap[nombre].first, nombre });
            nombreMap.erase(nombre);
        }
    }

    //O(log T)
    pair<bool, string> torre_en_posicion(int x, int y) const {
        auto const& ordinalX = xCoorMap.find(x);

        if (ordinalX == xCoorMap.end()) return { false, "" };

        auto const& t = ordinalX->second.lower_bound({y, ""});

        if (t == ordinalX->second.end() || t->first != y) {
            return { false, "" };
        }
        else return { true, t->second };
    }

    //O(1)
    pair<int, int> posicion(const string& nombre) const {
        if (!nombreMap.count(nombre)) throw domain_error("Torre no existente");
        else return nombreMap.at(nombre);
    }

    //O(log T)
    string torre_mas_cercana(const string& nombre, const Direccion& dir) const {
        if (!nombreMap.count(nombre)) throw domain_error("Torre no existente");
        else {
            Coor coor = nombreMap.at(nombre);
            auto const& torres = (dir == Direccion::Norte || dir == Direccion::Sur)
                ? xCoorMap.at(coor.first)
                : yCoorMap.at(coor.second);

            auto t = (dir == Direccion::Norte || dir == Direccion::Sur)
                ? torres.find({ coor.second, nombre })
                : torres.find({ coor.first, nombre });

            if (dir == Direccion::Norte || dir == Direccion::Este) ++t;
            else {
                if (t != torres.begin()) --t;
                else t = torres.end();
            }

            if (t == torres.end()) throw domain_error("No hay torres en esa direccion");
            else return t->second;
        }
    }
private:
    unordered_map<string, Coor> nombreMap;
    unordered_map<int, set<pair<int, string>>> xCoorMap;
    unordered_map<int, set<pair<int, string>>> yCoorMap;
};

//Coste total: O(log T)



//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    string inst, nombre; int x, y; Direccion dir;
    cin >> inst;
    if (!cin) return false;
    Desierto desierto;
    while (inst != "FIN") {
        try {
            if (inst == "anyadir_torre") {
                cin >> nombre >> x >> y;
                desierto.anyadir_torre(nombre, x, y);
            }
            else if (inst == "eliminar_torre") {
                cin >> nombre;
                desierto.eliminar_torre(nombre);
            }
            else if (inst == "posicion") {
                cin >> nombre;
                auto [x, y] = desierto.posicion(nombre);
                cout << x << ' ' << y << '\n';
            }
            else if (inst == "torre_en_posicion") {
                cin >> x >> y;
                auto [hay, nombre] = desierto.torre_en_posicion(x, y);
                if (hay) cout << "SI " << nombre << '\n';
                else cout << "NO\n";
            }
            else {
                cin >> nombre >> dir;
                nombre = desierto.torre_mas_cercana(nombre, dir);
                cout << nombre << '\n';
            }
        }
        catch (domain_error& e) {
            cout << e.what() << '\n';
        }
        cin >> inst;
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