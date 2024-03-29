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

struct Node
{
	Node *nex[2] = {};
	int bitnum;
    int mx[4] = {};
	Node(int b) : bitnum(b) {}
	void add(int i, int ai, int ans) {
        int bi = (i >> bitnum) & 1, ba = (ai >> bitnum) & 1;
        mx[(bi << 1) + ba] = max(mx[(bi << 1) + ba], ans);
		if (bitnum == 0) return;
        int idx = bi != ba;
		// int idx = 1 & (val >> (bitnum - 1));
		if (nex[idx] == NULL) nex[idx] = new Node(bitnum - 1);
		nex[idx]->add(i, ai, ans);
	}
    void query(int i, int ai, int& ans){
        int bi = (i >> bitnum) & 1, ba = (ai >> bitnum) & 1;
        int seek_ai = bi;
        int seek_i = ba ^ 1;
        ans = max(ans, 1 + mx[(seek_i << 1) + seek_ai]);
        if (bitnum == 0) return;
        int idx = bi != ba;
		if (nex[idx] == NULL) return;
		nex[idx]->query(i, ai, ans);
    }
	int closest(int val) {
		int res = 0;
		if (bitnum == 0) return res;
		int idx = 1 & (val >> (bitnum - 1));
		if (nex[idx] != NULL) {
			res |= idx << (bitnum - 1);
			res |= nex[idx]->closest(val);
		} else if (nex[1 - idx] != NULL) {
			res |= (1 - idx) << (bitnum - 1);
			res |= nex[1 - idx]->closest(val);
		}
		return res;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n);
        auto conv = [](int seek, int bit_idx, int i, int ai) -> ll {
            return (ll(seek) << 20) + (bit_idx << 2) + (i << 1) + ai;
        };
        // map<tuple<int, int, int, int>, int> best; // seek, bit_idx, i, a[i]
        // unordered_map<ll, int> best;
        Node trie(29);
        int trueans = 0;
        rep(i, 0, n){
            cin >> a[i];
            int ans = 1;
            trie.query(i, a[i], ans);
            trueans = max(ans, trueans);
            trie.add(i, a[i], ans);
            // int seek = 0;
            // for(int b = 29; b >= 0; b--){
            //     int bi = (i >> b) & 1, ba = (a[i] >> b) & 1;
            //     int seek_ai = bi;
            //     int seek_i = ba ^ 1;
            //     ans = max(ans, 1 + best[conv(seek, b, seek_i, seek_ai)]);
            //     if(bi != ba) seek ^= 1 << b;
            // }
            // seek = 0;
            // for(int b = 29; b >= 0; b--){
            //     int bi = (i >> b) & 1, ba = (a[i] >> b) & 1;
            //     best[conv(seek, b, bi, ba)] = max(best[conv(seek, b, bi, ba)], ans);
            //     if(bi != ba) seek ^= 1 << b;
            // }
        }
        // int ans = 0;
        // for(auto [key, val] : best) ans = max(ans, val);
        cout << trueans << "\n";
    }
    
    return 0;
}
