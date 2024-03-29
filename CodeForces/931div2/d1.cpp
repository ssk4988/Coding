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
#define bitat(x, b) 

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll n, m; cin >> n >> m;
        vl ans = {n};
        bool works = true;
        int firstseen = 0;
        int seen11 = 0, seen10 = 0, seen01 = 0;
        bool case2 = false;
        for(ll b = 1LL << 60; b; b >>= 1){
            ll nb = n & b, mb = m & b;
            if(nb && mb){seen11++;}
            if(nb && !mb){
                seen10++;
            }
            if(!nb && mb){
                seen01++;
            }
            if(!firstseen){
                if(nb && mb){
                    firstseen = 0b11;
                }
                if(nb && !mb){
                    firstseen = 0b10;
                }
            }
            if(seen01 == 1 && seen10 == 1 && !seen11){
                works = false;
                break;
            }
            else if(seen10 > 1 && seen01 == 1 && !seen11){
                case2 = true;
                break;
            }
        }
        // this is wrong somehow
        if(!works){
            cout << -1 << "\n";
            continue;
        }
        if(case2){
            for(ll b = 1LL << 60; b; b >>= 1){
                ll nb = n & b, mb = m & b;
                if(nb != mb){
                    ll y = n ^ m ^ b;
                    ans.pb(n ^ y);
                    break;
                }
            }
        }
        ans.pb(m);
        rep(i, 0, sz(ans) - 1){
            ll x = ans[i];
            ll y = ans[i+1];
            assert(y < x && (x ^ y) < x);
        }
        cout << sz(ans)-1 << nL;
        for(auto a : ans){
            cout << a << " ";
        }
        cout << "\n";
        // assert((n ^ m) < n && m < n);
        // set x = n and y = m
        // assert showed that  x ^ y < x and y < x so it is valid here
        // our action is set x=y
        // cout << 1 << "\n" << n << " " << m << "\n";
        // if(firstseen == 0b10){

        // }
        // seen11 = false, seen10 = false, seen01 = false;
        // for(ll b = 1LL << 60; b; b >>= 1){
        //     ll nb = x & b, mb = m & b;
        //     if(nb && mb){seen11 = true;}
        //     if(nb && !mb){
        //         seen10 = true;
        //     }
        //     if(!nb && mb){
        //         seen01 = true;
        //     }
        //     if(seen01 && seen10 && !seen11){
        //         works = false;
        //         break;
        //     }
        // }
    }
    
    return 0;
}
