#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

using vi = vector<int>;
using ll = long long;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

random_device rdev;
mt19937 rng(rdev());

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vi idxs;
    rep(i, 0, min(20, n)) {
        idxs.push_back(uniform_int_distribution<int>(0, n-1)(rng));
    }

    map<vi, vi> buckets;
    rep(i, 0, n) {
        vi res;
        rep(j, 0, sz(idxs)) {
            if(i == idxs[j]){
                res.push_back(0);
                continue;
            }
            cout << i+1 << " " << idxs[j]+1 << endl;
            int v; cin >> v;
            if(v == 0) return 0;
            res.push_back(v);
        }
        buckets[res].push_back(i);
    }
    for(auto [key, v] : buckets) {
        rep(i, 0, sz(v)){
            rep(j, 0, i){
                cout << v[j]+1 << " " << v[i]+1 << endl;
                int t; cin >> t;
                if(t == 0) return 0;
            }
        }
    }

    return 0;
}
