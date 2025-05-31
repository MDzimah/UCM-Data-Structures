/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (ED-DGXX) de los autores de la soluci�n (cada uno en una l�nea).
 *
 *@ </authors> */

 /*@ <answer>

  Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
  se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
  del tama�o del problema.

  @ </answer> */

#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>


  // Clase para representar �rboles binarios.
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
// Define aqu� la funci�n pedida en el enunciado.
// Puedes definir las funciones auxiliares que necesites, pero siempre
// entre las marcas 
//@ <answer>

//Explicaci�n breve
/* Calculo el �rea m�ximo de tanto el �rbol izq. como el dcho. adem�s de el m�ximo �rea posible sin ninguna barrera
hasta llegar al root actual. Con estos datos calculados, hallo el m�ximo �rea que puedo construir uniendo las m�ximas
�reas hasta el root de left y right solo si root es false (si root==true, no es posible "unir" las �reas izq y dcha m�ximas 
sin barreras hasta el nodo root). As�, el �rea m�xima del �rbol entero va a ser el m�ximo de estos tres: el area unida, el �rea m�ximo 
del izq y el �rea m�ximo del dcho.
*/

//Coste
/*
* T(n) = aT(n/b) + n^d si n >= b, coste cte si n < b
a = 2 al haber 2 llamadas recursivas en el caso recursivo,
b = 2 ya que cada llamada trata la mitad de los nodos (si ni/2 ~ nf/2),
d = 0 ya que lo que se hace en el caso recursivo tiene coste constante
Luego a = 2 > b ^ d = 2 ^ 0 = 1 --> Th.Div.el algoritmo tiene coste O(n ^ logb a) = O(n) donde n es el n�mero de nodos del �rbol

* En el caso del �rbol degenerado sigue teniendo coste O(n) en el n�mero de nodos del �rbol ya que, usando el Th. resta,
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
// �No modificar nada debajo de esta l�nea!
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
