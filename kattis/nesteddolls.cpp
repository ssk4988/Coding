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
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        map<int, vi> bucket;
        int n; cin >> n;
        rep(i, 0, n) {
            int x, y; cin >> x >> y; bucket[y].push_back(x);
        }
        multiset<int> xs;
        for(auto [key, val] : bucket) {
            for(int x : val) {
                auto it = xs.lower_bound(x);
                if(it != begin(xs)){
                    it--;
                    xs.erase(it);
                }
            }
            for(int x : val) xs.insert(x);
        }
        cout << sz(xs) << "\n";
    }
    
    return 0;
}
