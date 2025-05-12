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
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
random_device rd;
mt19937 rng(rd());


map<pii, bool> cache;
bool cmp(int a, int b) {
    if(a == b) return false;
    if(cache.count({a, b})) return cache[{a, b}];
    if(cache.count({b, a})) return !cache[{b, a}];
    cout << "? " << a+1 << " " << b+1 << endl;
    string s; cin >> s;
    cache[{a, b}] = s == "YES";
    return cache[{a, b}];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi perm(n);
    vi idxs(n);
    shuffle(all(idxs), rng);
    auto dfs = [&](vi cur, auto &&dfs) -> vi {
        if(sz(cur) <= 1) return cur;
        int split = sz(cur) / 2;
        vi left{begin(cur), begin(cur)+split};
        vi right{begin(cur)+split, end(cur)};
        left = dfs(left, dfs), right = dfs(right, dfs);
        vi res;
        int l = 0, r = 0;
        while(l < sz(left) || r < sz(right)) {
            if(r == sz(right) || (l < sz(left) && cmp(left[l], right[r]))){
                res.pb(left[l++]);
            } else res.pb(right[r++]);
        }
        return res;
    };
    iota(all(idxs), 0);
    idxs = dfs(idxs, dfs);
    rep(i, 0, n) {
        perm[idxs[i]] = i;
    }
    cout << "! ";
    rep(i, 0, n) {
        cout << perm[i]+1 << " ";
    }
    cout << endl;
    
    
    return 0;
}
