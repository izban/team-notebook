#include <bits/stdc++.h>
using namespace std;
#include "../musthave/generalMatching.cpp"
typedef long long ll;
int main() {
    int n;
    cin >> n;
    vector<pair<int, int> > edges;
    int u, v;
    while (cin >> u >> v) {
        u--; v--;
        edges.push_back(make_pair(u, v));
    }		
    auto ans = GeneralMatching::solve(n, edges);
    cout << ans.size() * 2 << endl;
    for (auto o : ans) cout << o.first + 1 << " " << o.second + 1 << endl;
    
    return 0;
}

