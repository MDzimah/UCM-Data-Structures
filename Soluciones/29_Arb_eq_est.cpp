/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Esta implementación utiliza smart pointers para prevenir
  * fugas de memoria y problemas con la destrucción.
  */

#include <cassert>
#include <iostream>
#include <memory>
#include <tuple>

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
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

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

//bool1: puede perder altura arbol
//bool2: estable arbol
//int: altura arbol

//a = 2, b = 2, d = 0 --> a = 2 > b^d = 2^0 = 1 --> Th. División, el algoritmo tiene coste O(n^logb a) = O(n) en el número de nodos

template <typename T> std::tuple <bool, bool, int> es_estable(const BinTree<T>& t) {
    if (t.empty()) return { false, true, 0};
    else {
        auto [p1, e1, h1] = es_estable(t.left());
        auto [p2, e2, h2] = es_estable(t.right());

        if (!e1 || !e2) return { false, false, -1 };
        else {
            bool p = true, e = true;

            if (p1) {
                if (abs(h1 - 1 - h2) > 1) e = false;
                
                if ((h1 == h2) || (h1 < h2 && !p2)) p = false;
            }
            if (p2) {
                if (abs(h2 - 1 - h1) > 1) e = false;
                
                if ((h1 == h2) || (h2 < h1 && !p1)) p = false;
            }
            
            return { p, e, std::max(h1,h2) + 1 };
        }
    }
}


void res() {
    BinTree<int> t = read_tree<int>(std::cin);
    auto [p, e, a] = es_estable(t);
    if (e) std::cout << "SI\n";
    else std::cout << "NO\n";
}

int main() {
    int nc; std::cin >> nc;
    while (nc--) res();
}