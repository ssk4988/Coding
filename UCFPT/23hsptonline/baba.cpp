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
    map<int, ll> m;
    int pref = 0;
    m[0] = 1;
    ll ans = 0;
    for(char c : str){
        if(c == 'A') pref++;
        else pref--;
        ans += m[pref];
        m[pref]++;
    }
    if(pref != 0){
        cout << "BABA IS NOT YOU!\n";
    }
    else cout << ans << "\n";
    
    return 0;
}