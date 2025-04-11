#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

vi Z(const vi& S) {
	vi z(sz(S));
	int l = -1, r = -1;
	rep(i,1,sz(S)) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}

struct UF {
    vi e;
    UF(int n) : e(n, -1) {}
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) { 
        a = find(a), b = find(b);
        if(a == b) return false;
        if(e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi z(n);
    int r = 0;
    UF uf(n);
    rep(i, 0, n) {
        cin >> z[i];
        if(i) {
            while(r < i + z[i]) {
                if(r >= i) uf.join(r, r-i);
                r++;
            }
        }
    }
    vector<set<int>> neq(n);
    rep(i, 1, n) {
        int after1 = i + z[i], after2 = z[i];
        if(max(after1, after2) >= n) continue;
        after1 = uf.find(after1), after2 = uf.find(after2);
        assert(after1 != after2);
        neq[after1].insert(after2);
        neq[after2].insert(after1);
    }
    vi fake(n-1);
    int unused = 1;
    map<int, int> rl, unrl;
    rep(i, 1, n) {
        int p = uf.find(i);
        if(!rl.count(p)) {
            rl[p] = unused++;
            unrl[rl[p]] = p;
        }
        fake[i-1] = rl[p];
    }
    vi ans = Z(fake);
    ans[0] = n-1;
    rep(i, 1, sz(ans)) {
        if(i + ans[i] == sz(ans)) {
            continue;
        }
        int after1 = ans[i], after2 = i + ans[i];
        after1 = unrl[fake[after1]], after2 = unrl[fake[after2]];
        after1 = uf.find(after1), after2 = uf.find(after2);
        if(neq[after1].count(after2)) {
            assert(neq[after2].count(after1));
        } else {
            ans[i] = -1;
        }
    }
    for(int v : ans) cout << v << " ";
    cout << "\n";



    return 0;
}
