#include <stack>
#include <iostream>
#include <queue>
#include <fstream>

bool resuelveCaso() {
    int N, salto;
    std::cin >> N >> salto;
    if(N == 0 && salto == 0) return false;
 
    std::queue<int> alumnos; //Es un stack pero FIFO en lugar de LIFO
   
    for (int i = 1; i <= N; ++i)
        alumnos.push(i);

    int cont = 0;

    //O(n^2) donde n = alumnos.size()
    while (alumnos.size() > 1) {
        std::queue<int>alumPotSalen;

        while (!alumnos.empty()) {
            if (cont == salto) cont = 0;
            else {
                alumPotSalen.push(alumnos.front());
                ++cont;
            }
            alumnos.pop();
        }

        alumnos = alumPotSalen; //Alumnos vuelve a ser los alumnos que pueden salir a la pizarra
    }

    /* SE PUEDE USAR SOLO UNA COLA:
    
    while (cola.size() > 1){
        int se_quedan K % cola.size();
        while (se_quedan--){
            cola.push(cola.front());
            cola.pop();
        }
    }
    
    */

    std::cout << alumnos.front() << '\n';

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}