#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int ans = 0;
struct node {
    vector<node*> ch;
    int cnt = 0;
    int dp = 0;
    node() : ch(26, NULL) {};
    void calc() {
        vi dps;
        int cs = 0;
        rep(c, 0, 26) if(ch[c]) {
            ch[c]->calc();
            if(!ch[c]->cnt) continue;
            cs++;
            dps.push_back(ch[c]->dp);
        }
        sort(all(dps));
        reverse(all(dps));
        if(cnt) {
            dp++;
            dp += cs;
            if(sz(dps)) {
                dp--;
                dp += dps[0];
            }
        }
        int cand = cnt + cs;
        rep(i, 0, min(2, sz(dps))) {
            cand += dps[i]-1;
        }
        ans = max(ans, cand);
    }
};

node root;
void add(string &s) {
    node *cur = &root;
    for(char c : s) {
        int ci = c - 'a';
        if(!cur->ch[ci]) cur->ch[ci] = new node();
        cur = cur->ch[ci];
    }
    cur->cnt++;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    rep(i, 0, n) {
        string s; cin >> s;
        reverse(all(s));
        add(s);
    }
    root.calc();
    cout << ans << "\n";

    return 0;
}
