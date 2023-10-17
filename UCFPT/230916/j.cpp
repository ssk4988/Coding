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

int n;
const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    vi sw;
	Node(int lo, int hi) : lo(lo), hi(hi), sw(n) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
        rep(i, 0, n){
            sw[i] = i;
        }
	}
    vi comb(vi &a, vi &b){
        vi res(n);
        rep(i, 0, n){
            res[i] = a[b[i]];
        }
        return res;
    }
	void swa(int L, int R, int a, int b) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			swap(sw[a], sw[b]);
		}
		else {
			l->swa(L, R, a, b), r->swa(L, R, a, b);
			sw = comb(l->sw, r->sw);
		}
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int w, h, q; cin >> w >> h >> q;
    n = w;
    Node tree(0, h + 10);
    rep(i, 0, q){
        int y, x1, x2; cin >> y >> x1 >> x2; x1--, x2--;
        tree.swa(y, y + 1, x1, x2);
        vi res(tree.sw);
        int ans = 0;
        rep(i, 0, n){
            while(res[i] != i){
                swap(res[res[i]], res[i]);
                ans++;
            }
        }
        cout << ans << nL;
    }
    
    return 0;
}
