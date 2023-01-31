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

int a[4000][4000];
int n;
int k1;
int curdp[4000], prevdp[4000];
int pref[4000][4000];

int C(int i, int j){
    int ans = pref[j][j];
    if(i){
        ans -= pref[i - 1][j] + pref[j][i - 1];
        ans += pref[i - 1][i - 1];
    }
    return ans / 2;
}

void compute(int l, int r, int optl, int optr){
    if(l > r) return;

    int mid = (l + r) / 2;
    pi best = {INT_MAX, -1};
    for(int k = optl; k <= min(mid, optr); k++){
        best = min(best, {(k > 0 ? prevdp[k - 1] : 0) + C(k, mid), k});
    }
    int opt = best.s;
    curdp[mid] = best.f;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> k1;
    rep(i, 0, n){
        rep(j, 0, n){
            cin >> a[i][j];
            pref[i][j] = a[i][j];
            if(i) pref[i][j] += pref[i - 1][j];
            if(j) pref[i][j] += pref[i][j - 1];
            if(i && j) pref[i][j] -= pref[i - 1][j - 1];
        }
    }
    rep(i, 0, n){
        prevdp[i] = C(0, i);
    }
    rep(i, 1, k1){
        compute(0, n - 1, 0, n - 1);
        rep(j, 0, n){
            prevdp[j] = curdp[j];
        }
    }
    cout << prevdp[n - 1] << nL;
    
    return 0;
}
