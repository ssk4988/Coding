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
using vvl = vector<vl>;

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

const ll inf = 1e15;

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mid;
    vvl dp;
	Node(vl& v, int lo, int hi) : lo(lo), hi(hi), mid(lo + (hi - lo)/2), dp(2, vl(2)) {
		if (lo + 1 < hi) {
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			dp = comb(l->dp, r->dp);
		}
		else dp = vvl(2, vl(2, v[lo]));
	}
    vvl comb(vvl &a, vvl &b){
        vvl res(2, vl(2, inf));
        if(lo + 2 == hi){
            res[0][0] = a[0][0];
            res[1][1] = res[1][0] = b[0][0];
            res[0][1] = a[0][0] + b[0][0];
        }
        else if(lo + 3 == hi){
            res = {{a[0][0] + b[0][0], a[0][0] + b[1][1]}, {b[0][0], b[0][0] + b[1][1]}};
        }
        else{
            rep(i, 0, 2){
                rep(j, 0, 2){
                    rep(k, 0, 2){
                        rep(l, 0, k + 1){
                            res[i][j] = min(res[i][j], a[i][k] + b[l][j]);
                        }
                    }
                }
            }
        }
        if(lo + 4 == hi){
            res[1][0] = a[1][1] + b[0][0];
        }
        return res;
    }
	void upd(int idx, ll x) {
		if (lo + 1 == hi) {
			dp = vvl(2, vl(2, x));
		}
		else {
            if(mid <= idx){
                r->upd(idx, x);
            }
            else l->upd(idx, x);
			dp = comb(l->dp, r->dp);
		}
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl v(n-1);
    rep(i, 0, n-1) cin >> v[i];
    int q; cin >> q;
    Node tree(v, 0, n - 1);
    rep(i, 0, q){
        int idx; ll x; cin >> idx >> x;
        idx--;
        tree.upd(idx, x);
        ll ans = tree.dp[0][1];
        cout << (2 * ans) << nL;
    }
    return 0;
}