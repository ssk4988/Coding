#include <bits/stdc++.h>
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

const int lim = 1'000'000;
int dp[lim];

int collatz(ll v){
    if(v < lim){
        if(dp[v] != 0) return dp[v];
    }
    ll nex = v % 2 == 0 ? v/2 : 3 * v + 1;
    ll ret = 1 + collatz(nex);
    if(v < lim){
        dp[v] = ret;
    }
    return ret;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    dp[1] = 1;
    pi best = {0, 0};
    rep(i, 1, 1'000'001){
        if(mp(collatz(i), i) > best){
            best = {collatz(i), i};
        }
    }
    cout << best.s << " " << best.f << nL;
}
