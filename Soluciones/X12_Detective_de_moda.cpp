#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <deque>

using namespace std;

//Coste O(log n) en los n únicos
class TiendaCamisetas {
    set<int> unicos;
    unordered_map<string, unordered_set<int>> infoRopa; //Todos los ids de la ropa
    deque<pair<string, int>> ropa;

    //O(log n) en los n únicos al borrar de un mapa ordenado
    void insertar(string const& color, bool izq) {
        int nextInd;
        ropa.empty() ? nextInd = 0 : (izq ? nextInd = ropa.front().second - 1 : nextInd = ropa.back().second + 1);

        izq ? ropa.push_front({ color, nextInd }) : ropa.push_back({ color, nextInd });

        //Está a punto de no ser único
        if (infoRopa[color].size() == 1) {
            //Coste contante ya q hay 1 elemento siempre
            for (auto const& i : infoRopa[color]) {
                unicos.erase(i);
            }
        }
        else if (infoRopa[color].size() == 0) unicos.insert(nextInd);

        infoRopa[color].insert(nextInd);
    }

    //O(log n) en los n únicos al borrar de un mapa ordenado
    void comprar(bool izq) {
        if (ropa.empty()) throw domain_error("Tienda sin camisetas");

        string colorQuitado;
        int indQuitado;

        if (izq) {
            indQuitado = ropa.front().second;
            colorQuitado = ropa.front().first;
        }
        else {
            indQuitado = ropa.back().second;
            colorQuitado = ropa.back().first;
        }

        if (infoRopa[colorQuitado].size() == 1) {
            for (auto const& i : infoRopa[colorQuitado]) {
                unicos.erase(i);
            }
            infoRopa.erase(colorQuitado);
        }
        else {
            infoRopa[colorQuitado].erase(indQuitado);

            //Se convierte en único tras la compra
            if (infoRopa[colorQuitado].size() == 1) {
                for (auto const& i : infoRopa[colorQuitado]) {
                    unicos.insert(i);
                }
            }
        }
        izq ? ropa.pop_front() : ropa.pop_back();
    }
public:
    TiendaCamisetas() {}

    void inserta_izquierda(string const& color) { insertar(color, true); }

    void inserta_derecha(string const& color) { insertar(color, false); }

    void compra_izquierda() { comprar(true); }

    void compra_derecha() { comprar(false); }

    //O(1)
    string pregunta() const {
        if (unicos.empty()) return "NADA INTERESANTE\n";
        else {
            //El +1 incluye la ropa única siendo comprada
            int numRopa_izqAdcha = *unicos.begin() - ropa.front().second + 1;
            int numRopa_dchaAizq = ropa.back().second - *(--unicos.end()) + 1;

            if (numRopa_izqAdcha == numRopa_dchaAizq) return std::to_string(numRopa_dchaAizq) + " CUALQUIERA\n";
            else if (numRopa_izqAdcha > numRopa_dchaAizq) return std::to_string(numRopa_dchaAizq) + " DERECHA\n";
            else return std::to_string(numRopa_izqAdcha) + " IZQUIERDA\n";
        }
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

    string c;

    TiendaCamisetas s;

    while (orden != "FIN") {
        try {
            if (orden == "inserta_izquierda") {
                cin >> c;
                s.inserta_izquierda(c);
            }
            else if (orden == "inserta_derecha") {
                cin >> c;
                s.inserta_derecha(c);
            }
            else if (orden == "compra_izquierda") {
                s.compra_izquierda();
            }
            else if (orden == "compra_derecha") {
                s.compra_derecha();
            }
            else {
                string const& mens = s.pregunta();
                cout << mens;
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
