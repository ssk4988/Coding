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

// AABBCB

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    string s; cin >> s;
    vvi cnt(3);
    vpi bs;
    vpi m;
    for(int i = 2*n-1; i >= 0; i--) {
        if(s[i] == 'C') {
            cnt[2].pb(i);
        } else if (s[i] == 'B') {
            if(sz(cnt[2])){
                bs.pb({i, cnt[2].back()});
                cnt[2].pop_back();
            }
            else {
                cnt[1].pb(i);
            }
        } else if(s[i] == 'A') {
            if(sz(cnt[1])) {
                m.pb({i, cnt[1].back()});
                cnt[1].pop_back();
            }
            else if(sz(cnt[2])) {
                m.pb({i, cnt[2].back()});
                cnt[2].pop_back();
            }else if (sz(bs)){
                auto [b, c] = bs.back();
                bs.pop_back();
                m.pb({i, b});
                cnt[2].pb(c);
            }else {
                cnt[0].pb(i);
            }
        }
    }
    if(sz(cnt[0]) || sz(cnt[1]) || sz(cnt[2])) {
        cout << "NO\n";
        return 0;
    }
    for(auto x : bs){
        m.pb(x);
    }
    cout << "YES\n";
    for(auto [a, b] : m){
        cout << a+1 << " " << b+1 << "\n";
    }

    
    return 0;
}
