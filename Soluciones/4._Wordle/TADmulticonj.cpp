#include "TADmulticonj.h"



void TADmulticonj::eliminarElementoEntero (int m) {

	for (int i = m; i < elems.size() - 1; ++i) {
		elems[i] = elems[i + 1];
	}
	elems.pop_back();
}

bool TADmulticonj::busBin(int &ind, int const& elem) const {
	int i = -1; ind = elems.size();
	while (i + 1 != ind) {
		int m = (i + ind) / 2;
		if (elems[m].valor < elem) i = m;
		else ind = m;
	}
	return ind != elems.size() && elems[ind].valor == elem;
}

void TADmulticonj::eliminar(int elem) {

	int i = 0;
	while (elem != elems[i].valor) 
		++i;

	if (elems[i].multiplicidad == 1) eliminarElementoEntero(i);
	else if (i < elems.size()) 
		--elems[i].multiplicidad;

}

bool TADmulticonj::pertenece(int elem) const {
	int ind;
	return busBin(ind, elem);
}

void TADmulticonj::insertar(int elem) {
	int ind;
	if (busBin(ind, elem)) ++elems[ind].multiplicidad;
	else {
		elems.push_back({ 0,0 });
		for (int i = elems.size() - 1; i > ind; --i) {
			elems[i] = elems[i - 1];
		}
		elems[ind] = { elem, 1 };
	}
}
