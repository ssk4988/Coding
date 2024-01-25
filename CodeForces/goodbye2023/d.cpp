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
    // map<string, vi> mm;
    // rep(i, 1, sqrt(1000000000)){
    //     int i2 = i * i;
    //     string s = to_string(i2);
    //     sort(all(s));
    //     mm[s].pb(i);
    // }
    // for(auto [s, v] : mm){
    //     if(sz(s) <= sz(v) && sz(s) % 2 == 1 && sz(s) >= 3 && s.substr(sz(s) - 3) == "169"){
    //         cout << s << " " << sz(v) << nL;
    //         for(int i : v){
    //             cout << i << " " << (i * i) << nL;
    //         }
    //     }
    // }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        if(n == 1){
            cout << 1 << nL;
            continue;
        }
        if(n == 3){
            cout << 169 << nL;
            cout << 196 << nL;
            cout << 961 << nL;
            continue;
        }
        // cout << "answering for " << n << nL;
        int n2 = n / 2;
        rep(i, 0, n2){
            string s;
            s.pb('1');
            rep(j, 0, i){
                s.pb('0');
            }
            s.pb('6');
            rep(j, 0, i){
                s.pb('0');
            }
            s.pb('9');
            while(sz(s) < n) s.pb('0');
            cout << s << nL;
        }
        {
            string s = "196";
            while(sz(s) < n) s.pb('0');
            cout << s << nL;
        }
        rep(i, 0, n2){
            string s;
            s.pb('9');
            rep(j, 0, i){
                s.pb('0');
            }
            s.pb('6');
            rep(j, 0, i){
                s.pb('0');
            }
            s.pb('1');
            while(sz(s) < n) s.pb('0');
            cout << s << nL;
        }
    }
    
    return 0;
}
