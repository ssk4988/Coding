#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using int128 = __int128_t;

typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ld> vd;
typedef vector<pi> vpi;
using vvi = vector<vi>;
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

struct Eertree {
	vi slink = {0, 0}, len = {-1, 0};
	vvi down, dlink;
	int cur = 0, t = 0;
    vi curst, tst, nodes;
    vector<array<int, 3>> downst;
    string str;
	Eertree() : down(2, vi(26, -1)), dlink(2, vi(26)) {}
    void add(char c) {
        nodes.push_back(sz(len));
        curst.push_back(cur);
        tst.push_back(t);
        str += c;
        int ci = c - 'a';
        if (t <= 0 || str[t-1] != c)
            cur = dlink[cur][ci], t = sz(str)-1 - len[cur];
        if (down[cur][ci] == -1) {
            downst.push_back({cur, ci, down[cur][ci]});
            down[cur][ci] = sz(slink);
            down.emplace_back(26, -1);
            len.push_back(len[cur] + 2);
            if (len.back() > 1) {
                slink.push_back(down[dlink[cur][ci]][ci]);
                // do t = (sz(str)-1) - len[cur = slink[cur]];
                // while(t <= 0 || str[t-1] != c);
                // slink.push_back(down[cur][ci]);
            } else slink.push_back(1);
            cur = sz(slink) - 1;
            dlink.push_back(dlink[slink[cur]]);
            dlink[cur][str[sz(str)-1 - len[slink[cur]]] - 'a'] = slink[cur];
        } else cur = down[cur][ci], downst.push_back({-1, -1, -1});
        t = (sz(str)-1) - len[cur] + 1;
    }
    void pop() {
        str.pop_back();
        slink.resize(nodes.back());
        len.resize(nodes.back());
        down.resize(nodes.back());
        dlink.resize(nodes.back());
        cur = curst.back();
        t = tst.back();
        if (downst.back()[0] != -1) down[downst.back()[0]][downst.back()[1]] = downst.back()[2];
        curst.pop_back();
        tst.pop_back();
        downst.pop_back();
        nodes.pop_back();
    }
};

Eertree e;
int128 ans = 0;
void rec(string& curr, int index, int stop, int lim) {
    if(sz(e.len) - 2 != sz(curr)) {
        return;
    }
    if(index == stop) {
        if(sz(e.len) - 2 == sz(curr)){
        // if(cnt(curr) == 1) {
            int128 have = stop;
            int128 here = 1;
            for(int i = 0; i < lim; i++) {
                here *= have;
                have--; 
            }
            ans += here;
        }
        return;
    }
    for(int i = 0; i < min(stop, lim + 1); i++) {
        char j = (char) ('a' + i);
        curr += j;
        e.add(j);
        rec(curr, index + 1, stop, max(lim, i + 1));
        curr.pop_back();
        e.pop();
    }
}

string int128str(int128 v) {
    string res;
    while (v){
        res.pb('0' + (v%10));
        v /= 10;
    }
    reverse(all(res));
    return res;
}

void solve() {
    ll start = chrono::steady_clock::now().time_since_epoch().count();
    for(int i = 1; i <= 23; i++) {
        string init;
        ans = 0;
        rec(init, 0, i, 0);

        long double res = ans;
        int128 div = 1;
        for(int j = 0; j < i; j++) div *= i;
        res /= div;
        cout << "k=" << i << "; count(k) = " << int128str(ans) << "; proportion = ";
        cout << fixed << setprecision(10) << res << endl;
        ll cur_time = chrono::steady_clock::now().time_since_epoch().count();
        cout << "duration: " << (cur_time-start)/1e9 << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc = 1;
    // cin >> tc;

    for(int tt = 1; tt <= tc; tt++) {
        solve();
    }

    return 0;
}
