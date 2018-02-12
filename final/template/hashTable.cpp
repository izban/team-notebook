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
