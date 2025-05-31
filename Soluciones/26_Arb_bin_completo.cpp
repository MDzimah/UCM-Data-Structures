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
#include <utility>

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
    bool completo() {
        std::pair<bool, int> res = completo(root_node);
        return res.first;
    }

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

    //Coste O(n) en el número de nodos del árbol por el Th. de la división

    //bool: arbol completo
    //int: altura árbol
    std::pair<bool, int> completo(const NodePointer& root) {
        //Árbol vacío
        if (root == nullptr) {
            return { true, 0 };
        }
        //Árbol con al menos 1 elem
        else {
            if (root->left == nullptr && root->right == nullptr) return { true, 1 };
            else {
                if (root->left == nullptr || root->right == nullptr) return { false, -1 };
                else {
                    std::pair<bool, int> l = completo(root->left);
                    std::pair<bool, int> r = completo(root->right);
                    
                    if (l.first && r.first && (l.second == r.second)) {
                        return { true, l.second + 1 };
                    }
                    else return { false, -1 };
                }
            }
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


void res() {
    BinTree<char> t = read_tree<char>(std::cin);
    if (t.completo()) std::cout << "SI\n";
    else std::cout << "NO\n";
}

int main() {
    int nc; std::cin >> nc;
    while (nc--) res();
}