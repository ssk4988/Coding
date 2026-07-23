#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ld = long double;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

const int MULT = 1e5;
ll read() {
    string s; cin >> s;
    int idx = s.find('.');
    ll start = stoll(s.substr(0, idx)) * MULT;
    if(idx != string::npos) {
        idx++;
        int place = MULT / 10;
        while(idx < sz(s)) {
            start += place * (s[idx] - '0');
            idx++;
            place /= 10;
        }
    }
    return start;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    ll a, b; cin >> a >> b;
    a *= MULT, b *= MULT;
    vl x(n);
    rep(i, 0, n) x[i] = read();
    rep(i, 0, n) cerr << x[i] << "\n";
    vl cand;
    rep(i, 0, n) {
        rep(j, 0, n) {
            cand.push_back(gcd(x[i], x[j]));
        }
    }
    sort(all(cand));
    cand.erase(unique(all(cand)), end(cand));
    {
        vl cand2;
        set<ll> xs(all(x));
        for(auto c : cand) {
            ll cstart = (a + c - 1) / c * c;
            ll cend = b / c * c;
            bool works = true;
            for(ll cc = cstart; cc <= cend && works; cc += c) {
                if(!xs.count(cc)) works = false;
            }
            if(works) cand2.push_back(c);
        }
        cand = cand2;
    }
    cerr << "works: " << endl;
    for(auto c : cand) {
        cerr << fixed << setprecision(5) << ld(c) / MULT << "\n";
    }
    {
        set<ll> cand2(all(cand));
        for(auto c : cand) {
            for(auto c1 : cand) {
                if(cand2.count(c1) && c1 % c == 0 && c1 != c) cand2.erase(c1);
            }
        }
        cand = vl(all(cand2));
    }
    cerr << "ans: " << endl;
    // cout << sz(cand) << "\n";
    for(auto c : cand) {
        cout << fixed << setprecision(5) << ld(c) / MULT << "\n";
    }

    return 0;
}
