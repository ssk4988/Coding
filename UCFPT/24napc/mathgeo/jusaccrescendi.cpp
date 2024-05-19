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
;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
using a4 = array<int, 4>;

bool go(a4 &cur, int idx, int left, int x) 
{
    if (idx == 3)
    {

        // vi cnt(2);
        // rep(i, 0, 4){
        //     if(i & 2) cnt[1] += cur[i];
        //     if(i & 1) cnt[0] += cur[i];
        // }
        cur[3] = left;
        // cout << cur[0] << " " << cur[1] << " " << cur[2] << " " << cur[3] << "\n";
        int make = cur[0] * cur[1] * cur[2] + cur[0] * cur[2] * cur[3] + cur[1] * cur[2] * cur[3] + cur[0] * cur[1] * cur[3];
        // if(make == x) return true;
        // cur[3] = 0;
        return make == x;
    }
    if(go(cur, idx + 1, left, x)) return true;
    int o = cur[idx];
    for(int i = 0; left; i++){
        left--;
        cur[idx]++;
        if(go(cur, idx + 1, left, x)) return true;
    }
    cur[idx] = o;
    return false;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, x;
    cin >> n >> x;
    x = n * (n - 1) * (n - 2) / 6 - x;
    a4 start{0, 0, 0, 0};
    if (!go(start, 0, n, x))
    {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    // return 0;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(-1000, 1000);
    set<pii> pts;
    a4 cnt{0, 0, 0, 0};
    // cout << start[0] << " " << start[1] << " " << start[2] << " " << start[3] << "\n";
    // return 0;
    int tried = 0;
    while (true)
    {
        bool works = true;
        rep(i, 0, 4) if (cnt[i] != start[i]) works = false;
        if (works)
            break;
        works = true;
        while (true)
        {
            int x = dist(rng), y = dist(rng);
            // cout << "try " << x << " " << y << endl;
            tried++;
            int mask = ((x % 2 != 0) << 1) + ((y % 2 != 0));
            if (cnt[mask] >= start[mask])
                continue;
            if (pts.count({x, y}))
                continue;
            bool bad = false;
            for (auto [x1, y1] : pts)
            {
                for (auto [x2, y2] : pts)
                {
                    int dx = x2 - x1, dy = y2 - y1;
                    if (dx == 0 && dy == 0)
                        continue;
                    int dx1 = x - x1, dy1 = y - y1;
                    if (dx * dy1 - dx1 * dy == 0)
                    {
                        bad = true;
                        break;
                    }
                }
                if (bad)
                    break;
            }
            // cout << "check badness " << bad << endl;
            if (bad)
                continue;
            pts.insert({x, y});
            cnt[mask]++;
            break;
        }
    }
    for (auto [x, y] : pts)
        cout << x << " " << y << "\n";

    return 0;
}
