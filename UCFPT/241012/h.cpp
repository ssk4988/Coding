#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define f first
#define s second


// OVERFLOW???
const int MOD = 10000000;

int ABSIZE;
vi frq;

struct DFA {
    vector<vector<pii>> t; // nextstate, count on transition
    vector<bool> accept;
    DFA(pair<vi, vi> rule) {
        int n = sz(rule.f) + sz(rule.s);
        t.assign(n, vii(ABSIZE, {-1, -1}));
        accept.resize(n);
        rep(i, 0, n) {
            if(i < sz(rule.f)){ 
                accept[i] = 1;
                rep(j, 0, ABSIZE) {
                    if(rule.f[i] == j) {
                        t[i][j] = {i+1, frq[j]};
                    } else if(j == rule.f[0]) {
                        t[i][j] = {1, frq[j]};
                    } else t[i][j] = {0, frq[j]};
                }
            } else {
                rep(j, 0, ABSIZE) {
                    if(rule.s[i - sz(rule.f)] == j) {
                        t[i][j] = {(i+1)%sz(t), frq[j]};
                    } else if(j == rule.s[0]) {
                        t[i][j] = {(sz(rule.f)+1)%sz(t), frq[j]};
                    } else t[i][j] = {sz(rule.f), frq[j]};
                }
            }
        }
        // rep(i, 0, n) {
        //     rep(j, 0, ABSIZE) {
        //         cerr << i << " " << j << " " << t[i][j].f << " " << t[i][j].s << endl;
        //     }
        // }
    }
    DFA (vector<vii> &t, vector<bool> &a) : t(t), accept(a) {}
};

DFA operator+(DFA &a, DFA &b) {
    int n = sz(a.t), m = sz(b.t);
    vector<vii> t(n * m, vii(ABSIZE, {-1, -1}));
    vector<bool> accept(sz(t));
    vvi radj(sz(t));
    rep(i, 0, n){
        rep(j, 0, m) {
            accept[i * m + j] = a.accept[i] && b.accept[j];
            rep(k, 0, ABSIZE) {
                auto [i1, c1] = a.t[i][k];
                auto [j1, c2] = b.t[j][k];
                if(i1 == -1 || j1 == -1) continue;
                t[i * m + j][k] = {i1 * m + j1, c1};
                // cerr << sz(t) << " " << i1*m+j1 << endl;
                radj[i1 * m + j1].push_back(i * m + j);
            }
        }
    }
    // find reachable from both
    // from accepts
    vector<bool> fromaccept(sz(t), 1);
    {
        queue<int> q;
        rep(i, 0, sz(t)) if(accept[i]) q.push(i);
        while(sz(q)) {
            int i = q.front(); q.pop();
            if(fromaccept[i]) continue;
            fromaccept[i] = true;
            for(int j : radj[i]) q.push(j);
        }
    }
    vector<bool> fromstart(sz(t));
    // from start
    {
        queue<int> q;
        q.push(0);
        while(sz(q)) {
            int i = q.front(); q.pop();
            if(fromstart[i]) continue;
            fromstart[i] = true;
            for(auto [nxt, cnt] : t[i]) if(nxt != -1) q.push(nxt);
        }
    }
    int seen = 0;
    vi idx(sz(t), -1);
    rep(i, 0, sz(t)) {
        if(fromstart[i] && fromaccept[i]) {
            idx[i] = seen++;
        }
    }
    vector<vii> t1;
    vector<bool> accept1;
    rep(i, 0, sz(t)) {
        if(idx[i] == -1) continue;
        t1.push_back(t[i]);
        rep(j, 0, ABSIZE) {
            if(t1.back()[j].first != -1) {
                t1.back()[j].first = idx[t1.back()[j].first];
            }
        }
        accept1.push_back(accept[i]);
    }
    return DFA(t1, accept1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int k; cin >> k;
    string alpha; cin >> alpha;
    int sigma = sz(alpha);
    // INIT ABSIZE
    string r; cin >> r;
    map<char, int> ids;
    vector<pair<vi, vi>> rules;
    string st;
    auto addrule = [&](string rule)-> void {
        int idx= rule.find('>');
        string s1 = rule.substr(0, idx), s2 = rule.substr(idx+1);
        vi v1, v2;
        for(char c : s1) {
            if(!ids.count(c)) ids[c] = sz(ids);
            v1.push_back(ids[c]);
        }
        for(char c : s2) {
            if(!ids.count(c)) ids[c] = sz(ids);
            v2.push_back(ids[c]);
        }
        rules.push_back({v1, v2});
    };
    for(char c : r) {
        if(c == '|') {
            addrule(st);
            st.clear();
            continue;
        }
        st.push_back(c);
    }
    if(sz(st)) {
        addrule(st);
        st.clear();
    }
    int n = sz(rules);
    // ABSIZE = sigma;
    ABSIZE = sz(ids) + 1;
    // frq.assign(ABSIZE, 1);
    frq.assign(sz(ids), 1);
    frq.push_back(0);
    for(char c : alpha) {
        if(!ids.count(c)) frq.back()++;
    }
    vector<DFA> dfas;
    rep(i, 0, n) {
        dfas.push_back(rules[i]);
    }
    while(sz(dfas) >= 2) {
        auto d1 = dfas.back();
        dfas.pop_back();
        auto d2 = dfas.back();
        dfas.pop_back();
        dfas.push_back(d1 + d2);
    }
    auto &d = dfas[0];
    vi dp(sz(d.t));
    dp[0] = 1;
    rep(i, 0, k) {
        vi dp2(sz(d.t));
        rep(j, 0, sz(dp)) {
            if(dp[j] == 0) continue;
            for(auto [nxt, cnt] : d.t[j]){
                if(nxt != -1) (dp2[nxt] += cnt * dp[j]) %= MOD;
            }
        }
        swap(dp, dp2);
    }
    int ans = 0;
    rep(i, 0, sz(d.t)){
        if(d.accept[i]) (ans += dp[i]) %= MOD;
    }
    cout << ans << "\n";
    

    return 0;
}