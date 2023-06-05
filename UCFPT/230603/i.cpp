#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vpi = vector<pi>;

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V){
        for(int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k){
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k]))
                jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b){
        assert(a < b);
        int dep = 31 - __builtin_clz(b - a);
        return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int v; cin >> v;
    vi a(v);
    rep(i, 0, v) cin >> a[i];
    RMQ rmq(a);
    int q; cin >> q;
    rep(cn, 0, q){
        int n; cin >> n;
        vi ind(n);
        ll ans = 0;
        // case n = 1
        rep(i, 0, n){
            cin >> ind[i];
            ind[i]--;
            ans += a[ind[i]];
        }
        vpi ints;
        rep(i, 0, n - 1){
            int mx = rmq.query(ind[i], ind[i + 1] + 1);
            // for(int j = ind[i]; j <= ind[i + 1]; j++){
            //     mx = max(mx, a[j]);
            // }
            ints.pb({mx, i});
        }
        sort(all(ints));
        reverse(all(ints));
        set<int> rights, lefts;
        rights.insert(0);
        lefts.insert(n - 1);
        for(auto [mx, idx] : ints){
            int numonleft = -1;
            auto it = rights.upper_bound(idx);
            it = prev(it);
            numonleft = *it;
            int numonright = -1;
            it = lefts.lower_bound(idx + 1);
            numonright = *it;
            numonleft = 1 + idx - numonleft;
            numonright = 1 + numonright - (idx + 1);
            ans += ll(mx) * ll(numonleft) * ll(numonright);
            lefts.insert(idx);
            rights.insert(idx + 1);
        }
        cout << ans << "\n";
    }
    return 0;
}
