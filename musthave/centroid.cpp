/**                        
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5, K = 17;

int q, n, centroid, color[N], level[N], parent[N];
vector<int> c[N];

int get_centroid( int v, int p, int n ) {
    int size = 1;
    for (int x : c[v])
        if (x != p && level[x] == -1)
            size += get_centroid(x, v, n);
    if (centroid == -1 && (size * 2 >= n || p == -1))
        centroid = v;
    return size;
}

void build( int v, int p, int dep, int size ) {
    assert(dep < K);
    centroid = -1;
    get_centroid(v, -1, size);
    int C = centroid;
    level[C] = dep, parent[C] = p;
    for (int x : c[C])
        if (level[x] == -1)
            build(x, C, dep + 1, size / 2);
}

memset(level, -1, sizeof(level));
build(0, -1, 0, n);
