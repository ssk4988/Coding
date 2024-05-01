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

// alice picks x items, bob buys x-k cheapest (in terms of b) from alice
// brute force that lowest b bob gets for free is c, buy k cheapest a with b >= c, then buy all others b <

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        vpi x(n);
        rep(i, 0, n){
            cin >> x[i].s;
        }
        rep(i, 0, n){
            cin >> x[i].f;
        }
        sort(all(x));
        reverse(all(x));
        ll best = 0;
        ll sum = 0;
        for(auto [b, a] : x){
            sum += max(0, b - a);
        }
        multiset<int> lowesta;
        if(sz(lowesta) == k) best = max(best, sum);
        for(auto [b, a] : x){
            sum -= max(0, b - a);
            lowesta.insert(a);
            sum -= a;
            while(sz(lowesta) > k){
                int exp = *lowesta.rbegin();
                sum += exp;
                lowesta.erase(lowesta.find(exp));
            }
            if(sz(lowesta) == k) best = max(best, sum);
        }
        cout << best << "\n";
    }
    
    return 0;
}
