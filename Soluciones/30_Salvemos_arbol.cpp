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
/* Para el �rbol izq y dcho del nodo ra�z se calcula recursivamente el m�ximo n�mero
de nodos que se pueden salvar si se ha infectado la ra�z respectivamente del �rbol
izq y dcho. Adem�s, se calcula el n�mero de nodos totales de ambos.

Una vez calculados estos resultados, la cuesti�n de cu�l de los dos cortar se reduce
a elegir la combinaci�n que resulte en la suma m�xima de nodos salvados y nodos totales teniendo
en cuenta que no se puede elegir dos veces del mismo "bazo"
*/

//Coste
/*
a = 2 al haber 2 llamadas recursivas en el caso recursivo, 
b = 2 ya que cada llamada trata la mitad de los nodos, 
d = 0 ya que lo que se hace en el caso recursivo tiene coste constante
Luego a = 2 > b ^ d = 2 ^ 0 = 1 --> Th.Div.el algoritmo tiene coste O(n ^ logb a) = O(n) donde n es el n�mero de nodos del �rbol
*/

//int1: max_nodos_salvados
//int2: nodos_arbol
template <typename T>
std::pair<int,int> salvar_Arbol(const BinTree<T>& t) {
   if (t.empty()) return {0,0};
   else {
       auto [mNs_l, N_l] = salvar_Arbol(t.left());
       auto [mNs_r, N_r] = salvar_Arbol(t.right());

       int max_nodos_salvados = std::max(mNs_l + N_r, mNs_r + N_l);

       return { max_nodos_salvados, N_l + N_r + 1 };
   }
}

int salvar_arbol(BinTree<char> const& arbol) {
    auto[max_nodos_salvados, nodos_arbol] = salvar_Arbol(arbol);
    return max_nodos_salvados;
}

//@ </answer>
// �No modificar nada debajo de esta l�nea!
// ----------------------------------------------------------------

void resuelveCaso() {
    BinTree<char> arbol = read_tree<char>(cin);
    assert(!arbol.empty());
    cout << salvar_arbol(arbol) << "\n";
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
