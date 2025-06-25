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
    vll a(n);
    rep(i, 0, n) cin >> a[i].f >> a[i].s;
    sort(all(a));
    vll b;
    for(auto p : a) {
        if(sz(b) == 0 || b.back().s < p.s) b.push_back(p);
    }
    vl knapsack(n+1);
    rep(i, 1, sz(knapsack)) {
        knapsack[i] = knapsack[i-1];
        for(auto [s, w] : b) {
            if(i >= s) knapsack[i] = max(knapsack[i], knapsack[i-s]+w);
        }
        cout << knapsack[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
