#include <cassert>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <string>

using namespace std;

//O(n) en las n líneas de código
bool res() {
    int N; std::cin >> N;

    if (!std::cin) return false;

    unordered_map<string, string> st_to_end; //Asociamos los starters a los enders
    unordered_set<string> enders; //No es necesario saber la relación inversa, luego guardamos los enders en un set
    stack<string> code;

    string starter, ender;
    while (N--) {
        std::cin >> starter >> ender;
        st_to_end[starter] = ender;
        enders.insert(ender);
    }


    std::cin >> N;

    string s;
    bool valid = true;
    while (N-- && valid) {
        cin >> s;
        if (st_to_end.count(s)) code.push(s);
        else if (enders.count(s)) {
            if (!code.empty() && st_to_end[code.top()] == s) code.pop();
            else valid = false;
        }
    }

    if (!valid) std::getline(std::cin, s);

    cout << ((valid && code.empty()) ? "SI\n" : "NO\n");
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (res());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Visual Studio
    // system("PAUSE");
#endif
    return 0;
}
