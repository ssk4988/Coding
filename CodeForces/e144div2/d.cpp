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

// const int inf = 1e9;
// struct Node {
// 	Node *l = 0, *r = 0;
// 	int lo, hi;
//     ll best = 0, pref = 0, suff = 0, sum = 0;
// 	Node(vl& v, int lo, int hi) : lo(lo), hi(hi) {
// 		if (lo + 1 < hi) {
// 			int mid = lo + (hi - lo)/2;
// 			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
// 			comb();
// 		}
// 		else{
//             best = pref = suff = sum = v[lo];
//         }
// 	}
//     void comb(){
//         if(l == NULL) return;
//         best = max(l->best, max(r->best, l->suff + r->pref));
//         pref = max(l->pref, l->sum + r->pref);
//         suff = max(r->suff, l->suff + r->sum);
//         sum = l->sum + r->sum;
//     }
// 	void set(int L, int R, ll x) {
// 		if (R <= lo || hi <= L) return;
// 		if (L <= lo && hi <= R) {
// 			best = pref = suff = sum = x;
// 		}
// 		else {
// 			l->set(L, R, x), r->set(L, R, x);
// 			comb();
// 		}
// 	}
// };

// Node *tree;
ll best = 0;
int n, k; ll x;
vl a, pref;

// curpref = pref[idx - 1] + used * x - (idx - used) * x
// store min pref that can exist in past 
vector<vl> dp;
ll BAD = LLONG_MAX;
ll BAD2 = LLONG_MAX - 1;

void calc(int idx, int added){
    if(dp[idx][added] != BAD) return;
    // if(idx == 0){
    //     if(added == 0) dp[idx][added] = 0;
    //     else dp[idx][added] = BAD2;
    //     return;
    // }
    dp[idx][added] = BAD2;
    if(added > idx) return;
    ll curpref = pref[idx - 1] + added * x - (idx - added) * x;
    // dp[idx][added] = curpref;
    calc(idx - 1, added);
    dp[idx][added] = min(dp[idx][added], dp[idx - 1][added]);
    if(added > 0){
        calc(idx - 1, added - 1);
        dp[idx][added] = min(dp[idx][added], dp[idx - 1][added - 1]);
    }
    // rep(i, 0, idx){
    //     calc(i, added - 1);
    //     calc(i, added);
    //     dp[idx][added] = min(dp[idx][added], dp[i][added - 1]);
    //     dp[idx][added] = min(dp[idx][added], dp[i][added]);
    // }
    if(dp[idx][added] != BAD && dp[idx][added] != BAD2){
        best = max(best, curpref - dp[idx][added]);
        dp[idx][added] = min(curpref, dp[idx][added]);
    }
}

void solve(int idx, int used, ll bestsofar, ll minpref){
    // if(used > k) return;
    best = max(best, bestsofar);
    if(used == k){
        // if(idx < n) return;
        // if(used == k && idx == n) 
        return;
    }
    ll curpref = (idx ? pref[idx - 1] : 0) + used * x - (idx - used) * x;
    // curpref = min(curpref, 0LL);
    // use
    solve(idx + 1, used + 1, max(bestsofar, a[idx] + x + curpref - minpref), min(minpref, a[idx] + x + curpref));
    if(n - (idx + 1) < k - used){
        return;
    }
    // don't use
    solve(idx + 1, used, max(bestsofar, a[idx] - x + curpref - minpref), min(minpref, a[idx] - x + curpref));
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        cin >> n >> k >> x;
        a = vl(n);
        rep(i, 0, n) cin >> a[i];
        pref = vl(a);
        rep(i, 1, n) pref[i] += pref[i - 1];
        // rep(i, 0, n) a[i] -= x;
        // Node tree(a, 0, n);
        // tree = new Node(a, 0, n);
        // k = 0? x = 0?
        best = 0;
        dp = vector<vl>(n + 1, vl(k + 1, BAD));
        dp[0][0] = 0;
        rep(i, 1, k + 1){
            dp[0][i] = BAD2;
        }
        calc(n, k);
        // solve(0, 0, 0, 0);
        cout << best << nL;
    }
    
    return 0;
}
