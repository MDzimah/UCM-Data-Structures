#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <unordered_map>
#include <map>
using namespace std;

using libro = string;

class VentaLibs {
    struct InfoLibro {
        int ej;
        int v;
        list<libro>::iterator posEnLV;
    };
    struct Comp {
        bool operator()(int const& a, int const& b) const { 
            return a > b; 
        }
    };
    unordered_map<libro, InfoLibro> libreria;
    map<int, list<libro>, Comp> vendidos;
public:
    //O(1)
    void nuevoLibro(int n, libro const& x) {
        if (libreria.count(x)) libreria[x].ej += n;
        else libreria[x] = { n, 0, {} };
    }
    
    //O(log n) al insertar/consultar/eliminar de un mapa ordenado
    void comprar(libro const& x) {
        if (!libreria.count(x)) throw invalid_argument("Libro no existente");
        if (libreria[x].ej == 0) throw out_of_range("No hay ejemplares");

        --libreria[x].ej;
        if (libreria[x].v > 0) {
            auto& pos = libreria[x].posEnLV;
            auto& ventas = libreria[x].v;
            vendidos[ventas].erase(pos);

            vendidos[++ventas].push_front(x);
            pos = vendidos[ventas].begin();
        }
        else {
            auto& lowestVendList = vendidos[1];
            lowestVendList.push_front(x);
            libreria[x] = { libreria[x].ej, 1, lowestVendList.begin() };
        }
    }

    //O(1)
    bool estaLibro(libro const& x) {
        return libreria.count(x);
    }

    //O(log n) en los n libros vendidos
    void elimLibro(libro const& x) {
        if (libreria.count(x)) {
            if (libreria[x].v > 0) vendidos[libreria[x].v].erase(libreria[x].posEnLV);
            libreria.erase(x);
        }
    }

    //O(1)
    int numEjemplares(libro const& x) {
        if (!libreria.count(x)) throw invalid_argument("Libro no existente");
        else return libreria[x].ej;
    }

    //O(n) en los n libros vendidos
    list<libro> top10() {
        list<libro> t10;

        int cont = 0;
        //Recorro el mapa de mayor a menor pero conservo el orden de las listas internas
        for (auto const& it : vendidos) {
            for (auto const& l : it.second) {
                t10.push_back(l);
                if (++cont == 10) break;
            }
            if (cont == 10) break;
        }
        return t10;
    }
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    int numOps;
    cin >> numOps;

    if (!std::cin) return false;

    VentaLibs tienda;
    libro l; int n;
    while (numOps--) {
        try {
            string orden;
            cin >> orden;
            cin.get();
            if (orden == "nuevoLibro") {
                cin >> n;
                cin.get();
                getline(cin, l);
                tienda.nuevoLibro(n, l);
            }
            else if (orden == "comprar") {
                getline(cin, l);
                tienda.comprar(l);
            }
            else if (orden == "estaLibro") {
                getline(cin, l);
                if (tienda.estaLibro(l)) cout << "El libro " << l << " esta en el sistema";
                else cout << "No existe el libro " << l << " en el sistema";
                cout << '\n';
            }
            else if (orden == "elimLibro") {
                getline(cin, l);
                tienda.elimLibro(l);
            }
            else if (orden == "numEjemplares") {
                getline(cin, l);
                try {
                    int ej = tienda.numEjemplares(l);
                    cout << "Existen " << ej << " ejemplares del libro " << l << "\n";
                }
                catch (std::exception& e) {
                    cout << "No existe el libro " << l << " en el sistema\n";
                }
            }
            else {
                auto ls = tienda.top10();
                cout << "TOP10\n";
                for (libro const& l : ls) {
                    cout << "    " << l << '\n';
                }
            }
        }
        catch (std::exception& e) {
            std::cout << e.what() << '\n';
        }
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
