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


// the ring can turn into any line of less degree
// therefore once you compute the answer for all lines, you can calc ring graphs in order of size
// line can split into several

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, l, r; cin >> n >> l >> r;
    vvi adj(n);
    rep(i, 0, n){
        int a, b; cin >> a >> b; a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vi cycles;
    vi visited(n);
    auto dfs = [&](int cur, int siz, auto &&dfs)->void{
        visited[cur] = true;
        bool another = false;
        for(int i : adj[cur]){
            if(!visited[i]){
                dfs(i, siz + 1, dfs);
                another = true;
            }
        }
        if(!another){
            cycles.pb(siz);
        }
    };
    rep(i, 0, n){
        if(!visited[i]) dfs(i, 1, dfs);
    }
    int nimsum = 0;
    for(int i : cycles){
        if(i <= l + r - 1) nimsum ^= (i / l);
    }
    cout << (nimsum == 0 ? "Bob" : "Alice") << nL;
    
    return 0;
}
