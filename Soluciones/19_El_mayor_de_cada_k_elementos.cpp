#include <iostream>
#include <fstream>
#include <queue> 
#include <vector>

//A veces se borran elementos, otras veces no. En el caso peor, esta
//eliminación de elementos hace que el coste sea O(N),
//el cual es lineal
void insertar_max_dq(std::deque<int>& max_dq, int elem) {
    while (!max_dq.empty() && max_dq.back() < elem) {
        max_dq.pop_back();
    }
    max_dq.push_back(elem);
}

bool res() {
    int N, k; std::cin >> N >> k;
    if (!std::cin) return false;

    std::queue<int> segmento;
    std::deque<int> max_dq;
    std::vector<int> sol;
    
    for (int i = 0; i < k; ++i) {
        int x; std::cin >> x;
        segmento.push(x);
        insertar_max_dq(max_dq, x);
    }
    sol.push_back(max_dq.front());

    for (int i = 0; i < N - k; ++i) {
        int x; std::cin >> x;
        if (segmento.front() == max_dq.front()) {
            max_dq.pop_front();
        }
        segmento.pop();
        segmento.push(x);
        insertar_max_dq(max_dq, x); 
        sol.push_back(max_dq.front());
    }

    /* Coste O(N). En cada iteración se realizan operaciones todas ellas de coste constante
    * excepto insertar_max_dq pero la suma de todas las llamadas a esta funcion tiene coste
    * lineal en el caso peor puesto que se eliminan todos los elementos de la lista además de 
    * insertarlos en la deque.
    */

    for (int i = 0; i < sol.size() - 1; ++i) {
        std::cout << sol[i] << ' ';
    }
    std::cout << sol[sol.size() - 1] << '\n';
        
    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero


#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (res());


    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif


    return 0;
}