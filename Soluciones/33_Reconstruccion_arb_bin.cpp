#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <vector>
#include <stack>

  /*
    Implementación de la clase BinTree para representar árboles binarios.

    Para realizar este ejercicio no es necesario modificar la clase.
   */

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


using namespace std;
// ----------------------------------------------------------------
// ¡No modificar nada importante por encima de esta línea!

// Implementa a continuación la función pedida. Puedes definir las funciones
// auxiliares que necesites.
//@ <answer>

BinTree<int> reco(const std::vector<int>& preorden, const std::vector<int>& inorden, int p_ini, int p_fin, int i_ini, int i_fin) {
    if (p_ini == p_fin) {
        return BinTree<int>();
    }
    else if (p_ini + 1 == p_fin) {
        return BinTree<int>(preorden[p_ini]);
    }
    else {
        int root = preorden[p_ini];
        int i = i_ini;
        //Encontrar posRoot en el subárbol actual
        while (i != i_fin && inorden[i] != root) ++i;

        int nodos_subarb_L = i - i_ini; //Todos los nodos antes del root en el inorden forman parte del subarbol izq
        //p_ini + 1 --> root de subarb izq
        //[p_ini + 1, p_ini + 1 + nodos_subarb_L) --> los nodos a procesar en el preorden
        //Para i_ini, i es análogo pero tomando en cuenta el inorden
        BinTree<int> left = reco(preorden, inorden, p_ini + 1, p_ini + 1 + nodos_subarb_L, i_ini, i);

        //Después de construir el subarb izq, comenzamos a construir el dcho a partir de p_ini+1 + nodosSubarb_L hasta p_fin (el final del segmento actual preorden)
        //i+1 ya que todo después de i es del subarb dcho
        BinTree <int> right = reco(preorden, inorden, p_ini + 1 + nodos_subarb_L, p_fin, i + 1, i_fin);
        return BinTree<int>(left, root, right);
    }
}

BinTree<int> reconstruir(vector<int> const& preorden, vector<int> const& inorden) {
    return reco(preorden, inorden, 0, preorden.size(), 0, inorden.size());
}

bool resuelveCaso() {

    // leemos la entrada
    int N;
    cin >> N;
    if (!cin)
        return false;

    vector<int> preorden(N);
    for (int& c : preorden) {
        cin >> c;
    }

    vector<int> inorden(N);
    for (int& c : inorden) {
        cin >> c;
    }

    auto arbol = reconstruir(preorden, inorden);
    cout << arbol << '\n';
    return true;
}

/*@ </answer> */

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());


#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
