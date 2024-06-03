#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
const ll MOD = 998244353;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q;
    cin >> n >> q;
    vi l(q), r(q);
    vvi lefts(n), rights(n);
    rep(i, 0, q)
    {
        cin >> l[i]; l[i]--;
    }
    rep(i, 0, q)
    {
        cin >> r[i]; r[i]--;
    }
    vi nxt(n, n);
    vi nxtl(n, n), nxtr(n, n);
    for(int i = q-1; i >= 0; i--){
        nxtl[i] = nxt[l[i]];
        nxtr[i] = nxt[r[i]];
        nxt[l[i]] = i;
        nxt[r[i]] = i;
    }
    auto dfs = [&](int i, auto &&dfs)->deque<int> {
        deque<int> ls = nxtl[i] == n ? deque<int>{l[i]} : dfs(nxtl[i], dfs);
        deque<int> rs = nxtr[i] == n ? deque<int>{r[i]} : dfs(nxtr[i], dfs);
        if(sz(ls) < sz(rs)){
            while(sz(ls)){
                rs.push_front(ls.back());
                ls.pop_back();
            }
            return rs;
        }
        while(sz(rs)){
            while(sz(rs)){
                ls.pb(rs.front());
                rs.pop_front();
            }
        }
        return ls;
    };
    deque<int> order = dfs(0, dfs);
    // for(int i : order) cout << i+1 << " ";
    // cout << "\n";
    vi cnt(n);
    cnt[order.front()]++;
    cnt[order.back()]++;
    rep(i, 0, sz(order)-1){
        cnt[max(order[i], order[i+1])]++;
    }
    ll ans = 1;
    int seg = 0;
    for(int i = n-1; i >= 0; i--){
        seg += cnt[i];
        if(nxt[i] == n){
            (ans *= seg) %= MOD;
            seg++;
        }
    }
    cout << ans << "\n";
    return 0;
}
