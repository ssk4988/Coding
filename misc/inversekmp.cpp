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
    vi kmp(n);
    rep(i, 0, n) cin >> kmp[i];
    vvi aut(n, vi(26));
    string s(n, 'a');
    aut[0][s[0]-'a'] = 1;
    bool works = kmp[0] == 0;
    rep(i, 1, n){
        if(!works) break;
        int c = find(all(aut[kmp[i-1]]), kmp[i]) - aut[kmp[i-1]].begin();
        if(c == 26){
            works = false;
            break;
        }
        s[i] = c+'a';
        aut[i] = aut[kmp[i-1]];
        aut[i][s[i] - 'a'] = i+1;
    }
    if(works) cout << s << nL;
    else cout << "IMPOSSIBLE" << nL;
    return 0;
}
