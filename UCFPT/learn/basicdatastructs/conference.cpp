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
    int n, t; cin >> n >> t;
    vector<string> names(n);
    vi len(n);
    rep(i, 0, n){
        cin >> names[i] >> len[i];
    }
    auto test = [&](int k) -> pair<bool, vpi> {
        priority_queue<pi, vpi, greater<pi>> rooms;
        rep(i, 0, k){
            rooms.push({0, i});
        }
        vpi ans(n);
        int last = 0;
        rep(i, 0, n){
            ans[i] = rooms.top(); rooms.pop();
            rooms.push({ans[i].f + len[i], ans[i].s});
            last = max(last, ans[i].f + len[i]);
        }
        return {last <= t, ans};
    };
    int k = 0;
    for(int dif = 1 << 20; dif; dif >>= 1){
        if(!test(k + dif).f) k += dif;
    }
    k++;
    auto [works, p] = test(k);
    vector<tuple<string, int, int>> ans;
    rep(i, 0, n){
        ans.emplace_back(names[i], p[i].f, p[i].s);
    }
    sort(all(ans));
    cout << k << "\n";
    for(auto [name, start, room] : ans){
        cout << name << " " << room << " " << start << "\n";
    }

    
    return 0;
}
