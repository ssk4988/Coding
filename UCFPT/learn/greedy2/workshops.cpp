#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int cn = 0;
    while(true){
        int n; cin >> n;
        if(n == 0) break;
        vii w(n);
        rep(i, 0, n) {
            cin >> w[i].f >> w[i].s;
            w[i].f *= -1;
        }
        sort(all(w));
        pii ans;
        int r; cin >> r;
        vii rooms(r);
        rep(i, 0, r) {
            cin >> rooms[i].f;
            string s; cin >> s;
            int h = stoi(s.substr(0, 2)), m = stoi(s.substr(3, 2));
            h -= 14;
            rooms[i].s = h * 60 + m;
        }
        for(auto [people, duration] : w) {
            people *= -1;
            int best = -1;
            rep(i, 0, sz(rooms)) {
                auto [people1, duration1] = rooms[i];
                if(people > people1 || duration > duration1) continue;
                if(best == -1 || duration1 < rooms[best].s) best = i;
            }
            if(best == -1) ans.f++, ans.s += people;
            else rooms.erase(begin(rooms)+best);
        }
        // bruh, had to empty file AC after multiple Presentation Errors
        cout << "Trial " << (++cn) << ": " << ans.f << " " << ans.s << "\n";
    }
    return 0;
}
