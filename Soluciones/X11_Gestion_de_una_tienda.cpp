#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <iomanip>
#include <queue>
#include <list>
#include <map>

using namespace std;
using cod = string;
using fecha = string;
using cli = string;

class Tienda {
    struct Fecha {
        int dia, mes, anyo;
    };
    struct Comp {
        bool operator()(Fecha const& f1, Fecha const& f2) const {
            if (f1.anyo != f2.anyo) return f1.anyo < f2.anyo;
            if (f1.mes != f2.mes) return f1.mes < f2.mes;
            if (f1.dia != f2.dia) return f1.dia < f2.dia;
            return false;
        }
    };
    struct Almacen {
        map<Fecha, int, Comp> prodConFechas;
        int numTotProd = 0;
        list<cli> cola;
    };
    unordered_map<cod, Almacen> almacen;
    unordered_map<cli, unordered_map<cod, list<list<cli>::iterator>>> posEnCola;

    Fecha convertir(fecha const& f) {
        string any, mes, dia;
        int i = 0;
        while (i < f.size() && f[i] != '/') {
            dia += f[i];
            ++i;
        }
        ++i;
        while (i < f.size() && f[i] != '/') {
            mes += f[i];
            ++i;
        }
        ++i;
        while (i < f.size()) {
            any += f[i];
            ++i;
        }
        return { std::stoi(dia), std::stoi(mes), std::stoi(any) };
    }
public:
    Tienda() {}

    //O(n + log m) en los n compradores totales, m productos totales
    queue<string> adquirir(cod const& c, fecha const& f, int const& ctdad) {
        queue<string> compradores;
        list<cli>& cola = almacen[c].cola;

        while (!cola.empty() && compradores.size() < ctdad) {
            compradores.push(cola.front());
            posEnCola[cola.front()][c].pop_front();
            cola.pop_front();
        }
       
        if (compradores.size() < ctdad) {
            Fecha fc = this->convertir(f);
            if (almacen[c].prodConFechas.count(fc)) almacen[c].prodConFechas[fc] += ctdad - (int)compradores.size();
            else almacen[c].prodConFechas[fc] = ctdad - (int)compradores.size();
            almacen[c].numTotProd += ctdad - (int)compradores.size();
        }

        return compradores;
    }

    //O(log n) en los n productos totales
    std::pair<bool, Fecha> vender(cod const& c, cli const& cl) {
        if (almacen[c].prodConFechas.empty()) {
            almacen[c].cola.push_back(cl);
            posEnCola[cl][c].push_back(--almacen[c].cola.end());
            return { false, {} };
        }
        else {
            Fecha f = almacen[c].prodConFechas.begin()->first;
            --almacen[c].prodConFechas[f];
            --almacen[c].numTotProd;

            if (!posEnCola[cl][c].empty()) {
                almacen[c].cola.erase(posEnCola[cl][c].front());
                posEnCola[cl][c].pop_front();
            }
            if (almacen[c].prodConFechas[f] == 0) almacen[c].prodConFechas.erase(f);
            return { true, f };
        }
    }

    //O(1)
    int cuantos(cod const& c) const {
        return almacen.count(c) ? almacen.at(c).numTotProd : 0;
    }

    //O(1)
    bool hay_esperando(cod const& c) const {
        return almacen.count(c) && almacen.at(c).cola.size() > 0;
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

    cod c;
    cli cl;
    int ctdad;
    fecha f;

    Tienda s;

    while (orden != "FIN") {
        try {
            if (orden == "adquirir") {
                cin >> c >> f >> ctdad;
                queue<cli> esp = s.adquirir(c, f, ctdad);

                std::cout << "PRODUCTO ADQUIRIDO";
                while (!esp.empty()) {
                    std::cout << ' ' << esp.front();
                    esp.pop();
                }
                std::cout << '\n';
            }
            else if (orden == "vender") {
                cin >> c >> cl;
                auto const& res = s.vender(c, cl);
                if (res.first) std::cout << "VENDIDO " << std::setw(2) << std::setfill('0') << res.second.dia << '/' << std::setw(2) << std::setfill('0') << res.second.mes << '/' << std::setw(2) << std::setfill('0') << res.second.anyo;
                else std::cout << "EN ESPERA";
                std::cout << '\n';
            }
            else if (orden == "cuantos") {
                cin >> c;
                cout << s.cuantos(c) << '\n';
            }
            else {
                cin >> c;
                if (s.hay_esperando(c)) cout << "SI";
                else cout << "NO";
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
