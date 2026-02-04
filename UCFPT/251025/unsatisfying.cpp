#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

struct TwoSat {
	int N;
	vector<vi> gr;
	vi values; // 0 = false, 1 = true

	TwoSat(int n = 0) : N(n), gr(2*n) {}

	int addVar() { // (optional)
		gr.emplace_back();
		gr.emplace_back();
		return N++;
	}

	void either(int f, int j) {
		f = max(2*f, -1-2*f);
		j = max(2*j, -1-2*j);
		gr[f].push_back(j^1);
		gr[j].push_back(f^1);
	}
	void setValue(int x) { either(x, x); }

	void atMostOne(const vi& li) { // (optional)
		if (sz(li) <= 1) return;
		int cur = ~li[0];
		rep(i,2,sz(li)) {
			int next = addVar();
			either(cur, ~li[i]);
			either(cur, next);
			either(~li[i], next);
			cur = ~next;
		}
		either(cur, ~li[1]);
	}

	vi val, comp, z; int time = 0;
	int dfs(int i) {
		int low = val[i] = ++time, x; z.push_back(i);
		for(int e : gr[i]) if (!comp[e])
			low = min(low, val[e] ?: dfs(e));
		if (low == val[i]) do {
			x = z.back(); z.pop_back();
			comp[x] = low;
			if (values[x>>1] == -1)
				values[x>>1] = x&1;
		} while (x != i);
		return val[i] = low;
	}

    bool solve2() {
        rep(i, 0, N) {
            vector<bool> seen(2*N);
            auto dfs = [&](int u, auto &&dfs) -> bool {
                if(seen[u]) return false;
                if(u == 2*i) return true;
                seen[u] = true;
                for(int v : gr[u]) if(dfs(v, dfs)) return true;
                return false;
            };
            if(dfs(2*i+1, dfs)) return true;
        }
        return false;
    }
    bool solve3() {
        rep(i, 0, N) {
            vector<bool> seen(2*N);
            auto dfs = [&](int u, auto &&dfs) -> bool {
                if(seen[u]) return false;
                if(u % 2 == 0) return true;
                seen[u] = true;
                for(int v : gr[u]) if(dfs(v, dfs)) return true;
                return false;
            };
            if(dfs(2*i+1, dfs)) return true;
        }
        return false;
    }

	bool solve() {
		values.assign(N, -1);
		val.assign(2*N, 0); comp = val;
		rep(i,0,2*N) if (!comp[i]) dfs(i);
		rep(i,0,N) if (comp[2*i] == comp[2*i+1]) return 0;
		return 1;
	}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    TwoSat ts(n);
    bool diff = false;
    rep(i, 0, m) {
        int type = 0;
        int u, v; cin >> u >> v;
        u--, v--;
        if(u < 0) u = ~(-(u+1)-1), type++;
        if(v < 0) v = ~(-(v+1)-1), type++;
        ts.either(u,v);
        diff = diff || type == 2;
    }
    if(!ts.solve()) {
        cout << "0\n";
    } else if(ts.solve2()) cout << "1\n";
    else if(diff) cout << "2\n";
    else cout << "-1\n";
    

    return 0;
}
