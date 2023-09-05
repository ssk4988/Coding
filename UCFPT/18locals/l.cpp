#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vl = vector<ll>;
using pl = pair<ll, ll>;

#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

struct FT {
    vl s;
    FT(int n) : s(n){}
    void update(int pos, ll dif){
        for(; pos < sz(s); pos |= pos + 1) s[pos] += dif;
    }
    ll query(int pos){
        ll res = 0;
        for(; pos > 0; pos &= pos - 1) res += s[pos - 1];
        return res;
    }
    // ll query(int l, int r){
    //     ll r1 = query(r);
    //     if()
    // }
};
const int DEBUG = false;
int main(){
    if(!DEBUG) cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; int s; cin >> q >> s;
    vector<vi> qs(q);
    int n = 1;
    vector<vi> child(1);
    using a3 = array<int, 3>;
    vector<vector<a3>> events(1);
    vector<vector<pi>> bonuses(1);
    // vector<
    events[0].pb({2, 0, s});
    rep(i, 1, q + 1){
        int t; cin >> t;
        if(t == 1){
            int idx; cin >> idx;
            idx--;
            child[idx].pb(sz(child));
            child.pb({});
            events.pb({});
            bonuses.pb({});
            events.back().pb({2, 0, 0});
            events.back().pb({2, i, s});
            n++;
            // 
            // qs[i] = {t, }
        }
        else if(t == 2){
            int idx, m; cin >> idx >> m;
            idx--;
            events[idx].pb({2, i, m});
        }
        else if(t == 3){
            int idx, b; cin >> idx >> b;
            idx--;
            bonuses[idx].pb({i, b});
        }
        else{
            int idx; cin >> idx; idx--;
            events[idx].pb({4, i, -1});
            // cout << "added query " << i << " " << idx << "\n";
        }
        // if(DEBUG){
        //     cout << "processed query " << i << "\n";
        // }
    }
    rep(i, 0, n){
        events[i].pb({2, q + 5, 0});
    }
    FT ft(q + 10);
    vector<pl> answers;
    auto dfs = [&](int cur, auto &&dfs)->void{
        for(auto [i, b] : bonuses[cur]){
            ft.update(i, b);
        }
        ll prevmult = 0;
        int multtime = 0;
        ll ans = 0;
        for(auto [t, i, v] : events[cur]){
            if(t == 2){
                ll cont = ft.query(i) - ft.query(multtime);
                ans += cont * prevmult;
                prevmult = v;
                multtime = i;
            }
            else if(t == 4){
                ll cont = ft.query(i) - ft.query(multtime);
                answers.pb({i, ans + cont * prevmult});
            }
        }
        for(auto c : child[cur]){
            dfs(c, dfs);
        }
        for(auto [i, b] : bonuses[cur]){
            ft.update(i, -b);
        }
    };
    dfs(0, dfs);
    sort(all(answers));
    for(auto [i, v] : answers){
        cout << v << "\n";
    }
}
