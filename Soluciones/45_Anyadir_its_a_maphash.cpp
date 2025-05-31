/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (ED-DGxx) de los autores de la solución (sustituye esta línea por esos datos; si sois dos, uno en cada línea).
 *
 *@ </authors> */


 /*@ <answer>

   Sustituye este párrafo por una explicación de tu solución y una justificación del coste.

  *@ </answer> */




  /*
   * Implementación del TAD Diccionario mediante tablas hash
   * abiertas. La tabla se redimensiona a medida que el factor
   * de carga supera MAX_LOAD_FACTOR
   */

#include <cassert>
#include <forward_list>
#include <iostream>
#include <string>
#include <fstream>

const int INITIAL_CAPACITY = 23;
const double MAX_LOAD_FACTOR = 0.8;

class MapHash {
public:
    struct MapEntry {
        int key;
        int value;

        MapEntry(int key, int value) : key(key), value(value) {}
        MapEntry(int key) : key(key), value() {}
    };

    MapHash()
        : num_elems(0), capacity(INITIAL_CAPACITY),
        buckets(new List[INITIAL_CAPACITY]) {};
    MapHash(const MapHash& other)
        : num_elems(other.num_elems), hash(other.hash), capacity(other.capacity),
        buckets(new List[other.capacity]) {
        std::copy(other.buckets, other.buckets + other.capacity, buckets);
    };
    ~MapHash() { delete[] buckets; }

    void insert(const MapEntry& entry) {
        int h = hash(entry.key) % capacity;

        auto it = find_in_list(buckets[h], entry.key);

        if (it == buckets[h].end()) {
            resize_if_necessary();
            h = hash(entry.key) % capacity;
            buckets[h].push_front(entry);
            num_elems++;
        }
    }

    bool contains(const int& key) const {
        int h = hash(key) % capacity;
        const List& list = buckets[h];
        auto it = find_in_list(list, key);
        return it != list.end();
    }

    const int& at(const int& key) const {
        int h = hash(key) % capacity;
        const List& list = buckets[h];
        auto it = find_in_list(list, key);
        assert(it != list.end());
        return it->value;
    }

    int& at(const int& key) {
        int h = hash(key) % capacity;
        List& list = buckets[h];
        auto it = find_in_list(list, key);
        assert(it != list.end());
        return it->value;
    }

    int& operator[](const int& key) {
        int h = hash(key) % capacity;
        auto it = find_in_list(buckets[h], key);

        if (it == buckets[h].end()) {
            resize_if_necessary();
            h = hash(key) % capacity;
            buckets[h].push_front(MapEntry(key));
            it = buckets[h].begin();
            num_elems++;
        }

        return it->value;
    }

    void erase(const int& key) {
        int h = hash(key) % capacity;
        List& list = buckets[h];

        if (!list.empty()) {
            if (list.front().key == key) {
                list.pop_front();
                num_elems--;
            }
            else {
                auto it_prev = list.begin();
                auto it_next = ++list.begin();

                while (it_next != list.end() && it_next->key != key) {
                    it_prev++;
                    it_next++;
                }
                if (it_next != list.end()) {
                    list.erase_after(it_prev);
                    num_elems--;
                }
            }
        }
    }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; }

    MapHash& operator=(const MapHash& other) {
        if (this != &other) {
            capacity = other.capacity;
            num_elems = other.num_elems;
            hash = other.hash;
            delete[] buckets;
            buckets = new List[capacity];
            copy(other.buckets, other.buckets + capacity, buckets);
        }
        return *this;
    }

    void display(std::ostream& out) const {
        out << "{";
        bool first_entry = true;
        for (int i = 0; i < capacity; i++) {
            const List& current = buckets[i];
            for (const MapEntry& entry : current) {
                out << (first_entry ? " " : ", ");
                first_entry = false;
                out << entry.key << " -> " << entry.value;
            }
        }
        out << " }";
    }


