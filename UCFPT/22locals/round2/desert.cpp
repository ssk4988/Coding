#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define pb push_back
#define mp make_pair
#define f first
#define s second

const int maxN = 5001;
ll dp[maxN][maxN];
int cpt[maxN];
ll c[maxN][2];
vi comp[maxN];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(20);
    int o;
    cin >> o;
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < o; i++)
    {
        cin >> c[i][0] >> c[i][1];
        comp[i].pb(i);
        cpt[i] = i;
    }
    vector<pair<ll, pii>> e;
    for (int i = 0; i < o; i++)
    {
        for (int j = 0; j < o; j++)
        {
            ll dist = ((ll)c[i][0] - c[j][0]) * ((ll)c[i][0] - c[j][0]) + ((ll)c[i][1] - c[j][1]) * ((ll)c[i][1] - c[j][1]);
            e.pb(mp(dist, mp(i, j)));
        }
    }
    sort(e.begin(), e.end());
    for (auto e1 : e)
    {
        if (cpt[e1.s.f] == cpt[e1.s.s])
            continue;
        int c1 = comp[cpt[e1.s.f]].size() >= comp[cpt[e1.s.s]].size() ? cpt[e1.s.f] : cpt[e1.s.s];
        int c2 = comp[cpt[e1.s.f]].size() >= comp[cpt[e1.s.s]].size() ? cpt[e1.s.s] : cpt[e1.s.f];
        for (int i : comp[c1])
        {
            for (int j : comp[c2])
            {
                dp[i][j] = dp[j][i] = e1.f;
            }
        }
        for (int j : comp[c2])
        {
            comp[c1].pb(j);
            cpt[j] = c1;
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int a;
        int b;
        cin >> a >> b;
        a--;
        b--;
        cout << sqrtl(dp[a][b]) << "\n";
    }
}