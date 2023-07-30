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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    set<pi> ans;
    rep(j, 10, 100){
        rep(i, 10, j){
            vi i1 = {i / 10, i % 10}, j1 = {j / 10, j % 10};
            rep(k, 0, 2){
                rep(l, 0, 2){
                    if(i1[k] == j1[l] && i1[k] != 0){
                        int resi = i1[1-k], resj = j1[1-l];
                        if(resi * j == resj * i){
                            ans.insert({i, j});
                        }
                    }
                }
            }
        }
    }
    ll n1 = 1, d1 = 1;
    for (auto [n, d] : ans){
        cout << n << " " << d << nL;
        n1 *= n;
        d1 *= d;
    }
    ll g = __gcd(n1, d1);
    n1 /= g;
    d1 /= g;
    cout << n1 << " " << d1 << nL;
    return 0;
}