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
        int n = sz(rule.f) + sz(rule.s) + 1;
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
            } else if(i == sz(rule.f)) {
                rep(j, 0, ABSIZE) {
                    if(rule.s[0] == j) {
                        t[i][j] = {i+1, frq[j]};
                    } else t[i][j] = {i, frq[j]};
                }
            } else {
                rep(j, 0, ABSIZE) {
                    if(rule.s[i - sz(rule.f)-1] == j) {
                        t[i][j] = {i+1, frq[j]};
                    } else if(j == rule.s[0]) {
                        t[i][j] = {sz(rule.f)+1, frq[j]};
                    } else t[i][j] = {sz(rule.f), frq[j]};
                }
            }
        }
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
                t[i * m + j][k] = {i1 * m + j1, (c1 * c2)%MOD};
                radj[i1 * m + j1].push_back(i * m + j);
            }
        }
    }
    // find reachable from both
    // from accepts
    {
        
    }
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
    ABSIZE = sz(ids) + 1;
    frq.assign(sz(ids), 1);
    frq.push_back(0);
    for(char c : alpha) {
        if(!ids.count(c)) frq.back()++;
    }
    // rep(i, 0, n) {
    //     addWord(rules[i].first, i*2);
    //     addWord(rules[i].second, i*2+1);
    // }
    // vector dp(sz(trie), vector(K, vi(1 << n)));
    // dp[0][0][0] = 1;
    // rep(len, 0, k) {
    //     rep(t, 0, sz(trie)) {
    //         rep(mask, 0, 1 << n) {
    //             rep(c, 0, sz(frq)) {
    //                 int t1 = calc(t, c);
    //                 int mask1 = (mask | getMask1(t1)) & (~getMask2(t1));
    //                 (dp[t1][len+1][mask1] += frq[c] * dp[t][len][mask]) %= MOD;
    //             }
    //         }
    //     }
    // }
    // int ans = 0;
    // rep(t, 0, sz(trie)) {
    //     (ans += dp[t][k][0]) %= MOD;
    // }
    // // cout << "DFA:\n";
    // // rep(t, 0, sz(trie)) {
    // //     rep(c, 0, sz(frq)) {
    // //         cout << t << " " << c << " " << frq[c] << " " << calc(t, c) << endl;
    // //     }
    // // }
    // // cout << "masks:\n";
    // // rep(t, 0, sz(trie)){
    // //     cout << t << " " << getMask1(t) << " " << getMask2(t) << endl;
    // // }
    // // rep(len, 0, k+1) { 
    // //     rep(t, 0, sz(trie)) {
    // //         rep(mask, 0, 1 << n){
    // //             // cout << "len " << len << " node " << t << " mask " << mask << " = " << dp[t][len][mask] << endl;
    // //         }
    // //     }
    // // }
    // cout << ans << "\n";
    

    return 0;
}