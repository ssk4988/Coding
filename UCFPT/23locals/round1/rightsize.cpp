#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < (b); i++)

using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

#define pb push_back
#define f first
#define s second

bool cmp(pair<ll, string> &a, pair<ll, string> &b)
{
    if (a.f == b.f)
        return a.s > b.s;
    return a.f < b.f;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q;
    cin >> n >> q;
    vector<pair<ll, string>> es(n);
    // set<pair<ll, string>> ss([](pair<ll, string> &a, pair<ll, string> &b) -> bool
    //                          {if(a.f == b.f) return a.s < b.s;
    // return a.f > b.f; });
    priority_queue<pair<ll, string>, vector<pair<ll, string>>, decltype(&cmp)> ss(&cmp);
    map<string, int> cc;
    rep(i, 0, n)
    {
        cin >> es[i].s >> es[i].f;
        ss.push(es[i]);
        cc[es[i].s] = i;
    }
    rep(i, 0, q)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            string str;
            cin >> str;
            ll x;
            cin >> x;
            int v = cc[str];
            // ss.erase(es[v]);
            es[v].f += x;
            ss.push(es[v]);
        }
        else
        {
            while (true)
            {
                auto [w, s] = ss.top();
                if(es[cc[s]].f != w) ss.pop();
                else break;
            }
            auto [w, s] = ss.top();
            cout << s << " " << w << "\n";
            // ss.erase(ss.begin());
            ss.pop();
        }
    }
}
