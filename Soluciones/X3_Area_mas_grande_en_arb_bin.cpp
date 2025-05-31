/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (ED-DGXX) de los autores de la solución (cada uno en una línea).
 *
 *@ </authors> */

 /*@ <answer>

  Escribe aquí un comentario general sobre la solución, explicando cómo
  se resuelve el problema y cuál es el coste de la solución, en función
  del tamaño del problema.

  @ </answer> */

#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>


  // Clase para representar árboles binarios.
  // No es posible modificar esta clase para el problema de hoy

template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}


using namespace std;


// ----------------------------------------------------------------
// Define aquí la función pedida en el enunciado.
// Puedes definir las funciones auxiliares que necesites, pero siempre
// entre las marcas 
//@ <answer>

//Explicación breve
/* Calculo el área máximo de tanto el árbol izq. como el dcho. además de el máximo área posible sin ninguna barrera
hasta llegar al root actual. Con estos datos calculados, hallo el máximo área que puedo construir uniendo las máximas
áreas hasta el root de left y right solo si root es false (si root==true, no es posible "unir" las áreas izq y dcha máximas 
sin barreras hasta el nodo root). Así, el área máxima del árbol entero va a ser el máximo de estos tres: el area unida, el área máximo 
del izq y el área máximo del dcho.
*/

//Coste
/*
* T(n) = aT(n/b) + n^d si n >= b, coste cte si n < b
a = 2 al haber 2 llamadas recursivas en el caso recursivo,
b = 2 ya que cada llamada trata la mitad de los nodos (si ni/2 ~ nf/2),
d = 0 ya que lo que se hace en el caso recursivo tiene coste constante
Luego a = 2 > b ^ d = 2 ^ 0 = 1 --> Th.Div.el algoritmo tiene coste O(n ^ logb a) = O(n) donde n es el número de nodos del árbol

* En el caso del árbol degenerado sigue teniendo coste O(n) en el número de nodos del árbol ya que, usando el Th. resta,
a = 1, b = 1, d = 0 --> El algoritmo tiene coste O(n^(d+1)) = O(n)
*/

//int: max_area
//int: max_area_sin_barrera_hasta_root

template <typename T>
std::pair<int, int> area_mayor_sin_barreras_aux(const BinTree<T>& t) {
    if (t.empty()) return { 0,0 };
    else {
        auto [max_area_L, max_a_sbhr_L] = area_mayor_sin_barreras_aux(t.left());
        auto [max_area_R, max_a_sbhr_R] = area_mayor_sin_barreras_aux(t.right());
        
        int max_joined = 0;
        
        if (t.root() == 'V') {
            ++max_joined;
            max_joined += max_a_sbhr_L;
            max_joined += max_a_sbhr_R;
        }

        return { std::max(max_joined, std::max(max_area_L, max_area_R)), max_joined };
    }
}


template <typename T>
int area_mayor_sin_barreras(const BinTree<T>& t) {
    auto [max_area, max_a_sbhr] = area_mayor_sin_barreras_aux(t);
    return max_area;
}

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

void resuelveCaso() {
    BinTree<char> arbol = read_tree<char>(cin);
    std::cout << area_mayor_sin_barreras(arbol) << '\n';
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int num_casos;
    cin >> num_casos;
    while (num_casos--) {
        resuelveCaso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
