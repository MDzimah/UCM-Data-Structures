/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

  /*@ <answer>

    Dad una explicaci�n de la soluci�n y justificad el coste del
    algoritmo.
    
    Se lleva un stack ordenado de menor a mayor n�mero de accidentes.
    Si el i-�simo elemento le�do es menor o igual que el top, entonces ya tenemos 
    la soluci�n y lo metemos en el stack.

    Si es igual, respondemos con que no hay y lo metemos en el stack

    Si es mayor, desapilamos hasta encontrar el primero con estrictamente 
    mayor n�mero de muertos que el elemento le�do. Mostramos el accidente en el top
    y apilamos este nuevo, estrictamente menor que el �ltimo

    Coste O(N) en los N accidentes de vuelo ya que con cada accidente siempre se apila
    y como mucho en otra iteraci�n se desapilar�, luego siempre es coste lineal.

   *@ </answer> */


#include <iostream>
#include <fstream>
using namespace std;

// ----------------------------------------------------------------
//@ <answer>

#include <stack>
#include <vector>

struct Accidente {
    std::string fecha = "";
    int muertos = -1;
};

bool resuelveCaso() {
    int N;
    cin >> N;
    if (!cin)
        return false;

    std::vector<Accidente> leer;

    for (int i = 0; i < N; ++i) {
        Accidente a;
        std::cin >> a.fecha >> a.muertos;
        leer.push_back(a);
    }

    std::stack<Accidente> accs;
    for (Accidente a: leer) {
        if (accs.empty()) {
            accs.push(a);
            std::cout << "NO HAY\n";
        }
        else {
            if (a.muertos >= accs.top().muertos) {
                while (!accs.empty() && accs.top().muertos <= a.muertos) {
                    accs.pop();
                }
                if (accs.empty()) std::cout << "NO HAY\n";
                else std::cout << accs.top().fecha << '\n';
                accs.push(a);
            }
            else {
                std::cout << accs.top().fecha << '\n';
                accs.push(a);
            }
        }
    }

    std::cout << "---\n";
    return true;
}

//@ </answer>

// �No modificar nada debajo de esta l�nea!
// ----------------------------------------------------------------

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
