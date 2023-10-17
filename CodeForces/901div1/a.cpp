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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m, k; cin >> n >> m >> k;
        multiset<ll> a, b;
        rep(i, 0, n){
            ll v; cin >> v; a.insert(v);
        }
        rep(i, 0, m) {
            ll v; cin >> v; b.insert(v);
        }
        vl scores;
        scores.pb(0);
        for(ll i : a){
            scores.back() += i;
        }
        rep(j, 0, min(5, k)){
            if(j % 2 == 0){
                ll amin = *a.begin(), bmax = *b.rbegin();
                if(amin < bmax){
                    a.erase(a.find(amin));
                    b.erase(b.find(bmax));
                    a.insert(bmax);
                    b.insert(amin);
                }
            }
            else{
                ll amax = *a.rbegin(), bmin = *b.begin();
                if(amax > bmin){
                    a.erase(a.find(amax));
                    b.erase(b.find(bmin));
                    a.insert(bmin);
                    b.insert(amax);
                }
            }
            scores.pb(0);
            for(ll i : a){
                scores.back() += i;
            }
        }
        if(sz(scores) ==  k + 1){
            cout << scores.back() << nL;
        }
        else{
            while((k - (scores.size() - 1)) % 2 != 0){
                scores.pop_back();
            }
            cout << scores.back() << nL;
        }
    }
    
    return 0;
}