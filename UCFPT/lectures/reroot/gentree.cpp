#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vii ed;
    mt19937 rng(time(NULL));
    rep(i, 1, n){
        int j = rng() % i;
        ed.emplace_back(i, j);
    }
    vi perm(n);
    iota(all(perm), 0);
    shuffle(all(perm), rng);
    cout << n << "\n";
    for(auto &[u, v] : ed) {
        u = perm[u], v = perm[v];
        cout << u+1 << " " << v+1 << "\n";
    }
    
    return 0;
}
