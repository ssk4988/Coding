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
    vi composite(100);
    composite[0] = composite[1] = true;
    for(int i = 0; i < sz(composite); i++){
        if(!composite[i]){
            for(int j = 2 * i; j < sz(composite); j += i){
                composite[j] = true;
            }
        }
    }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        string str; cin >> str;
        if(sz(str) == 1){
            cout << (!composite[stoi(str)] ? stoi(str) : -1) << nL;
            continue;
        }
        bool works = false;
        rep(i, 0, sz(str)){
            if(works) break;
            rep(j, i + 1, sz(str)){
                int v = (str[i] - '0') * 10 + (str[j] - '0');
                if(!composite[v]){
                    works = true;
                    cout << v << nL;
                    break;
                }
            }
        }
        if(!works) cout << -1 << nL;
    }
    
    
    return 0;
}