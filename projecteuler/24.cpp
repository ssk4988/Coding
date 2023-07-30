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
    set<int> digs = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ll k = 1'000'000;
    vl fact = {1};
    rep(i, 1, 11) fact.pb(fact.back() * i);
    rep(i, 0, 10){
        int cnt = 0, r = -1;
        for(int rem : digs){
            if((cnt + 1) * fact[10 - i - 1] >= k){
                r = rem;
                break;
            }
            cnt++;
        }
        k -= cnt * fact[10 - i - 1];
        digs.erase(r);
        cout << r;
    }
    
    return 0;
}