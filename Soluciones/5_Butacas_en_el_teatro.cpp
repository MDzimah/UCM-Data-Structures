#include <iostream>
#include <vector>
#include <algorithm>

class Teatro {
public:
    Teatro() {}

    bool nueva_reserva(int inicio, int fin, std::string nombre) {
        //Coste O(n) donde n = fin-inicio

        if (reservas.size() != 0) {
            //Primera reserva tal que r.inicio >= fin
            auto it = std::lower_bound(reservas.begin(), reservas.end(), fin, [](Reserva const& r, int val) { return r.inicio < val;  });

            /*No hay una reserva con su inicio mayor o igual que fin -> todas las reservas tienen un inicio menor que fin ->
            -> con ver si el final del previo (reserva.size()-1) solapa con el inicio conseguimos detectar solapamiento*/
            if (it == reservas.end()) {
                auto previo = std::prev(it);
                if (previo->fin < inicio) {
                    reservas.insert(reservas.end(), { inicio,fin,nombre });
                    return true;
                }
                else return false;
            }
            else {
                //El segmento [inicio,fin] justo solapa con el inicio del segmento representado por el iterador
                if (fin == it->inicio) return false;
                //Vemos si el elemento previo solapa con [inicio,fin]
                else {
                    //Si it apunta a reservas.begin(), esto quiere decir que todos tienen un inicio mayor que fin, luego se puede meter al principio del vector sin problemas
                    if (it == reservas.begin()) {
                        reservas.insert(it, { inicio,fin,nombre });
                        return true;
                    }
                    else {
                        auto previo = std::prev(it);
                        if (previo->fin < inicio) {
                            reservas.insert(it, { inicio,fin,nombre });
                            return true;
                        }
                        else return false;
                    }
                }
            }
        }
        else {
            reservas.push_back({ inicio,fin,nombre });
            return true;
        }
    }

    std::string nombre_reserva(int num_butaca) {
        //Coste O(log n) donde n = reservas.size()
        auto it = std::lower_bound(reservas.begin(), reservas.end(), num_butaca, [](Reserva const& r, int val) { return r.inicio < val;  });

        if (it == reservas.end()) {
            auto previo = std::prev(it);
            if (previo->fin < num_butaca) return "LIBRE";
            else return previo->nombre;
        }
        else {
            if (num_butaca == it->inicio) return it->nombre;
            else {
                if (it == reservas.begin()) return "LIBRE"; 
                else {
                    auto previo = std::prev(it);
                    if (previo->fin < num_butaca) return "LIBRE";
                    else return previo->nombre;
                }
            }
        }
    }

private:
    struct Reserva {
        int inicio, fin;
        std::string nombre;

    };
    std::vector<Reserva> reservas;
};

bool res() {
	int N; int Q; std::cin >> N >> Q;
	if (N == 0 && Q == 0) return false;

    std::string resultado;
	Teatro t;
	for (int i = 0; i < N; ++i) {
		int in, f; std::string nombre;
		std::cin >> in >> f >> nombre;
		if(t.nueva_reserva(in, f, nombre)) resultado += '.';
		else resultado += 'X';
	}
    std::cout << resultado << '\n';

	for (int i = 0; i < Q; ++i) {
		int consulta; std::cin >> consulta;
		std::cout << t.nombre_reserva(consulta) << '\n';
	}
	std::cout << "---\n";

	return true;
}

int main() {
	while (res());
	return 0;
}