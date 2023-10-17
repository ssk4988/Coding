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

// 0 circle 1 square 2 triangle
ll maxb(int tin, int tout, ll a){
    // if(a == 1) return 
    if(tin == tout) return a - 1;
    if(tin == 0){
        if(tout == 1){
            ll b = a / 2;
            while(2 * b >= a) b--;
            return b;
        }
        else{
            ll b = ld(a) / 2 / sqrtl(3);
            return b;
        }
    }
    else if(tin == 1){
        if(tout == 0){
            ll b = a * sqrtl(2);
            return b;
        }
        else{
            ll b = ld(a) / (1 + ld(2) / sqrtl(3));
            return b;
        }
    }
    else{
        if(tout == 0){
            ll b= a * sqrtl(3);
            return b;
        }
        else{
            ll b = a * sqrtl(2) * (1 - tanl(15 * acosl(-1) / 180));
            return b;
        }
    }
}

ll calc(int t, ll a){
    if(a == 1) return 2 - t;
    if(t == 0) return ll(a * sqrtl(3));
    if(t == 1) return ll(a * sqrtl(2) * (1 - tanl(15 * acosl(-1) / 180)));
    // cout << i << " " << dp[1][i] << " " << i << " " << (dp[1][i] - i) << " " << ld(dp[1][i])/i << nL;
    return a - 1;
}

// find number of i <= lim such that grumber[t][i] = a through binary search
ll getocc(int t, ll a, ll lim = 1e10){
    ll lo = 1, hi = lim + 1;
    while(lo < hi){
        ll mid = lo + (hi - lo) / 2;
        if(a <= calc(t, mid)){
            hi = mid;
        }
        else{
            lo = mid + 1;
        }
    }
    ll lowerbound = lo;
    lo = 1, hi = lim + 1;
    while(lo < hi){
        ll mid = lo + (hi - lo) / 2;
        if(a < calc(t, mid)){
            hi = mid;
        }
        else{
            lo = mid + 1;
        }
    }
    ll higherbound = lo;
    return higherbound - lowerbound;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int LIM = 1e7;
    int BAD = -2;
    vvi dp(3, vi(LIM, BAD));
    dp[0][0] = dp[1][0] = dp[2][0] = -1;
    auto solve = [&](int t, int a, auto &&solve)->int{
        if(dp[t][a] != BAD) return dp[t][a];
        dp[t][a] = 0;
        rep(i, 0, 3){
            // cout << "fit " << i << " of size " << maxb(i, t, a) << "in " << t << " of size " << 
            dp[t][a] = max(dp[t][a], 1 + solve(i, maxb(i, t, a), solve));
            // cout << t << " " << a << " trans to " << maxb(i, t, a) << " for type " << i << nL;
        }
        return dp[t][a];
    };
    rep(i, 0, 5){
        rep(t, 0, 3){
            solve(t, i, solve);
            // cout << "dp[" << t << "][" << i << "]=" << solve(t, i, solve) << nL;
        }
        // cout << i << nL;
        if(i > 1){
            assert(dp[0][i] == int(i * sqrtl(3)));
            assert(dp[1][i] == int(i * sqrtl(2) * (1 - tanl(15 * acosl(-1) / 180))));
            // cout << i << " " << dp[1][i] << " " << i << " " << (dp[1][i] - i) << " " << ld(dp[1][i])/i << nL;
            assert(dp[2][i] == i - 1);
        }
    }
    int n; cin >> n;
    vl grumbers(n);
    ll sum = 0;
    vi ts(n);
    vl as(n);
    rep(i, 0, n){
        string str; cin >> str;
        int t;
        if(str == "circle") t = 0;
        else if(str == "square") t = 1;
        else t = 2;
        ts[i] = t;
        ll a; cin >> a;
        as[i] = a;
        grumbers[i] = maxb(2, t, a);
        sum ^= grumbers[i];
    }
    if(sum == 0){
        cout << 0 << nL;
        return 0;
    }
    ll ans = 0;
    rep(i, 0, n){
        rep(t, 0, 3){
            ans += getocc(t, grumbers[i] ^ sum, maxb(t, ts[i], as[i]));
        }
    }
    cout << ans << nL;
    
    return 0;
}
