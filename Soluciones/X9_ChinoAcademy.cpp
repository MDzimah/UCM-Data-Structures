 /*@ <answer>

  Usamos dos mapas desordenados, uno para la informaci�n del estudiante dentro de la academia y otro
  para los grupos (HSK 1 - 6) de la academia (grupo a lista de dni). La informaci�n del estudiante consta
  de un iterador a su posici�n en la lista de los grupos de la academia (iterador), del grupo en el que actualmente est� y si se ha graduado.
  El iterador se guarda ya que reducimos el coste a constante en la promoci�n de los estudiantes de grupo a grupo.
  El booleano graduado es para evitar tener que buscar en el set y que tenga coste constante los m�todos (salvo graduados), aunque no afecta al final 
  el coste asint�tico del TAD.
  Adem�s, usamos un set ordenado para los graduados por su dni.

  Los mapas ordenados los usamos porque esa informaci�n no nos importa que est� ordenada y para tener coste
  constante amortizado en insertar/eliminar/buscar. Sin embargo, llevamos un set ordenado para evitar en 
  la funci�n graduados hacer un sort, el cual tendr�a coste O(n log n) en los n estudiantes graduados. Por ende,
  el TAD acaba teniendo en el caso peor coste O(n) en los n graduados (por �l m�todo graduados).


  Nos da run-error seguramente por un acceso incorrecto por un at. Sin embargo, no fuimos capaz de encontrarlo. No obstante,
  pensamos que la l�gica del problema es correcta y que se ha hecho todo de la forma m�s eficiente posible, justificando
  los costes y estructuras usadas adecuadamente.
  @ </answer> */

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <list>
#include <unordered_map>
#include <set>

using namespace std;

// Elige el tipo representante adecuado para el TAD AcademiaChino e
// implementa sus operaciones. Puedes a�adir m�todos o funciones privadas
// si lo consideras conveniente.
//@ <answer>

using dni = string;
using grupo = int;

class academia_chino {
    struct Estudiante {
        grupo g;
        list<dni>::iterator posEnGrupo;
        bool graduado;
    };
    unordered_map<dni, Estudiante> academia;
    unordered_map<grupo, list<dni>> grupos;
    set<dni> grads;
public:

    academia_chino() {}

    //O(log n) en los n graduados al hacer una consulta en un set ordenado
    void nuevo_estudiante(dni e, grupo g) {
        if (academia.count(e) || grads.count(e)) throw domain_error("Estudiante existente");
        if (g < 1 || g > 6) throw domain_error("Grupo incorrecto");

        grupos[g].push_front(e);
        academia[e] = { g, grupos[g].begin(), false};
    }

    //O(log n) en los n graduados al hacer una inserci�n en un set ordenado
    void promocionar(dni e) {
        if (!academia.count(e)) throw domain_error("Estudiante no existente");
        if (academia[e].graduado) throw domain_error("Estudiante ya graduado");

        int grupo = academia[e].g;
        if (grupo == 6) {
            grupos[grupo].erase(academia[e].posEnGrupo);
            grads.insert(e);
            academia[e].graduado = true;
        }
        else {
            grupos[grupo].erase(academia[e].posEnGrupo);
            int nuevoGrupo = grupo + 1;

            grupos[nuevoGrupo].push_front(e);
            academia[e].posEnGrupo = grupos[nuevoGrupo].begin();
            academia[e].g = nuevoGrupo;
        }
    }

    //O(1)
    int grupo_estudiante(dni e) const {
        if (!academia.count(e)) throw domain_error("Estudiante no existente");
        if (academia.at(e).graduado) throw domain_error("Estudiante ya graduado");

        return academia.at(e).g;
    }

    //O(n) en los n graduados al formarse una lista de los graduados
    list<dni> graduados() const {
        list<dni> gs;
        for (dni const& e : grads) {
            gs.push_back(e);
        }
        return gs;
    }

    //O(1)
    dni novato(grupo g) const {
        if (g < 1 || g > 6) throw domain_error("Grupo incorrecto");
        if (!grupos.count(g) || grupos.at(g).empty()) throw domain_error("Grupo vacio");

        return grupos.at(g).front();
    }
};

//@ </answer>
// �No modificar nada debajo de esta l�nea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    string orden;
    cin >> orden;
    if (!cin)
        return false;

    string dni;
    int grupo;

    academia_chino ac;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo_estudiante") {
                cin >> dni >> grupo;
                ac.nuevo_estudiante(dni, grupo);
            }
            else if (orden == "grupo_estudiante") {
                cin >> dni;
                int grupo = ac.grupo_estudiante(dni);
                cout << dni << " esta en el grupo " << grupo << '\n';
            }
            else if (orden == "promocionar") {
                cin >> dni;
                ac.promocionar(dni);
            }
            else if (orden == "graduados") {
                auto graduados = ac.graduados();
                cout << "Lista de graduados:";
                for (string const& s : graduados) {
                    cout << ' ' << s;
                }
                cout << '\n';
            }
            else if (orden == "novato") {
                cin >> grupo;
                string novato = ac.novato(grupo);
                cout << "Novato de " << grupo << ": " << novato << '\n';
            }
        }
        catch (std::domain_error& e) {
            cout << "ERROR: " << e.what() << '\n';
        }

        cin >> orden;
    }
    cout << "---\n";

    return true;
}

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
