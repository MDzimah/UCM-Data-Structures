#include <iostream>
#include <fstream>

bool resuelveCaso() {
    int N;
    std::cin >> N;
    if (N == 0) return false;

    std::deque<int> ordenado;

    //O(N) <-- HAY QUE JUSTIFICAR EL COSTE!!!
    while (N--) {
        int aux; std::cin >> aux;
        if (aux >= 0) ordenado.push_back(aux);
        else ordenado.push_front(aux);
    }

    //TE PEDÍAN HACER UNA FUNCIÓN QUE RECIBE UNA COLA POR REFERENCIA. OJO ENUNCIADO

    /*Deque es la TAD apropiada ya que el problema así lo exige. 
    Como se dan los números en orden creciente en valor absoluto, aquellos números
    con valor absoluto alto pero que son negativos serán de los primeros elementos mientras
    que los positivos serán de los últimos elementos. Así, los positivos se meten al final y los 
    negativos al principio. Como esta operación es característica de deque, la he eligido para el problema*/

    std::cout << ordenado.front();
    ordenado.pop_front();

    while (!ordenado.empty()) {
        std::cout << ' ' << ordenado.front();
        ordenado.pop_front();
    }
    std::cout << '\n';
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