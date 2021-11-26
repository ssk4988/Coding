/*
 *  Problem: RNA
 *  Author: Atharva Nagarkar
 *  Extra Solution (Used to generate data)
*/


#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> //gp_hash_table

#define all(a) a.begin(), a.end()
#define pb push_back
#define eb emplace_back

using namespace std;
using namespace __gnu_pbds;


typedef long long int ll;
typedef pair<int, int> pii;

const int N = (int) 1e6 + 10;
const int MODS[2]{(int) 1e9 + 7, (int) 1e9 + 9};
const int BASE = 23;

int add(int a, int b, int MOD) { return (a + b) % MOD; }
int sub(int a, int b, int MOD) { return (a - b + MOD) % MOD; }
int mult(ll a, ll b, int MOD) { return (a * b) % MOD; }
int bin_pow(int n, int k, int MOD) {
    int ans = 1;
    while(k) {
        if(k % 2 == 0) {
            k /= 2;
            n = mult(n, n, MOD);
        } else {
            k--;
            ans = mult(ans, n, MOD);
        }
    }
    return ans;
}
int inv(int n, int MOD) { return bin_pow(n, MOD - 2, MOD); }
int pows[2][N], ipows[2][N];

int n, r, len;
string s;
map<string, int> mp;
vector<vector<pii>> hashes;

vector<pii> build_hash(vector<int>& a) {
    int n = a.size();
    vector<pii> prefix;
    int cur_hash1 = 0, cur_hash2 = 0;
    int pw1 = 1, pw2 = 1;
    for(int i = 0; i < n; ++i) {
        int x = a[i];
        cur_hash1 = add(cur_hash1, mult(x, pw1, MODS[0]), MODS[0]);
        cur_hash2 = add(cur_hash2, mult(x, pw2, MODS[1]), MODS[1]);
        prefix.eb(cur_hash1, cur_hash2);
        pw1 = mult(pw1, BASE, MODS[0]);
        pw2 = mult(pw2, BASE, MODS[1]);
    }
    return prefix;
}

pii get_hash(vector<pii>& prefix, int& l, int& r) {
    pii ans = prefix[r];
    if(l > 0) {
        ans.first = sub(ans.first, prefix[l - 1].first, MODS[0]);
        ans.second = sub(ans.second, prefix[l - 1].second, MODS[1]);
    }
    ans.first = mult(ans.first, ipows[0][l], MODS[0]);
    ans.second = mult(ans.second, ipows[1][l], MODS[1]);
    return ans;
}

void solve() {
    cin >> s; n = s.length();
    mp.clear();
    for(int i = 0; i < 64; ++i) {
        string x; cin >> x;
        int a; cin >> a;
        mp[x] = a;
    }
    cin >> r; len = r / 3;
    hashes.clear();
    for(int i = 0; i < 3; ++i) {
        vector<int> list;
        for(int j = i; j + 2 < n; j += 3) {
            string sub = s.substr(j, 3);
            list.pb(mp[sub]);
        }
        hashes.pb(build_hash(list));
    }
    set<pii> S;
    for(int i = 0; i < n; ++i) {
        vector<pii>& list = hashes[i % 3];
        int l = i / 3, r = l + len - 1;
        if(r >= list.size()) continue;
        pii cur_hash = get_hash(list, l, r);
        S.insert(cur_hash);
    }
    cout << S.size() << '\n';
}

void precomp() {
    for(int a = 0; a < 2; ++a) {
        int MOD = MODS[a];
        pows[a][0] = ipows[a][0] = 1;
        int cinv = inv(BASE, MOD);
        for(int i = 1; i < N; ++i) {
            pows[a][i] = mult(pows[a][i - 1], BASE, MOD);
            ipows[a][i] = mult(ipows[a][i - 1], cinv, MOD);
        }
    }
}

int main() {
    // freopen("input.in", "r", stdin);
    // freopen("input.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.precision(20);
    cout << fixed;
    precomp();
    int t; cin >> t; while(t--)
    solve();
    cout.flush();
    return 0;
}