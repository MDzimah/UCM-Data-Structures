/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Introduce el nombre y apellidos de los/as componentes del grupo:
  *
  * Estudiante 1:
  * Estudiante 2:
  *
  */

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <map>
#include <functional>

using namespace std;

class ConteoVotos {
    using Est = string;
    using Part = string;
    struct infoEst {
        int numComprom;
        Part gana;
        unordered_map<Part, int> partidos;
    };
    unordered_map <Est, infoEst> estados;
    map <Part, int> compromPorPartido; //Para que los partidos estén ordenados alfabéticamente
    
public:
    //O(1)
    void nuevo_estado(const string& nombre, int num_compromisarios) {
        if (!estados.count(nombre)) {
            estados[nombre] = { num_compromisarios, "", unordered_map<Part,int>() };
        }
        else throw std::domain_error("Estado ya existente");
    }

    //O(log P)
    void sumar_votos(const string& estado, const string& partido, int num_votos) {
        if (estados.count(estado)) {
            //Partido registrado con votos en el estado
            auto& est = estados[estado];
            auto& partsEst = est.partidos;
            
            if (partsEst.count(partido)) partsEst[partido] += num_votos;
            else partsEst[partido] = num_votos;

            if (est.gana == "") {
                est.gana = partido;

                if (compromPorPartido.count(partido)) compromPorPartido[partido] += est.numComprom;
                else compromPorPartido[partido] = est.numComprom;
            }
            else {
                auto votosPartAnalizado = partsEst[partido];
                //El número de votos del partido actual analizado supera el que tenía mayor número de votos en el estado antes
                if (votosPartAnalizado > est.partidos[est.gana]) {
                    compromPorPartido[est.gana] -= est.numComprom;
                    
                    est.gana = partido;

                    //El partido puede superar el número de votos del máximo de antes en su primer registro en el estado
                    if (compromPorPartido.count(partido)) compromPorPartido[partido] += est.numComprom;
                    else compromPorPartido[partido] = est.numComprom;
                }
            }
        }
        else throw std::domain_error("Estado no encontrado");
    }

    //O(1)
    string ganador_en(const string& estado) const {
        if (estados.count(estado)) {
            return estados.at(estado).gana;
        }
        else throw std::domain_error("Estado no encontrado");
    }

    //O(P) donde "P" es el número de partidos
    vector<pair<string, int>> resultados() const {
        std::vector<pair<string, int>> res;
        for (auto const& it : compromPorPartido) {
            //En los resultados solo nos interesa a aquellos partidos con compromisarios > 0
            if (it.second > 0) res.push_back({ it.first, it.second });
        }
        return res;
    }

    //Coste final es O(P + log P) = O(P)
};


bool resuelveCaso() {
    string operacion, estado, partido;
    int compromisarios, votos;
    cin >> operacion;
    if (!cin)
        return false;

    ConteoVotos CV;

    while (operacion != "FIN") {
        try {
            if (operacion == "nuevo_estado") {
                cin >> estado >> compromisarios;
                CV.nuevo_estado(estado, compromisarios);
            }
            else if (operacion == "sumar_votos") {
                cin >> estado >> partido >> votos;
                CV.sumar_votos(estado, partido, votos);
            }
            else if (operacion == "ganador_en") {
                cin >> estado;
                auto ganador = CV.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << ganador << '\n';
            }
            else if (operacion == "resultados") {
                for (auto [estado, compromisarios] : CV.resultados()) {
                    cout << estado << ' ' << compromisarios << '\n';
                }
            }
        }
        catch (domain_error& e) {
            cout << e.what() << '\n';
        }
        cin >> operacion;
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
