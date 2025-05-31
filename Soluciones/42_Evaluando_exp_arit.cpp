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
  * Se añaden iteradores con respecto a la versión anterior.
  */

#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <stack>
#include <cctype>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <vector>

template<class T>
class BinTree {
public:

    BinTree() : root_node(nullptr) { }

    BinTree(const T& elem) : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) { }

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        :root_node(std::make_shared<TreeNode>(left.root_node, elem, right.root_node)) { }


    bool empty() const {
        return root_node == nullptr;
    }

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

    void display(std::ostream& out) const {
        display_node(root_node, out);
    }

private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right) : elem(elem), left(left), right(right) { }

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

/*
 * Operador << para mostrar un árbol por pantalla. No es necesario hacer esto
 * en la práctica, pero os lo dejo por si queréis depurar.
 */
template<typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}


/*
 * Función para leer un árbol binario de la entrada. El formato es el siguiente:
 *
 *  Árbol vacío: .
 *  Árbol no vacío: (i x r)  donde i es la representación del hijo izquierdo
 *                                 x es la raíz
 *                                 r es la representación del hijo derecho
 */
template<typename T>
BinTree<T> read_tree(std::istream& in) {
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

/*
 * Analizador léxico del lenguaje
 */

class Lexer {
public:
    Lexer(std::istream& in) : in(in) { }

    std::string peek() {
        if (next != "") {
            return next;
        }
        else {
            next = read_next();
            return next;
        }
    }

    std::string get() {
        std::string result = peek();
        next = "";
        return result;
    }

private:
    std::istream& in;

    std::string read_next() {
        std::ostringstream result;
        char current;
        in >> current;
        while (iswspace(current)) {
            in >> current;
        }

        if (isdigit(current)) {
            result << current;
            while (isdigit(in.peek())) {
                in >> current;
                result << current;
            }
        }
        else if (isalpha(current)) {
            result << current;
            while (isalnum(in.peek())) {
                in >> current;
                result << current;
            }
        }
        else if (current == '+' || current == '-' || current == '*' || current == ';' || current == '(' || current == ')') {
            result << current;
        }
        else if (current == ':') {
            result << current;
            in >> current;
            if (current != '=') throw std::domain_error("invalid token: :" + current);
            result << current;
        }
        else {
            throw std::domain_error("invalid_token: " + current);
        }

        return result.str();
    }

private:
    std::string next;
};

/*
 * Analizador sintáctico del lenguaje
 */


class Parser {
public:
    Parser(std::istream& in) : l(in) { }

    BinTree<std::string> parse() {
        return S();
    }

private:
    Lexer l;

    bool is_identifier(const std::string& token) {
        return (!token.empty() && isalpha(token[0]));
    }

    bool is_identifier_or_number(const std::string& token) {
        return (!token.empty() && isalnum(token[0]));
    }

    BinTree<std::string> S() {
        std::string identifier = l.get();
        if (!is_identifier(identifier)) throw std::domain_error("identifier expected, found " + identifier);

        std::string equal = l.get();
        if (equal != ":=") throw std::domain_error(":= expected, found " + equal);

        BinTree<std::string> rhs = E();

        std::string semicolon = l.get();
        if (semicolon != ";") throw std::domain_error("; expected, found " + semicolon);

        return { { identifier }, ":=", rhs };
    }

    BinTree<std::string> E() {
        BinTree<std::string> term = T();
        return Ep(term);
    }

    BinTree<std::string> Ep(const BinTree<std::string>& left) {
        std::string op = l.peek();
        if (op == "+" || op == "-") {
            l.get();
            BinTree<std::string> term = T();
            return Ep({ left, op, term });
        }
        else {
            return left;
        }
    }

    BinTree<std::string> T() {
        BinTree<std::string> factor = F();
        return Tp(factor);
    }

    BinTree<std::string> Tp(const BinTree<std::string>& left) {
        std::string op = l.peek();
        if (op == "*") {
            l.get();
            BinTree<std::string> factor = F();
            return Tp({ left, "*", factor });
        }
        else {
            return left;
        }
    }

    BinTree<std::string> F() {
        std::string next = l.get();
        if (is_identifier_or_number(next)) {
            return { next };
        }
        else if (next == "(") {
            BinTree<std::string> inner = E();
            std::string closing = l.get();
            if (closing != ")") throw std::domain_error(") expected, found " + closing);
            return inner;
        }
        else {
            throw std::domain_error("number or identifier expected, found " + next);
        }
    }
};

/*
 * Función que lee una sentencia y devuelve su árbol sintáctico.
 */

BinTree<std::string> parse(std::istream& in) {
    return Parser(in).parse();
}

using namespace std;

/* ======================================================================
 * Escribe tu solución entre las etiquetas "answer" que se muestran a
 * continuación.
 *
 * No es necesario añadir ni modificar ningún método de las clases
 * anteriores, pero puedes implementar las funciones auxiliares
 * que necesites.
 * ====================================================================== */
 /*@ <answer> */

bool isNumber(std::string const& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

bool isOp(std::string const& s) {
    return s == "-" || s == "+" || s == "*";
}

int calculate(BinTree<std::string> const& t, std::unordered_map<std::string, int> const& v) {
    if (t.left().empty() && t.right().empty()) {
        if (isNumber(t.root())) return std::stoi(t.root());
        else return v.at(t.root());
    }
    else {
        int l;
        if (isNumber(t.left().root())) l = std::stoi(t.left().root());
        else {
            if (isOp(t.left().root())) l = calculate(t.left(), v);
            else l = v.at(t.left().root());
        }

        int r;
        if (isNumber(t.right().root())) r = std::stoi(t.right().root());
        else {
            if (isOp(t.right().root())) r = calculate(t.right(), v);
            else r = v.at(t.right().root());
        }

        switch (t.root()[0]) {
        case '-': return l - r;
        case '+': return l + r;
        default: return l * r;
        }
    }
}
/*
Explicación general: Se calculan recursivamente los subárboles izq. y dcho. distinguiendo entre si es el root
un número, un operando o una variable previamente inicializada en una asignación. Después, se prosigue a calcular
el resultado porque root tiene que ser un operando a la fuerza que relacione el resultado del subárbol izq y del dcho.
Así se calcula y se devuelve el resultado de la expresión

Respecto al número de variables, el coste es O(N log N) puesto que la ordenación de las variables al final
domina sobre el coste del bucle principal. En este, cada variable es metida 1 sola vez en el mapa, luego cada
vuelta tiene coste constante en el número de variables resultando en un coste O(n), de menor medida que O(N log N).

Respecto al número de asignaciones, el coste es O(M^2) ya que cada asignación puede depender de
todas las variables asignadas anteriormente (O(1) + O(2) + ... + O(M) ~ O(M^2)).

Respecto al número máximo de nodos, es un recorrido en postorden, luego es de coste O(S) en los S nodos
del árbol parseado.

ESTO NO ES LO QUE SE PEDÍA. SE PEDÍA QUE PUSIESES EL COSTE DEL ALGORITMO EN FUNCIÓN DE TODAS LAS VARIABLES
JUNTAS

En este caso, tiene coste O(M*S + N log N)
*/

bool res() {
    int N; std::cin >> N;
    if (N == 0) return false;
    
    std::unordered_map<std::string, int> variables;
    while (N--) {
        BinTree<std::string> inst = parse(std::cin);
        variables[inst.left().root()] = calculate(inst.right(), variables);
    }

    std::vector<std::string> aux;
    for (auto const& i : variables) {
        aux.push_back(i.first);
    }
    std::sort(aux.begin(), aux.end());

    for (std::string const& s : aux) {
        std::cout << s << " = " << variables[s] << '\n';
    }

    std::cout << "---\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (res());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}