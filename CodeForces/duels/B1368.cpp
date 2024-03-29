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
    ll k; cin >> k;
    vl freq(10, 1);
    ll prod = 1;
    while(prod < k){
        int mindex = 0;
        rep(i, 0, sz(freq)){
            if(freq[i] < freq[mindex]) mindex = i;
        }
        prod /= freq[mindex];
        freq[mindex]++;
        prod *= freq[mindex];
    }
    string str = "codeforces";
    rep(i, 0, sz(freq)){
        rep(j, 0, freq[i]){
            cout << str[i];
        }
    }
    cout << "\n";
    
    return 0;
}
