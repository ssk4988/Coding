#include <bits/stdc++.h>
using namespace std;

#define int long long

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using pii = pair<int, int>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

const int mod = 1e9 + 7;

struct node {
    ll len, sum;
    int left, right;
    int dist = 0;
};

vi initPSum;
int m;
vector<node> tree;

int add(int a, int b) {
    node nxt = {0, 0, a, b};
    if(a == -1) nxt.len += m, nxt.sum = (nxt.sum + initPSum.back()) % mod;
    else nxt.len += tree[a].len, nxt.sum = (nxt.sum + tree[a].sum) % mod;

    if(b == -1) nxt.len += m, nxt.sum = (nxt.sum + initPSum.back()) % mod;
    else nxt.len += tree[b].len, nxt.sum = (nxt.sum + tree[b].sum) % mod;

    tree.push_back(nxt);
    return nxt.sum;
}

int query(int i, int L, int R) {
    if(L > R) return 0;
    if(i == -1) {
        if(R >= m) return initPSum.back();
        return (initPSum[R+1] - initPSum[L] + mod) % mod;
    }
    if(R < 0 || L >= tree[i].len) return 0;
    if(L == 0 && R >= tree[i].len - 1) return tree[i].sum;
    if(tree[i].left == -2) return query(tree[i].right, L + tree[i].dist, R + tree[i].dist);
    int leftLen = i == -1 ? m : tree[tree[i].left].left;
    int left = query(tree[i].left, L, R);
    int right = query(tree[i].right, max(0LL, L - leftLen), R - leftLen);
    return (left + right) % mod;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    string s; cin >> s;
    m = sz(s);
    initPSum = vi(m+1);
    rep(i, 0, m)
        initPSum[i+1] = (initPSum[i] + s[i]) % mod;
    
    int res = 0;
    while(--n > 0) {
        string type; cin >> type;
        if(type == "SUB") {
            int i, L, R; cin >> i >> L >> R;
            res = query(i-1, L, R-1);
            node nxt = { R - L, res, -2, i-1 };
            nxt.dist = L;
            tree.push_back(nxt);
        }
        else {
            int a, b; cin >> a >> b; a--, b--;
            res = add(a, b);
        }
    }

    cout << res << '\n';

    return 0;
}
