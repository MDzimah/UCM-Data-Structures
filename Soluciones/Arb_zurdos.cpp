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
/* Hallo recursivamente el número de nodos de tanto el árbol izquierdo como el derecho del root node. Así,
si el número de nodos del árbol izquierdo supera al derecho tiene que ser al menos la mitad de los descendientes del root
obligatoriamente, luego es zurdo. En caso contrario, zurdo es falso.
*/

//Coste
/*
a = 2 al haber 2 llamadas recursivas en el caso recursivo,
b = 2 ya que cada llamada trata la mitad de los nodos (si ni + nd = nTot),
d = 0 ya que lo que se hace en el caso recursivo tiene coste constante
Luego a = 2 > b ^ d = 2 ^ 0 = 1 --> Th.Div.el algoritmo tiene coste O(n ^ logb a) = O(n) donde n es el número de nodos del árbol

* En el caso del árbol degenerado sigue teniendo coste O(n) en el número de nodos del árbol ya que, usando el Th. resta, 
a = 1, b = 1, d = 0 --> El algoritmo tiene coste O(n^(d+1)) = O(n)
*/

//bool: arbol zurdo
//int: num_nodos_tot

template <typename T>
std::pair<bool,int> es_zurdo_aux(const BinTree<T>& t) {
    if (t.empty()) return { true, 0 };
    else if (t.left().empty() && t.right().empty()) return { true, 1 };
    else {
        auto[zurdoL, nL] = es_zurdo_aux(t.left());
        auto[zurdoR, nR] = es_zurdo_aux(t.right());
        return { (nL > nR ? true : false) && zurdoL && zurdoR, nL + nR + 1 };
    }
}


template <typename T>
bool es_zurdo(const BinTree<T>& t) {
    auto [zurdo, n] = es_zurdo_aux(t);
    return zurdo;
}

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

void resuelveCaso() {
    BinTree<char> arbol = read_tree<char>(cin);
    std::cout << es_zurdo(arbol) ? "SI": "NO";
    std::cout << '\n';
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
