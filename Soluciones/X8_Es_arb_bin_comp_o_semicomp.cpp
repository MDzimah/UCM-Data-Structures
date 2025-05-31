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

//bool1: completo
//bool2: semicompleto
//int1: altura árbol

template <typename T>
std::tuple<bool, bool, int> arb_bin_comp_o_semi(const BinTree<T>& t) {
    if (t.empty())return { true, true, 0 };
    else {
        auto[comp_l, semicomp_l, hL] = arb_bin_comp_o_semi(t.left());
        auto [comp_r, semicomp_r, hR] = arb_bin_comp_o_semi(t.right());

        if (hL == hR && comp_l && comp_r) return { true, true, hR + 1 };
        else if ((hL == hR + 1 && semicomp_l && comp_r) || (hL == hR && comp_l && semicomp_r)) return { false, true, hL + 1 };
        else return { false, false, -1 };
    }
}

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

void resuelveCaso() {
    BinTree<char> arbol = read_tree<char>(cin);
    auto [completo, semi, h] = arb_bin_comp_o_semi(arbol);

    if (completo) std::cout << "COMPLETO\n";
    else if (semi) std::cout << "SEMICOMPLETO\n";
    else std::cout << "NADA\n";
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