#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vl = vector<ll>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

const int ABSIZE = 26;
const int MOD = 1000003;
struct node {
    int nxt[ABSIZE];
    int dp[25][8];
    vi ids = {};
    int prv = -1, link = -1;
    int linkwords = -1;
    char c;
    int linkMemo[ABSIZE];
    node(int prv = -1, char c = '$'): prv(prv), c(c) {
        fill(all(nxt), -1);
        fill(all(linkMemo), -1);
        memset(dp, 0, sizeof dp);
    }
};

vector<node> trie;

void addWord(string& s, int id) {
    int cur = 0;
    for(char c : s) {
        int idx = c - 'a';
        if(trie[cur].nxt[idx] == -1) {
            trie[cur].nxt[idx] = sz(trie);
            trie.emplace_back(cur, c);
        }
        cur = trie[cur].nxt[idx];
    }
    trie[cur].ids.push_back(id);
}

int getLink(int cur);

int calc(int cur, char c) {
    int idx = c - 'a';
    auto &ret = trie[cur].linkMemo[idx];
    if(ret != -1) return ret;
    if(trie[cur].nxt[idx] != -1)
        return ret = trie[cur].nxt[idx];
    return ret = cur == 0 ? 0 : calc(getLink(cur), c);
}

int getLink(int cur) {
    auto &ret = trie[cur].link;
    if(ret != -1) return ret;
    if(cur == 0 || trie[cur].prv == 0) return ret = 0;
    return ret = calc(getLink(trie[cur].prv), trie[cur].c);
}

int linkSum(int cur) {
    auto &ret = trie[cur].linkwords;
    if(ret != -1) return ret;
    ret = sz(trie[cur].ids);
    if(getLink(cur) != cur) ret += linkSum(getLink(cur));
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    trie.resize(1);

    int a, b; cin >> a >> b;
    int n; cin >> n;
    rep(i, 0, n){
        string s; cin >> s;
        addWord(s, i);
    }
    auto dfs = [&](int t, string path, auto &&dfs) -> void {
        // cout << t << " word: " << path << " link cnt: " << linkSum(t) << " " << sz(trie[t].ids) << endl;
        rep(c, 0, 26) {
            if(trie[t].nxt[c] == -1) continue;
            dfs(trie[t].nxt[c], path + char(c + 'a'), dfs);
        }
    };
    dfs(0, "", dfs);
    trie[0].dp[0][0] = 1;
    rep(L, 0, b+1) {
        rep(t, 0, sz(trie)) {
            if (linkSum(t) > 0) continue;
            rep(mask, 0, 8) {
                rep(c, 'A', 'Z' + 1) {
                    int nmask = mask | (1 << 0);
                    int nxt = calc(t, c - 'A' + 'a');
                    if(linkSum(nxt) > 0) continue;
                    (trie[nxt].dp[L+1][nmask] += trie[t].dp[L][mask]) %= MOD;
                }
                rep(c, 'a', 'z' + 1) {
                    int nmask = mask | (1 << 1);
                    int nxt = calc(t, c);
                    if(linkSum(nxt) > 0) continue;
                    (trie[nxt].dp[L+1][nmask] += trie[t].dp[L][mask]) %= MOD;
                }
                rep(c, 0, 10) {
                    int nmask = mask | (1 << 2);
                    char ac = '$';
                    if(c == 0) ac = 'o';
                    if(c == 1) ac = 'i';
                    if(c == 3) ac = 'e';
                    if(c == 5) ac = 's';
                    if(c == 7) ac = 't';
                    int nxt = ac == '$' ? 0 : calc(t, ac);
                    if(linkSum(nxt) > 0) continue;
                    (trie[nxt].dp[L+1][nmask] += trie[t].dp[L][mask]) %= MOD;
                }
            }
        }
    }
    int ans = 0;
    rep(L, a, b+1) {
        rep(t, 0, sz(trie)) {
            if(linkSum(t) > 0) continue;
            (ans += trie[t].dp[L][7]) %= MOD;
        }
    }
    cout << ans << "\n";

    return 0;
}

// 5823813