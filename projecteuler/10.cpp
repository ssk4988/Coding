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
    ll ans = 0;
    ll sq = 1000000;
    vl composite(sq);
    composite[0] = composite[1] = true;
    vi primes;
    for(ll i = 1; i < sq; i++){
        if(!composite[i]) for(ll j = i * i; j < sq; j += i) composite[j] = true;
        if(!composite[i]) primes.pb(i);
    }
    ll sum = 0;
    for(int i : primes) if(i < 2000000) sum += i;
    cout << sum << nL;
    
    return 0;
}
