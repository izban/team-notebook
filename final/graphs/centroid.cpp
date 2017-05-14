// original author: burunduk1, rewritten by me (enot110)
// !!! warning !!! this code is not tested well
const int N = 1e5, K = 17;

int pivot, level[N], parent[N];
vector<int> v[N];

int get_pivot( int x, int xx, int n ) {
    int size = 1;
    for (int y : v[x])
    {
        if (y != xx && level[y] == -1) size += get_pivot(y, x, n);
    }
    if (pivot == -1 && (size * 2 >= n || xx == -1)) pivot = x;
    return size;
}

void build( int x, int xx, int dep, int size ) {
    assert(dep < K);
    pivot = -1;
    get_pivot(x, -1, size);
    x = pivot;
    level[x] = dep, parent[x] = xx;
    for (int y : v[x]) if (level[y] == -1)
    {
        build(y, x, dep + 1, size / 2);
    }
}
