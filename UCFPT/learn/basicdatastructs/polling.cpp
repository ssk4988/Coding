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
    int n; cin >> n;
    map<string, int> freq;
    rep(i, 0, n){
        string str; cin >> str;
        freq[str]++;
    }
    vector<string> best = {""};
    for(auto [key, val] : freq){
        if(val > freq[best[0]]) best = {key};
        else if(val == freq[best[0]])best.pb(key);
    }
    sort(all(best));
    for(auto s : best){
        cout << s << "\n";
    }
    
    return 0;
}
