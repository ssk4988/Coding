#include <bits/stdc++.h>
using namespace std;

#define int long long

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
	vi e, l, r;
    vector<array<int, 2>> hs;
    vector<vector<vector<set<int>>>> tp;
    int sm = 0;
	UF(int n) : e(n, -1), l(n), r(n), hs(n, {-1, -1}), tp(2, vector(2, vector<set<int>>(2))) {
        iota(all(l), 0); iota(all(r), 1);
    }
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
        for(int u : {a, b}){
            sm -= (r[u] - l[u] + 1) / 2;
            rep(i, 0, 2){
                if(hs[u][i] != -1) tp[(r[u]-l[u])&1][l[u]&1][i].erase(u);
            }
        }
		e[a] += e[b]; e[b] = a;
        l[a] = min(l[a], l[b]), r[a] = max(r[a], r[b]);
        sm += (r[a] - l[a] + 1) / 2;
        rep(i,0,2){
            if(hs[b][i] != -1 && hs[a][i] == -1) hs[a][i] = hs[b][i];
            if(hs[a][i] != -1) tp[(r[a]-l[a])&1][l[a]&1][i].insert(a);
        }
		return true;
	}
};

signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        int mx = 0;
        vi a(n);
        vii swp;
        rep(i, 0, n){
            cin >> a[i];
            mx = max(mx, a[i]);
            swp.pb({a[i], i});
        }
        sort(all(swp));
        reverse(all(swp));
        int ans = 0;
        int l = 0;
        vi use(n);
        UF uf(n);
        while(l < n && swp[l].f == mx) {
            auto [v, i] = swp[l];
            use[i] = true;
            uf.hs[i][i&1] = i;
            uf.tp[1][i&1][i&1].insert(i);
            uf.sm++;
            if(i && use[i-1]) uf.join(i-1, i);
            if(i+1 < n && use[i+1]) uf.join(i, i+1);
            l++;
        }
        ans = max(ans, 2 * mx + uf.sm);
        while(l < n) {
            int r = l;
            while(r < n && swp[r].f == swp[l].f) {
                auto [val, i] = swp[r];
                use[i] = true;
                uf.sm++;
                if(i && use[i-1]) uf.join(i-1, i);
                if(i+1 < n && use[i+1]) uf.join(i, i+1);
                rep(pi, 0, 2) {
                    rep(li, 0, 2){
                        rep(hi, 0, 2){
                            // if(sz(uf.tp[li][hi]) == 0) continue;
                            if(sz(uf.tp[pi][li][hi]) == 0) continue;
                            int u = *begin(uf.tp[pi][li][hi]);
                            int cnt = uf.sm - (uf.r[u] - uf.l[u] + 1) / 2;
                            int v = uf.hs[u][hi];
                            assert(v != -1);
                            if(v > uf.l[u]) cnt += (v-1 - uf.l[u] + 1) / 2;
                            if(v+2 <= uf.r[u]) cnt += (uf.r[u] - (v+2) + 1) / 2;
                            cnt++;
                            int cand = cnt + val + mx;
                            ans = max(ans, cand);
                        }
                    }
                }
                r++;
            }
            l = r;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
