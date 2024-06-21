#include <bits/stdc++.h>
using namespace std;


using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;


#define rep(i,a,b) for(int i =a; i < (b); i++)
#define sz(x)(int)x.size()
#define all(x) begin(x), end(x)
#define bitat(x, b) (((x) >> (b)) & 1)

const ll oo = 1e18;
int active = 0;

struct info {
    int first = -1, last = -1, tot = 0, save = 0;
    info(int t=-1) : first(t), last(t) {
        if(t != -1 && bitat(active, t)) {
            tot++;
        }
    }
};
info comb(info &l, info &r) {
    info res(-1);
    res.first = l.first == -1 ? r.first : l.first;
    res.last = r.last == -1 ? l.last : r.last;
    res.tot = l.tot + r.tot;
    res.save = l.save + r.save;
    if(min(l.last, r.first) != -1 && bitat(active, l.last) && bitat(active, r.first)) res.save++;
    return res;
}

info infopow(info &a, ll p){
    assert(p != 0);
    // cout << "infopow" << endl;
    if(p == 1){
        return a;
    }
    info half = infopow(a, p/2);
    half = comb(half, half);
    if(p & 1) half = comb(half, a);
    return half;
}

set<int> vars;
int banks, n, reg, init, m, idx;
vector<string> tok;
info solve() {
    // cout << "at " << idx << " " << m << endl;
    assert(idx < m);
    if(tok[idx][0] == 'V') {
        int t = stoi(tok[idx].substr(1))-1;
        // cout << "access memory " << t << " with bank " << t/reg << " at idx " << idx << endl;
        idx++;
        return info(t);
    }
    ll times = stoll(tok[idx].substr(1));
    // cout << "repeat " << times << " times at idx " << idx << ": " << endl;
    idx++;
    info res = solve();
    while(idx < m && tok[idx] != "E"){
        info o = solve();
        // cout << "combining " << idx << endl;
        res = comb(res, o);
    }
    idx++;
    // cout << "ended at " << idx << endl;
    res = infopow(res, times);
    return res;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    string str;
    while(getline(cin, str)) {
        stringstream is(str);
        is >> banks >> reg;
        // banks++;
        // init = banks-1;
        getline(cin, str);
        is = stringstream(str);
        tok.clear();
        tok.push_back("R1");
        while(is >> str){
            tok.push_back(str);
        }
        vars.clear();
        tok.push_back("E");
        for(auto &reg : tok){
            if(reg[0] != 'V') continue;
            vars.insert(stoi(reg.substr(1)));
        }
        
        n = sz(vars);
        // cout << "n: " << n << endl;
        m = sz(tok);

        vl save(1 << n), tot(1 << n);
        rep(i, 0, 1 << n){
            idx = 0;
            active = i;
            info res = solve();
            tot[i] = res.tot;
            save[i] = res.save;
            cout << i << " " << tot[i] << " " << save[i] << endl;
        }

        vector<vl> dp(banks+1, vl(1 << n, oo));
        dp[0][0] = 0;
        ll best = oo;
        rep(t, 1, banks+1){
            rep(mask, 0, sz(dp[t])){
                int sub = mask;
                while(sub){
                    if(__builtin_popcount(sub) <= reg)
                        dp[t][mask] = min(dp[t][mask], dp[t-1][mask ^ sub] + (t == 1 ? tot[sub] : 2 * tot[sub] - save[sub]));
                    sub = (sub - 1) & mask;
                }
                cout << "dp: " << t << " " << mask << " " << dp[t][mask] << endl;
            }
            best = min(best, dp[t].back());
        }
        // cout << "got here" << endl;
        ll ans = best;
        cout << ans << endl;
    }

    return 0;
}
