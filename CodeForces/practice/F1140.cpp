#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
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


vl ans;
struct RollbackUF {
	vi e, cs, hasc; vector<vl> st;
    ll sum = 0;
    
	RollbackUF(int n) : e(n, -1), cs(n, 0), hasc(n, -1) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;){
			if(st[i][0] == 0)
                e[st[i][1]] = st[i][2];
            else if(st[i][0] == 1)
                hasc[st[i][1]] = st[i][2];
            else if(st[i][0] == 2)
                cs[st[i][1]] = st[i][2];
            else sum = st[i][1];
        }
		st.resize(t);
	}
    ll score(int x){
        return ll(size(x)) * cs[find(x)];
    }
    void insert(int r, int c){
        st.pb({3, sum});
        if(hasc[c] == -1){
            r = find(r);
            st.pb({1, c, hasc[c]});
            st.pb({2, r, cs[r]});
            hasc[c] = r;
            sum -= score(r);
            cs[r]++;
            sum += score(r);
        }
        else{
            join(r, hasc[c]);
        }
    }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
        sum -= score(a) + score(b);
		st.push_back({0, a, e[a]});
		st.push_back({0, b, e[b]});
		e[a] += e[b]; e[b] = a;
        st.pb({2, a, cs[a]});
        cs[a] += cs[b];
        sum += score(a);
		return true;
	}
};

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
    vpi v;
	int lo, hi;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
	}
	void set(int L, int R, pi c) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) v.pb(c);
		else {
			l->set(L, R, c), r->set(L, R, c);
		}
	}
    void dfs(RollbackUF &uf){
        int t = uf.time();
        for(auto [x, y] : v){
            uf.insert(x, y);
        }
        if(lo + 1 == hi){
            // cout << uf.sum << nL;
            ans.pb(uf.sum);
        }
        else{
            l->dfs(uf), r->dfs(uf);
        }
        uf.rollback(t);
    }
};

const int LIM = 3e5 + 100;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; cin >> q;
    Node tree(0, q + 5);
    unordered_map<ll, int> pret;
    auto encode = [](pi p)->ll{
        ll v = p.f;
        v <<= 25;
        v |= p.s;
        return v;
    };
    auto decode = [](ll v)->pi{
        pi p;
        p.s = v & ((1 << 25) - 1);
        v >>= 25;
        p.f = v;
        return p;
    };
    rep(t, 1, q + 1){
        pi p; cin >> p.f >> p.s;
        ll v = encode(p);
        if(pret[v] == 0){
            pret[v] = t;
        }
        else{
            tree.set(pret[v], t, p);
            pret[v] = 0;
        }
    }
    for(auto &p : pret){
        pi v = decode(p.f);
        if(p.s != 0){
            tree.set(p.s, q + 1, v);
        }
    }
    RollbackUF uf(LIM);
    tree.dfs(uf);
    rep(t, 1, q + 1){
        cout << ans[t] << " ";
    }
    cout << nL;
    return 0;
}
