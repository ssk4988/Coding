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

ld score(vpi &v, ld time){
    ld mint = 2e6 * 1e5;
    ld maxt = -mint;
    for(auto &p : v){
        mint = min(mint, time * p.s + p.f);
        maxt = max(maxt, time * p.s + p.f);
    }
    return maxt - mint;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vpi v(n);
    rep(i, 0, n){
        int a, b;
        cin >> a >> b;
        v[i] = {a, b};
    }
    ld low = 0;
    ld high = 2e6;
    while(abs(high - low) > 1e-4){
        ld l1 = low + (high - low) / 3;
        ld l2 = high - (high - low) / 3;
        ld s1 = score(v, l1);
        ld s2 = score(v, l2);
        if(score(v, l1) < score(v, l2)){
            high = l2;
        }
        else{
            low = l1;
        }
    }
    cout << fixed << setprecision(4) << score(v, low) << nL;
    
    return 0;
}