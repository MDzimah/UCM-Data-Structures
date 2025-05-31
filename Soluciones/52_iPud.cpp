#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <unordered_map>
#include <set>
using namespace std;

// Elige el tipo representante adecuado para el TAD e implementa
// sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente.
//@ <answer>

/*
Breve explicación:
Llevo:
- un mapa no ordenado para las canciones
- 2 listas, una para las canciones a ser reproducidas (listRepro) y otra de las que
se reproducen (listPlayed), junto con un mapa no ordenado de nombre canción a iteradores a las posiciones dentro
de cada una de las listas
- variable acumuladora int para llevar el tiempo total de la listRepro

Los métodos addSong, current, totalTime, recent son triviales. Explico los otros:
addToPlayList: añado la song desde el mapa de songs a listRepro y su iterador al mapa correspondiente, asegurando aumentar timeRepro adecuadamente
play: es como current pero quito la primera song de listRepro y hago push_FRONT en listPlayed ya que listPlayed está ordenada de menos a más recientemente reproducida.
Hago todas las actualizaciones correspondientes a los mapas de iteradores, eliminando en repro y añadiendo en play. En play me aseguro borrar instancias previas ya que 
solo me interesa las más recientes
deleteSong: Quito de repro todo si es que la canción se halla en listRepro. Si no está en repro, tiene que estar en played, luego quito de ahí todo. Finalmente borro la canción
del sistema mediante el unordered_map de songs

Coste: todos los métodos tienen coste constante ya que insertar, eliminar, acceder tienen coste constante amortizado en un unordered_map. En las listas, todas las operaciones hechas
tienen coste constante gracias al mapa apuntando a las posiciones dentro de ambas listas, asegurando no tener que recorrerlas para encontrar las canciones a borrar.
El único método con coste no constante es el de recent, el cual tiene coste O(R) en las R canciones reales que son devueltas como canciones recientes
reproducidas.
El TAD tiene coste, por tanto, O(R)
*/
using S = string;
using A = string;

class iPud {
    struct Song {
        S nom;
        int dur;
    };
    unordered_map<S, pair<A, int>> songs;
    list<Song> listRepro;
    int timeRepro = 0;
    list<Song> listPlayed;
    unordered_map<S, list<Song>::iterator> posEnListRepro;
    unordered_map<S, list<Song>::iterator> posEnListPlay;
public:
    iPud() {}

    //O(1)
    void addSong(S const& song, A const& artista, int dur) {
        if (!songs.count(song)) songs[song] = { artista, dur };
        else throw domain_error("addSong");
    }

    //O(1)
    void addToPlaylist(S const& song) {
        if (songs.count(song)) {
            if (!posEnListRepro.count(song)) {
                listRepro.push_back({ song, songs[song].second });
                posEnListRepro[song] = --listRepro.end();
                timeRepro += songs[song].second;
            }
          }
        else throw domain_error("addToPlaylist");
    }

    //O(1)
    S current() const {
        if (!listRepro.empty()) return listRepro.begin()->nom;
        else throw domain_error("current");
    }

    //O(1)
    S play() {
        if (!listRepro.empty()) {
            Song song = { listRepro.begin()->nom, listRepro.begin()->dur };

            //Nos aseguramos de no tener duplicados
            if (posEnListPlay.count(song.nom)) {
                listPlayed.erase(posEnListPlay[song.nom]);
                posEnListPlay.erase(song.nom);
            }

            listPlayed.push_front(song);
            posEnListPlay[song.nom] = listPlayed.begin();

            timeRepro -= songs[listRepro.front().nom].second;
            posEnListRepro.erase(listRepro.begin()->nom);
            listRepro.pop_front();
            
            return song.nom;
        }
        else return "";
    }

    //O(1)
    int totalTime() const {
        return timeRepro;
    }

    //O(R) donde R <= N es el número de canciones recientemente reproducidas. En caso peor O(N) obviamente
    list<S> recent(int N) const {
        if (listPlayed.empty()) return {};
        else {
            list<S> list;
            N = std::min((int)listPlayed.size(), N);

            auto it = listPlayed.begin();
            while (N--) {
                list.push_back(it->nom);
                ++it;
            }

            return list;
        }
    }

    //O(1)
    void deleteSong(S const& song) {
        if (songs.count(song)) {
            if (posEnListRepro.count(song)) {
                timeRepro -= songs[song].second;
                listRepro.erase(posEnListRepro[song]);
                posEnListRepro.erase(song);
            }

            if (posEnListPlay.count(song)) {
                listPlayed.erase(posEnListPlay[song]);
                posEnListPlay.erase(song);
            }
            
            songs.erase(song);
        }
    }
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    S song; A artista; int dur;
    string orden;
    std::cin >> orden;
    if (!std::cin)
        return false;

    iPud dispositivo;

    while (orden != "FIN") {
        try {
            if (orden == "addSong") {
                cin >> song >> artista >> dur;
                dispositivo.addSong(song, artista, dur);
            }
            else if (orden == "addToPlaylist") {
                cin >> song;
                dispositivo.addToPlaylist(song);
            }
            else if (orden == "current") {
                song = dispositivo.current();
            }
            else if (orden == "play") {
                song = dispositivo.play();
                if (song == "") cout << "No hay canciones en la lista\n";
                else cout << "Sonando " << song << '\n';
            }
            else if (orden == "totalTime") {
                dur = dispositivo.totalTime();
                cout << "Tiempo total " << dur << '\n';
            }
            else if (orden == "recent") {
                int N; cin >> N;
                auto const& lista = dispositivo.recent(N);

                if (lista.empty()) cout << "No hay canciones recientes\n";
                else {
                    cout << "Las " << lista.size() << " mas recientes\n";
                    for (auto const& s : lista) {
                        cout << "    " << s << '\n';
                    }
                }
            }
            else {
                cin >> song;
                dispositivo.deleteSong(song);
            }
               
        }
        catch (std::domain_error& e) {
            std::cout << "ERROR " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
