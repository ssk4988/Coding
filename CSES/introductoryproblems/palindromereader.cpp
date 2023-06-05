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
    vi freq(26);
    string str; cin >> str;
    int n = sz(str);
    rep(i, 0, n){
        freq[str[i] - 'A']++;
    }
    int numodd = 0;
    rep(i, 0, 26) if(freq[i] % 2 == 1) numodd++;
    if(numodd > 1) cout << "NO SOLUTION" << nL;
    else{
        rep(i, 0, 26){
            rep(j, 0, freq[i] / 2) cout << char('A' + i);
        }
        rep(i, 0, 26) if(freq[i] % 2 == 1) cout << char('A' + i);
        for(int i = 25; i >= 0; i--){
            rep(j, 0, freq[i] / 2) cout << char('A' + i);
        }
        cout << nL;
    }
    
    return 0;
}
