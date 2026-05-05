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

struct UF {
    vi e;
    UF(int n) : e(n, -1) {}
    int find(int u) { return e[u] < 0 ? u : e[u] = find(e[u]); }
    bool join(int u, int v) {
        u = find(u), v = find(v);
        if(u==v) return false;
        if(e[u] > e[v]) swap(u, v);
        e[u] += e[v]; e[v] = u;
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        UF uf(n);
        vi a(n), b(n);
        rep(i, 0, n) {
            cin >> a[i];
            if(a[i] > 0) a[i]--;
        }
        rep(i, 0, n) {
            cin >> b[i];
            if(b[i] > 0) b[i]--;
        }
        bool works = true;
        rep(i, k, n) {
            if(a[i] == a[i-k]) uf.join(i, i-k);
            else {
                if(b[i] != -1 && b[i] != a[i]) works = false;
                if(b[i-k] != -1 && b[i-k] != a[i-k]) works = false;
                b[i] = a[i];
                b[i-k] = a[i-k];
            }
        }
        // cerr << "works: " << works << endl;
        vi made(n, -1);
        rep(i, 0, n) {
            if(b[i] == -1) continue;
            int j = uf.find(i);
            if(made[j] == -1) made[j] = b[i];
            else if(made[j] != b[i]) works = false;
        }
        rep(i, 0, n) {
            int j = uf.find(i);
            if(made[j] != -1) b[i] = made[j];
        }
        vi freqdiff(n);
        rep(i, 0, n) {
            vi check;
            if(i >= k) {
                freqdiff[a[i-k]]--;
                check.push_back(a[i-k]);
                if(b[i-k] != -1) freqdiff[b[i-k]]++;
            }
            freqdiff[a[i]]++;
            if(b[i] != -1) {
                freqdiff[b[i]]--;
                check.push_back(b[i]);
            }
            if(i == k-1) {
                rep(j, 0, k) if(freqdiff[a[j]] < 0) works = false;
            }
            if(i >= k-1) for(int x : check) if(freqdiff[x] < 0) works = false;
        }
        cout << (works ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
