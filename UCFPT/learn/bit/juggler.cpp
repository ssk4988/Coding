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

struct FT{
    vector<ll> s;
    FT(int n) : s(n){}
    void update(int pos, ll dif){
        for(; pos < sz(s); pos |= pos + 1) s[pos] += dif;
    }
    ll query(int pos){
        ll res = 0;
        for(; pos > 0; pos &= pos - 1) res += s[pos - 1];
        return res;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    while(true){
        int n; cin >> n;
        if(n == 0) break;
        vi perm(n), rev(n);
        set<int> pos;
        FT ft(n);
        rep(i, 0, n){
            ft.update(i, 1);
            pos.insert(i);
            cin >> perm[i]; perm[i]--;
            rev[perm[i]] = i;
        }
        ll ans = 0;
        int cur = 0;
        rep(i, 0, n){
            // - - a - - b - - 
            int a = min(cur, rev[i]), b = max(cur, rev[i]);
            ll moves = min(ft.query(b) - ft.query(a), ft.query(n) - ft.query(b) + ft.query(a)) + 1;
            ans += moves;
            cur = rev[i];
            ft.update(rev[i], -1);
            pos.erase(rev[i]);
            if(pos.upper_bound(rev[i]) == pos.end()){
                cur = *pos.begin();
            }
            else cur = *pos.upper_bound(rev[i]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
