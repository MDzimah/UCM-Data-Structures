#pragma once
#include "Pelicula.h"
#include <vector>
#include <algorithm>

class Cartelera {
public:
	Cartelera(int numPelis) { c = std::vector<Pelicula>(numPelis); }
	void read(std::istream& in);
	void imprimir(std::ostream& out) const;
	void ordenar();

private:
	std::vector <Pelicula> c;
};

std::istream& operator>>(std::istream& in, Cartelera& c);
std::ostream& operator<<(std::ostream& out, Cartelera const& c);