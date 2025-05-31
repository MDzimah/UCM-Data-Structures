#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>


bool esVocal(char c) { 
    c = std::tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; 
}

void meterInv(std::string& s, std::stack<char> & invert) {
    while (!invert.empty()) {
        s += invert.top();
        invert.pop();
    }
}

bool resuelveCaso() {
    std::string s; std::getline(std::cin, s);
    if (!std::cin) return false;

    std::string X_2P;
    std::string X_P;
    std::string X;

    //O(X_2P.size())
    
    //Conversión X'' a X'
    int i = 0;

    //Si el size del caso es impar, hay que asegurar que el último
    //elemento desemparejado quede en la parte primera, segunda, tercera,etc.
    //del string y no en la parte última, penúltima,etc. del string

    /*
    Con deque
    Los impares se meten al principio y los pares
    al final, luego para el siguiente paso hay que
    cambiar ambos tramos de orden para hacer la última conversión
    */
    if (s.size() % 2 == 0) {
        for (int i = 0; i < s.size(); i += 2) X_P += s[i];
        for (int i = s.size() - 1; i >= 0; i -= 2) X_P += s[i];
    }
    else {
        for (int i = 0; i < s.size(); i += 2) X_P += s[i];
        for (int i = s.size() - 2; i >= 0; i -= 2) X_P += s[i];
    }

    std::stack<char> invert;
    //Conversión primera parte de X' a X
   for (char c: X_P) {
        if (!esVocal(c)) {
            invert.push(c);
        }
        else {
            //Meter lo invertido
            meterInv(X, invert);

            //Se mete la vocal
            X += c;
        }
    }

    //Pueden quedar parte de invert sin meter adecuadamente en X'
    meterInv(X, invert);

    std::cout << X << '\n';
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