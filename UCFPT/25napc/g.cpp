#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
    int n = sz(a), L  = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);
    for(static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vi rev(n);
    rep(i,0,n) rev[i] = (rev[i/2]|(i&1)<<L) / 2;
    rep(i,0,n) if(i<rev[i]) swap(a[i], a[rev[i]]);
    for(int k = 1; k < n; k *= 2)
        for(int i = 0; i < n ; i += 2 * k) rep(j,0,k) {
            C z = rt[j+k] * a[i+j+k];
            a[i+j+k] = a[i+j] - z;
            a[i+j] += z;
        }
}
vd conv(const vd& a, const vd& b) {
    if(a.empty() || b.empty()) return {};
    vd res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vector<C> in(n), out(n);
    copy(all(a), begin(in));
    rep(i,0,sz(b)) in[i].imag(b[i]);
    fft(in);
    for(C& x : in) x *= x;
    rep(i,0,n) out[i] = in[-i&(n-1)]- conj(in[i]);
    fft(out);
    rep(i,0,sz(res)) res[i] = imag(out[i]) / (4*n);
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    const int K = 400;
    vector<vl> precomp(K);
    rep(i, 0, K) {
        precomp[i].resize(i);
    }
    vi p(n);
    rep(i, 0, n) {
        cin >> p[i]; p[i]--;
    }
    vi used(n);
    vector<vl> big;
    rep(i, 0, n) {
        if(used[i]) continue;
        vi cycle;
        int u = i;
        while(!used[u]) {
            cycle.push_back(u);
            used[u] = 1;
            u = p[u];
        }
        vd a(sz(cycle)), b(sz(cycle));
        rep(i, 0, sz(cycle)) {
            a[i] = cycle[i]+1, b[i] = cycle[i]+1;
        }
        rep(i, 0, sz(cycle)) a.push_back(a[i]);
        reverse(all(b));
        vd res = conv(a, b);
        res.erase(begin(res), begin(res)+sz(cycle)-1);
        res.resize(sz(cycle));
        if(sz(cycle) < K) {
            rep(i, 0, sz(cycle)) {
                precomp[sz(cycle)][i] += round(res[i]);
            }
        } else {
            vl resl(sz(cycle));
            rep(i, 0, sz(cycle)) resl[i] = round(res[i]);
            big.push_back(resl);
        }
    }
    rep(qid, 0, q) {
        int k; cin >> k;
        ll ans = 0;
        rep(i, 1, K) {
            ans += precomp[i][k % i];
        }
        for(auto &b : big) {
            ans += b[k % sz(b)];
        }
        cout << ans << "\n";
    }
    return 0;
}
