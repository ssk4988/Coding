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
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

struct RollbackUF {
	vi e; vector<pii> st;
	RollbackUF(int n) : e(n, -1) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;)
			e[st[i].first] = st[i].second;
		st.resize(t);
	}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		st.push_back({a, e[a]});
		st.push_back({b, e[b]});
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

RollbackUF uf(1);
using U = pii;
struct QueueUpdates {
    vector<tuple<bool, int, U>> st; // reversed, time before update, update
    void push(U u, bool r = false) {
        int t = uf.time();
        uf.join(u.first, u.second);
        st.emplace_back(r, t, u);
    }

    tuple<bool, int, U> rollback() {
        auto [r, t, u] = st.back();
        st.pop_back();
        uf.rollback(t);
        return {r, t, u};
    }
    
    void pop() {
        assert(sz(st));
        auto [r, t, u] = st.back();
        if (r) return void(rollback());
        array<vector<U>, 2> sq;
        do {
            tie(r, t, u) = rollback();
            sq[r].push_back(u);
        } while (sz(st) && sz(sq[0]) > sz(sq[1]));
        if (sz(st) == 0) {
            for(auto &u : sq[0]) push(u, true); // turn all stack updates into queue updates
            sq[0].clear();
        }
        rep(i, 0, 2)
            while(sz(sq[i])) 
                push(sq[i].back(), i), sq[i].pop_back();
        rollback();
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q, k; cin >> n >> q >> k;
    QueueUpdates qu;
    uf = RollbackUF(n);
    queue<int> rs;
    int d = 0;
    rep(i, 0, q) {
        int t; cin >> t;
        if(t == 1) {
            int x, y; cin >> x >> y; x--, y--;
            rs.push(d+k);
            qu.push({x, y});
        }
        else if(t == 2) {
            int x; cin >> x; x--;
            cout << uf.size(x) << "\n";
        } else {
            d++;
            while(sz(rs) && rs.front() <= d) {
                qu.pop();
                rs.pop();
            }
        }
    }
    
    return 0;
}
