#include <iostream>
#include <stack>
#include <fstream>

bool resuelveCaso() {
    int N; std::cin >> N; //N >= 3
    if (!std::cin) return false;

    std::stack<int> alt;

    while (N--) {
        int aux; std::cin >> aux;
        alt.push(aux);
    }
    
    /*Explicaci�n de la soluci�n:
    Sin saber ninguna estructura de datos,
    el coste ser�a O(N^3) ya que hay que mirar todos los
    tripletes posibles y ver si existe al menos uno de la forma {a, b, c} donde
    a < c < b para concluir que se quedan sin premio.
    
    Almaceno los datos en una pila porque me interesa el LIFO para
    acceder a los elementos de atr�s.
     
    El razonamiento del algoritmo se explica en el propio c�digo a continuaci�n
    */

    /*Coste O(N) ya que en cada iteraci�n se realizan operaciones de coste constante,
    salvo quiz�s el �ltimo "else", que aunque es un bucle, la pila no se vac�a cada
    iteraci�n, luego se puede tomar como constante este vac�o*/

    //Ordenada de mayor a menor candidatos a mediano
    std::stack<int> c_altMedia;
    int cand_med = -1; //Hemos encontrado un "b" para este candidato 100%
    bool encontrado = false;

    //Inicializo c_altMedia
    c_altMedia.push(alt.top());
    alt.pop();

    while (!alt.empty() && !encontrado) {
        if (cand_med != -1 && cand_med > alt.top()) {
            //Para pillar combinaci�n sin premio
            encontrado = true;
        }
        else if (c_altMedia.top() > alt.top()) {
            /*Es un elemento menor que todos los que tenemos en la pila. Hay que
            meterlo porque justo podr�a aparecer una combinaci�n sin premio*/ 
            c_altMedia.push(alt.top()); 
        }
        else {
            /*Es un elemento mayor que el que ahora es top de nuestra pila de 
            medianos. Ahora, buscamos nuestro mejor candidato a medio
            en la pila que tenemos y lo guardamos en cand_med*/
            while (!c_altMedia.empty() && c_altMedia.top() < alt.top()) {
                cand_med = c_altMedia.top();
                c_altMedia.pop();
            }
            c_altMedia.push(alt.top());
        }
        alt.pop();
    }
   
    if (encontrado) std::cout << "ELEGIR OTRA\n";
    else std::cout << "SIEMPRE PREMIO\n";

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero

 /*
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
*/
    while (resuelveCaso());
  
  /*
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
*/
    return 0;
}