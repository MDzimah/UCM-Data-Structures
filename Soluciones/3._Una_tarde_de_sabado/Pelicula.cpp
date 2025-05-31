#include "Pelicula.h"

bool Pelicula::operator<(Pelicula& o) const {
	if (this->termina < o.termina) return true;
	else if (this->termina == o.termina) {
		return this->nom < o.nom;
	}
	else return false;
}

void Pelicula::read(std::istream& in) {
	in >> this->h >> this->dur;
	std::getline(in,this->nom);
	this->nom = this->nom.substr(1);
}

void Pelicula::imprimir(std::ostream& out) const {
	out << this->termina << ' ' << this->nom << '\n';
}

void Pelicula::calcHoraTermina() {
	this->termina = this->h + this->dur;
}

std::istream& operator>>(std::istream& in, Pelicula& p) {
	p.read(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Pelicula& p) {
	p.imprimir(out);
	return out;
}

