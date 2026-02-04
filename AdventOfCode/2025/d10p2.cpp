#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
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


int solve() {
    vector<string> chunks;
    string line;
    getline(cin, line);
    // cout << ">" << line << "<line\n";
    stringstream ss(line);
    string token;
    while(getline(ss, token, ' ')) {
        chunks.push_back(token);
        // cout << ">" << token << "<\n";
    }
    int n = sz(chunks[0])-2;
    vi ids(n);
    rep(i, 0, n) {
        ids[i] = uniform_int_distribution<int>(1, 1e9)(rng);
    }
    int m = sz(chunks)-2;
    auto splitcomma = [](string s) {
        vi res;
        stringstream ss(s);
        string token;
        while(getline(ss, token, ',')) {
            res.push_back(stoi(token));
        }
        return res;
    };
    vi targ = splitcomma(chunks.back().substr(1, sz(chunks.back())));
    int targethash = 0;
    rep(i, 0, n) rep(j, 0, targ[i]) targethash += ids[i];
    vi rows(m), mx(m, 1e9);
    rep(i, 0, m) {
        vi but = splitcomma(chunks[i+1].substr(1, sz(chunks[i+1])-2));
        for(int j : but) rows[i] += ids[j], mx[i] = min(mx[i], targ[j]);
    }
    unordered_set<int> seen;
    seen.insert(0);
    queue<array<int, 4>> q;
    q.push({0, 0, 0, 0});
    while(sz(q)) {
        auto [d, h, start, freq] = q.front(); q.pop();
        rep(i, start, m) {
            int h2 = h + rows[i];
            int freq2 = i == start ? freq+1 : 1;
            if(h2 == targethash) return d+1;
            if(freq2 > mx[i]) continue;
            if(seen.count(h2)) continue;
            seen.insert(h2);
            q.push({d+1, h2, i, freq2});
        }
    }

    assert(false);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    string t; getline(cin, t);
    int ans = 0;
    rep(cn, 0, nc) {
        ans += solve();
        cout << "finished " << cn << " " << nc << endl;
    }
    cout << ans << "\n";
    // solve();
    
    return 0;
}
