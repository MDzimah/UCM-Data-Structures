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

    //int1: equipos requeridos
    //int2: ruta con mayor excursionistas atrapados
    std::pair<int,int> atrapados() {
        return atrapados(root_node);
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

    //Coste O(n) en el número de nodos del árbol por el Th. división (a = 2, b = 2, d = 0 -> O(n logb a))

    //int1: eq_rescates
    //int2: ruta con máximo número de atrapados

    std::pair<int, int> atrapados(const NodePointer& root) {
        if (root != nullptr) {
            //Obtengo el lado derecho e izquierdo de root
            auto[eq_res_L, ruta_max_L] = atrapados(root->left);
            auto [eq_res_R, ruta_max_R] = atrapados(root->right);

            int eq_res_nec, ruta_max;

            //Si en ninguno de los lados hacen falta mandar equipos y root->elem > 0, 
            //tengo que mandar un equipo para rescatar el equipo en root
            if (root->elem > 0 && eq_res_L == 0 && eq_res_R == 0) eq_res_nec = 1;
            else eq_res_nec = eq_res_L + eq_res_R;

            ruta_max = root->elem + std::max(ruta_max_L, ruta_max_R);

            return { eq_res_nec, ruta_max };
        }
        else return {0, 0};
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
    BinTree<int> t = read_tree<int>(std::cin);
    auto[eq_atrapados, ruta_max] = t.atrapados();
    std::cout << eq_atrapados << ' ' << ruta_max << '\n';
}

int main() {
    int nc; std::cin >> nc;
    while (nc--) res();
}