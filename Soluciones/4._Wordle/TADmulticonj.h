#pragma once
#include <iostream>
#include <vector>


class TADmulticonj {
public:

	TADmulticonj() { }

	void insertar(int elem);

	void eliminar(int elem);

	bool pertenece(int elem) const;

private:
	struct Elem {
		long long int valor;
		int multiplicidad;
	};
	std::vector <Elem> elems;
	void eliminarElementoEntero(int m);
	bool busBin(int &ind, int const& elem) const;
};