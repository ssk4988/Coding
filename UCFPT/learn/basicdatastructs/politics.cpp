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
    while(true){
        int n, m; cin >> n >> m;
        if(n == 0) break;
        map<string, int> cand;
        rep(i, 0, n){
            string str; cin >> str;
            cand[str] = i;
        }
        vpi votes(m);
        vector<string> names;
        rep(i, 0, m){
            string vote, name; cin >> name >> vote;
            names.pb(name);
            if(!cand.count(vote)) cand[vote] = sz(cand);
            votes[i] = {cand[vote], i};
        }
        sort(all(votes));
        rep(i, 0, m){
            cout << names[votes[i].s] << "\n";
        }
    }
    
    return 0;
}
