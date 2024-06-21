#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n = 10;
    vector<string> b(3);
    rep(i, 0, 3) cin >> b[i];
    string o = "ogrc";
    vector<string> m;
    auto rot = [&](int i, int r) -> void
    {
        if (r == 0 || r == n) return;
        m.push_back(o[i] + to_string(r));
        if (i < 3) rotate(b[i].begin(), b[i].end() - r, b[i].end());
        else while (r) {
            rep(j, 0, 3){
                swap(b[0][j], b[1][j]);
                swap(b[1][j], b[2][j]);
            }
            r--;
        }
    };
    rep(x, 0, 3)
    {
        while (b[x] != string(n, o[x]))
            rep(y, x + 1, 3)
            {
                while (true)
                {
                    int t = find(all(b[y]), o[x]) - b[y].begin();
                    if (t == n) break;
                    rot(y, n - t);
                    rep(t, 0, n){
                        if (b[x][t] != o[x]){
                            rot(x, n - t);
                            break;
                        }
                    }
                    int i = x, j = y;
                    if (i + 1 != j) swap(i, j);
                    rot(j, 3);
                    rot(3, 2);
                    rot(j, n - 1);
                    rot(3, 1);
                }
            }
    }
    cout << sz(m) << "\n";
    for (auto s : m) cout << s << "\n";
    return 0;
}
