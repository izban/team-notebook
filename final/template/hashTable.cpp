template <const int max_size, class HashType, class Data, const Data default_value>
struct hashTable {
    HashType hash[max_size];
    Data f[max_size];
    int size;

    int position(HashType H ) const {
        int i = H % max_size;
        while (hash[i] && hash[i] != H)
            if (++i == max_size)
                i = 0;
        return i;
    }

    Data & operator [] (HashType H ) {
        assert(H != 0);
        int i = position(H);
        if (!hash[i]) {
            hash[i] = H;
            f[i] = default_value; 
            size++;
        }
        return f[i];
    }
};

hashTable<13, int, int, 0> h;

#include "ext/pb_ds/assoc_container.hpp"
using namespace __gnu_pbds;

template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V> using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

// HOW TO USE ::
// -- order_of_key(10) returns the number of elements in set/map strictly less than 10
// -- *find_by_order(10) returns 10-th smallest element in set/map (0-based)
