#include <cassert>
#include <iostream>
#include <fstream>
#include <iterator>
#include <memory>
#include <queue>
#include <stack>

template <class T> class BinTree {

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

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

    template <typename U> void preorder(U func) const {
        preorder(root_node, func);
    }

    template <typename U> void inorder(U func) const {
        std::stack<NodePointer> st;

        descend_and_push(root_node, st);

        while (!st.empty()) {
            NodePointer current = st.top();
            st.pop();

            func(current->elem);

            descend_and_push(current->right, st);
        }
    }

    template <typename U> void postorder(U func) const {
        postorder(root_node, func);
    }

    template <typename U> void levelorder(U func) const;

    class iterator {
    public:
        const T& operator*() const {
            assert(!st.empty());
            return st.top()->elem;
        }

        const T* operator->() const { return &operator*(); }

        iterator& operator++() {
            assert(!st.empty());
            NodePointer top = st.top();
            st.pop();
            BinTree::descend_and_push(top->right, st);
            return *this;
        }

        iterator operator++(int) {
            iterator previous = *this;
            ++(*this);
            return previous;
        }

        bool operator==(const iterator& other) const { return st == other.st; }

        bool operator!=(const iterator& other) const {
            return !this->operator==(other);
        }

    private:
        friend class BinTree;

        iterator() {}

        iterator(const NodePointer& root) { BinTree::descend_and_push(root, st); }

        std::stack<NodePointer> st;
    };

    iterator begin() const { return iterator(root_node); }

    iterator end() const { return iterator(); }

private:
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

    static void descend_and_push(const NodePointer& node,
        std::stack<NodePointer>& st);

    template <typename U> static void preorder(const NodePointer& node, U func);

    template <typename U> static void postorder(const NodePointer& node, U func);
};

template <typename T>
void BinTree<T>::descend_and_push(const NodePointer& node,
    std::stack<NodePointer>& st) {
    NodePointer current = node;
    while (current != nullptr) {
        st.push(current);
        current = current->left;
    }
}

template <typename T>
template <typename U>
void BinTree<T>::preorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        func(node->elem);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::postorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        postorder(node->left, func);
        postorder(node->right, func);
        func(node->elem);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::levelorder(U func) const {
    std::queue<NodePointer> pending;
    if (root_node != nullptr) {
        pending.push(root_node);
    }
    while (!pending.empty()) {
        NodePointer current = pending.front();
        pending.pop();
        func(current->elem);
        if (current->left != nullptr) {
            pending.push(current->left);
        }
        if (current->right != nullptr) {
            pending.push(current->right);
        }
    }
}

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

//int1: alt max subArb comp
//int2: alt max subArb comp conecta
//bool: hay subArb completo hasta el root

/* Considero el caso peor, �rbol degenerado
0 <= n < 2, T(n) = k0*n^0 
n >= 2, T(n) = T(ni) + T(nd) + k1*n^0 = 1*T(n) + 0 + k1*n^0
Por Th. Resta, T(n) pertenece al orden O(n^0+1) = O(n)
*/
std::tuple<int, int, bool> subArbCompMasGrandeAux(BinTree<char> const& t) {
    if (t.empty()) return { 0, 0, true };
    else {
        auto [altL_subMax, altL_subMax_c, compL] = subArbCompMasGrandeAux(t.left());
        auto [altR_subMax, altR_subMax_c, compR] = subArbCompMasGrandeAux(t.right());

        bool comp = compL && compR && altL_subMax_c == altR_subMax_c;
        int altSubMax_c = 1;
        //O conecta el �rbol, o no lo hace. En el caso q no, el �nico subarbol conectable m�s grande posible es el m�nimo de ambos lados conectables
        if (comp) altSubMax_c += altR_subMax_c;
        else if (!t.left().empty() && !t.right().empty()) {
            altSubMax_c += std::min(altL_subMax_c, altR_subMax_c);
            comp = true;
        }

        int altSubMax = std::max(altSubMax_c, std::max(altL_subMax, altR_subMax));

        return { altSubMax, altSubMax_c, comp };
    }
}

int subArbCompMasGrande(BinTree<char> const& t) {
    auto [altMaxSubArb, altMaxSubArb_c, b] = subArbCompMasGrandeAux(t);
    return std::max(altMaxSubArb, altMaxSubArb_c);
}

void res() {
    BinTree<char> t = read_tree<char>(std::cin);
    std::cout << subArbCompMasGrande(t) << '\n';
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int nc; std::cin >> nc;
    while (nc--) res();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Visual Studio
    // system("PAUSE");
#endif
    return 0;
}