private:
    using List = std::forward_list<MapEntry>;

    std::hash<int> hash;

    List* buckets;
    int num_elems;
    int capacity;

    void resize_if_necessary() {
        double load_factor = ((double)num_elems) / capacity;
        if (load_factor < MAX_LOAD_FACTOR)
            return;

        int new_capacity = next_prime_after(2 * capacity);

        List* new_array = new List[new_capacity];
        for (int i = 0; i < capacity; i++) {
            for (const MapEntry& entry : buckets[i]) {
                int new_pos = hash(entry.key) % new_capacity;
                new_array[new_pos].push_front(entry);
            }
        }

        capacity = new_capacity;
        delete[] buckets;
        buckets = new_array;
    }

    static int next_prime_after(int num) {
        while (!is_prime(num)) {
            num++;
        }
        return num;
    }

    static bool is_prime(int n) {
        int i = 2;
        bool is_prime = true;
        while (is_prime && i * i < n) {
            if (n % i == 0)
                is_prime = false;
            i++;
        }
        return is_prime;
    }

    static typename List::const_iterator find_in_list(const List& list,
        const int& key) {
        auto it = list.begin();
        while (it != list.end() && it->key != key) {
            ++it;
        }
        return it;
    }

    static typename List::iterator find_in_list(List& list, const int& key) {
        auto it = list.begin();
        while (it != list.end() && it->key != key) {
            ++it;
        }
        return it;
    }

public:

    // ----------------------------------------------------------------
    // Define aquí la clase de los iteradores
    // y los métodos begin() y end()
    //@ <answer>

    class iterator {
    public:
        using BucketIt = List::iterator;
        iterator(List* const& buckets, int capacity, int indBucket, BucketIt const& itInBucket) :
            buckets(buckets), capacity(capacity), indBucket(indBucket), itInBucket(itInBucket) {};

        iterator(List* const& buckets, int capacity) : buckets(buckets), capacity(capacity)
        {
            auto& itBuckets = this->buckets[0];
            auto [indNextBucket, nextIt] = this->findNext(0, itBuckets.begin());
            this->indBucket = indNextBucket;
            this->itInBucket = nextIt;
        };

        MapEntry& operator*() {
            return *itInBucket;
        }

        iterator& operator++() {
            auto [indNextBucket, nextIt] = this->findNext(this->indBucket, this->itInBucket);
            this->indBucket = indNextBucket;
            this->itInBucket = nextIt;
            return *this;
        }

        bool operator==(iterator const& o) const {
            return this->indBucket == o.indBucket && this->itInBucket == o.itInBucket;
        }

        bool operator!=(iterator const& o) const {
            return !(*this == o);
        }

    friend class MapHash;

    private:
        List* buckets; //LinkedList de punteros a LinkedLists
        int capacity;
        int indBucket;
        BucketIt itInBucket;

        //Encuentra el próximo bucket vacío a partir del bucketIdx dado y el iterador dentro del bucket
        std::pair<int, BucketIt> findNext(int bucketIdx, BucketIt it) {
            if (it != buckets[bucketIdx].end()) {
                ++it;
                if (it != buckets[bucketIdx].end()) return { bucketIdx, it };
            }
            for (int i = bucketIdx + 1; i < capacity; ++i) {
                if (!buckets[i].empty())
                    return { i, buckets[i].begin() };
            }
            return { capacity, {} };
        }
    };


    iterator begin() { return iterator(this->buckets, this->capacity); }
    iterator end() { return iterator(this->buckets, this->capacity, capacity, {}); }

    //@ </answer>

};


#include <string>
using namespace std;

bool resuelve() {
    int N; cin >> N;
    if (!cin) return false;

    // construimos el diccionario con la información en la entrada
    MapHash diccionario;
    for (int i = 0; i < N; ++i) {
        int clave, valor; cin >> clave >> valor;
        diccionario[clave] = valor;
    }

    // recorremos el diccionario sumando los valores asociados
    // a claves impares
    int total = 0;
    for (auto [clave, valor] : diccionario) {
        if (clave % 2 == 1)
            total += valor;
    }
    cout << total << '\n';
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelve());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}