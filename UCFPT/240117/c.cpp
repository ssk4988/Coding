#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

const ll MOD = 998244353;
inline ll mod(ll k){
    return k % MOD;
}

int n;


struct Eertree {
	vector<int> slink = {0, 0}, len = {-1, 0}, idx = {0, 0};
	vector<vector<int>> down;
	int cur = 0, t = 0;
    vl ans = {0, 0};
	Eertree(string &str) : down(2, vector<int>(10, -1)) {
		for(int i = 0; i < str.size(); i++) {
            char c = str[i]; int ci = c - '0';
            while(t <= 0 || str[t-1] != c)
            t = i - len[cur = slink[cur]];
            if (down[cur][ci] == -1) {
                down[cur][ci] = slink.size();
                down.emplace_back(10, -1);
                len.push_back(len[cur] + 2);
                ans.push_back(0);
                idx.push_back(i);
                if(len.back() > 1) {
                    do t = i - len[cur = slink[cur]];
                    while(t <= 0 || str[t-1] != c);
                    slink.push_back(down[cur][ci]);
                } else slink.push_back(1);
                cur = slink.size() - 1;
            } else cur = down[cur][ci];
            if(i >= n)
                ans[cur]++;
            t = i - len[cur] + 1;
        }
	}
    vector<pair<pii, ll>> calc() {
        vector<pair<pii, ll>> res;
        for(int i = sz(slink) - 1; i >= 2; i--){
            ans[slink[i]] = mod(ans[slink[i]] + ans[i]);
            res.push_back({{idx[i] - len[i] + 1, idx[i]}, ans[i]});
        }
        return res;
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;
    string str; cin >> str;
    vector<pair<pii, ll>> res2;
    str += str;
    Eertree e(str);
    res2 = e.calc();
    // sort(all(res1));
    // sort(all(res2));
    // int p = 0;
    // for(auto [key, val] : res1){
    //     while(p < sz(res2) && res2[p].first < key) p++;
    //     if(p < sz(res2) && res2[p].first == key){
    //         res2[p].second = mod(res2[p].second + MOD - val);
    //     }
    // }
    ll ans = 0;
    for(auto [key, val] : res2){
        int len = key.second - key.first + 1;
        if(len > n) continue;
        if(key.first >= n) continue;
        ans = mod(ans + mod(val * mod(val * len)));
    }
    cout << ans << "\n";
    // cout << str << "\n";
    
    // cout << res << "\n";

    return 0;
}
