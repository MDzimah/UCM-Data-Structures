#pragma once
#include "Hora.h"
#include <string>

class Pelicula {
public:
	bool operator<(Pelicula& o) const;
	void read(std::istream& in);
	void imprimir(std::ostream& out) const;
	void calcHoraTermina();
private:
	std::string nom;
	Hora h, dur, termina;
};

std::istream& operator>>(std::istream& in, Pelicula& p);
std::ostream& operator<<(std::ostream& out, const Pelicula& p);
