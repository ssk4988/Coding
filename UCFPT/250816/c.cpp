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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vi a(n), b(n), s(n);
    ll last = 0;
    const int P = 20;
    vi kmp(n);
    vvi jmp(n+1, vi(P, -1)), letter(n+1, vi(P, -1));
    // i links to kmp[i]-1, except 0 links to 0
    // -1 if not all are same, otherwise has the letter
    jmp[n] = vi(P, n);
    ll bsum = 0;
    ll ans = 0;

    rep(i, 0, n) {
        cin >> s[i] >> a[i] >> b[i];
        (s[i] += last % n) %= n;
        if(i > 0) {
            int len = kmp[i-1];
            while(len > 0 && s[len] != s[i]) len = kmp[len-1];
            kmp[i] = len + (s[i] == s[len]);
            jmp[i-1][0] = kmp[i-1]-1;
            if(jmp[i-1][0] == -1) jmp[i-1][0] = n;
            letter[i-1][0] = s[i];
            rep(p, 0, P-1) {
                jmp[i-1][p+1] = jmp[jmp[i-1][p]][p];
                letter[i-1][p+1] = (letter[i-1][p] == letter[jmp[i-1][p]][p]) ? letter[i-1][p] : -1;
            }
            int u = i-1;
            while(u != n) {
                // find longest prefix that doesn't have s[i] as next letter
                for(int p = P-1; p >= 0; p--) {
                    if(letter[u][p] == s[i]) {
                        u = jmp[u][p];
                    }
                }
                if(u != n && letter[u][0] != s[i]) {
                    // cerr << "at i=" << i << " sub out " << i-1-u << " u=" << u << endl;
                    bsum -= b[i-1-u];
                    u = jmp[u][0];
                }
            }
        }
        if(s[i] == s[0]) {
            bsum += b[i];
        }
        ans += bsum * a[i];
        cout << ans << "\n";
        last = ans;
        // cerr << "i=" << i << " kmp=" << kmp[i] << " bsum=" << bsum << endl;
    }

    return 0;
}
