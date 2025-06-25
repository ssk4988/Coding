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
	UF(int n=0) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

UF uf;

vi tin;
vector<vector<pii>> ed;
int Time;
int dfs(int cur, int par) {
	int me = tin[cur] = ++Time, low = me;
	for (auto [nxt, e] : ed[cur]) if (e != par) {
		if (tin[nxt]) {
			low = min(low, tin[nxt]);
		} else {
			int up = dfs(nxt, e);
			low = min(low, up);
            if(up <= me) {
                uf.join(cur, nxt);
            }
		}
	}
	return low;
}

void bicomps() {
	tin.assign(sz(ed), 0);
	rep(i,0,sz(ed)) if (!tin[i]) dfs(i, -1);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vvi grid(2*n+1, vi(2*m+1));
    rep(i, 1, 2*n) {
        string s; cin >> s;
        rep(j, 1, 2*m) {
            grid[i][j] = s[j-1] != '.';
        }
    }
    int g = (n+1) * (m+1);
    ed.resize(g);
    uf = UF(g);
    int T = 0;
    for(int i = 0; i < sz(grid); i += 2) {
        for(int j = 0; j < sz(grid[i]); j += 2) {
            int u = i/2 * (m+1) + j/2;
            if(i+2 < sz(grid) && !grid[i+1][j]) {
                int v = (i+2)/2 * (m+1) + j/2;
                ed[u].emplace_back(v, T);
                ed[v].emplace_back(u, T++);
            }
            if(j+2 < sz(grid[i]) && !grid[i][j+1]) {
                int v = i/2 * (m+1) + (j+2)/2;
                ed[u].emplace_back(v, T);
                ed[v].emplace_back(u, T++);
            }
        }
    }
    bicomps();
    vvi belong(g);
    rep(i, 0, g) belong[uf.find(i)].push_back(i);
    vi vis(g);
    auto calc = [&](int u, int p, auto &&calc) -> int {
        int loop = 0;
        int ans = 0;
        vis[u] = 1;
        for(int u1 : belong[u]) {
            for(auto [v, e] : ed[u1]) {
                if(uf.find(v) == u) {
                    loop++;
                } else if (uf.find(v) == p) {}
                else {
                    assert(!vis[uf.find(v)]);
                    int c = calc(uf.find(v), u, calc);
                    c++;
                    ans ^= c;
                }
            }
        }
        assert(loop % 2 == 0);
        loop /= 2;
        loop &= 1;
        ans ^= loop;
        return ans;
    };
    int tot = calc(uf.find(0), -1, calc);
    for(int i = 0; i < sz(grid); i += 2) {
        for(int j = 0; j < sz(grid[i]); j += 2) {
            if(i == 0 || i+1 == sz(grid) || j == 0 || j+1 == sz(grid[i])) assert(vis[uf.find(i/2 * (m+1) + j/2)]);
        }
    }
    cout << (tot ? "Talia" : "Terra") << "\n";


    return 0;
}
