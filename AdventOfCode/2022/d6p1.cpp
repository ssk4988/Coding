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
    string str; cin >> str;
    map<char, int> m;
    str = 'A' + str;
    rep(i, 0, 14){
        m[str[i]]++;
    }
    rep(i, 14, str.length()){
        m[str[i - 14]]--;
        m[str[i]]++;
        bool b = false;
        for(auto &p : m){
            if(p.s > 1){
                b = true;
                break;
            }
        }
        if(!b){
            cout << i << nL;
            break;
        }
    }
    
    return 0;
}