#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Implementa a continuación la función que resuelve un caso de
// prueba. Puedes utilizar otras funciones auxiliares, pon su
// implementación debajo de la etiqueta <answer>.
//@ <answer>

//O(n + nlog n) = O(n log n) ya que al final se ordenan de la solución. Sin embargo, el bucle principal tiene coste O(n)
//ya que al usar unordered_maps (implementadas con tablas hash) las consultas e inserciones tienen todas ellas coste amortizado 
//constante
bool resuelveCaso()
{

    // completar
    std::string entrada;
    std::string deporte;
    std::unordered_map<std::string, std::pair<std::string, bool>> alum_a_dep;
    std::unordered_map<std::string, int> dep_a_numAlums;

    std::getline(std::cin,entrada);

    if (!std::cin) return false;

    while (entrada != "_FIN_")
    {
        //Es un deporte, entonces se inserta en el mapa deportes a numAlums q lo practican
        if (isupper(entrada[0]))
        {
            if (!dep_a_numAlums.count(entrada)) {
                dep_a_numAlums[entrada] = 0;
            }
            deporte = entrada;
        }
        else
        {
            //Es un alumno y ya está en el mapa de alumnos a deporte practicado
            if (alum_a_dep.count(entrada))
            {
                //La primera vez que se inserta el alumno, el value del booleano es "false", es decir, hasta ahora no se ha metido
                //en otro grupo de deporte distinto
                if (!alum_a_dep[entrada].second)
                {
                    //Hay que asegurar que el deporte que tiene asignado es igual a la lista actualmente analizada. Si no, 
                    //hay que borrarle de la lista que tenía como deporte y ponerle como "true". Es decir, ha aparecido 2 veces en listas distintas de deportes
                    if (alum_a_dep[entrada].first != deporte)
                    {
                        --dep_a_numAlums[alum_a_dep[entrada].first];
                        alum_a_dep[entrada].second = true;
                    }
                }
            }
            else
            {
                //El alumno no ha aparecido en ninguna lista de deportes
                alum_a_dep[entrada] = {deporte,false};
                ++dep_a_numAlums[deporte];
            }
        }
        std::getline(std::cin, entrada);
    }
    std::vector<std::pair<std::string, int>> v;
    for (auto const& it : dep_a_numAlums)
    {
        v.push_back({ it.first,it.second });
    }

    std::sort(v.begin(), v.end(), [](std::pair<std::string, int> const& p1, std::pair<std::string, int> const& p2) {
        if (p1.second == p2.second) {
            return p1.first < p2.first;
        }
        else {
            return p2.second < p1.second;
        }
        });

    for (auto const& it : v) {
        std::cout << it.first << " " << it.second << "\n";
    }
    std::cout << "---\n";

    return true;
}

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Visual Studio
    // system("PAUSE");
#endif
    return 0;
}