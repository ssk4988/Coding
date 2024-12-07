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

void solve(int cn) {
    int n, k; cin >> n >> k;
    if(!(n % 2 == 1 || k % 2 == 0)){
        cout << "NO\n";
        return;
    }
    if(n == 1){
        if(k == 1){
            cout << "YES\n";
            cout << "1\n";
        }
        else{
            cout << "NO\n";
        }
        return;
    }
    if(k == 1){
        cout << "NO\n";
        return;
    }
    if(n < 12){
        ll fact = 1;
        rep(i, 1, n+1)
            fact *= i;
        if(k > fact || k == fact - 1 || k == 1){
            cout << "NO\n";
            return;
        }
    }
    vvi perms;
    set<vi> used;
    int target = (n+1) * k / 2;
    if(k % 2 == 1) {
        vi iden(n);
        iota(all(iden), 1);
        perms.pb(iden);
        int target3 = (n+1) * 3 / 2;
        vi p1(n), p2(n);
        iota(all(p1), 1);
        rotate(begin(p1), begin(p1) + n/2, end(p1));
        perms.pb(p1);
        rep(i, 0, n){
            p2[i] = target3 - p1[i] - iden[i];
        }
        perms.pb(p2);
        for(auto &v : perms){
            used.insert(v);
        }
    }
    vi perm(n), perm2(n);
    iota(all(perm), 1);
    do {
        if(sz(perms) >= k) break;
        rep(i, 0, n){
            perm2[i] = n + 1 - perm[i];
        }
        if(used.count(perm) || used.count(perm2)) continue;
        perms.pb(perm);
        perms.pb(perm2);
        used.insert(perm);
        used.insert(perm2);
    }
    while(next_permutation(all(perm)));
    cout << "YES\n";
    for(auto &p : perms){
        rep(i, 0, n){
            cout << p[i] << " ";
        }
        cout << "\n";
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve(cn);
    }
    
    return 0;
}
