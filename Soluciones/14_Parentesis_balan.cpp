#include <string>
#include <stack>
#include <iostream>
#include <fstream>

using namespace std;

bool resuelveCaso() {
    string s;
    getline(cin, s);
    if (!cin) return false;
    stack<char> pila;
    bool b = true;
    for (int i = 0; i < s.size() && b; ++i) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') pila.push(s[i]);
        else if (s[i] == ')' || s[i] == '}' || s[i] == ']') {
            if (!pila.empty() && ((s[i] == ')' && pila.top() == '(') || (s[i] == '}' && pila.top() == '{') || (s[i] == ']' && pila.top() == '['))) {
                pila.pop();
            }
            else b = false;
        }
    }

    if (b && pila.empty()) cout << "SI\n";
    else cout << "NO\n";
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