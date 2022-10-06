#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
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
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll start = 0, target = 0;
    int x, y;
    rep(i, 0, 4)
    {
        cin >> x >> y;
        start |= ((ll)1 << (6 * x + y));
    }
    rep(i, 0, 4)
    {
        cin >> x >> y;
        target |= ((ll)1 << (6 * x + y));
    }
    int maxbit = 36;
    unordered_map<ll, pair<int, ll>> ans;
    deque<tuple<ll, ll, int>> q;
    q.emplace_back(start, 0, 0);
    int shift[] = {1, -1, 6, -6};
    int cnt = 0;
    while (!q.empty())
    {
        auto [pos, prevpos, depth] = q.front();
        q.pop_front();
        bitset<64> p(pos);
        if (cnt % 100000 == 0)
        {
            // cout << __builtin_popcountll(pos) << " " << depth << " " << ans.size() << " " << cnt << nL;
            // cout << p << nL;
            //  return 0;
        }
        cnt++;
        if(ans.find(pos)!=ans.end()){
            continue;
        }
        ans[pos] = mp(depth, prevpos);
        if (pos == target)
            break;
        rep(i, 0, 36)
        {
            if ((pos & ((ll)1 << i)) == 0)
                continue;
            int r = i / 6;
            int c = i % 6;
            rep(j, 0, 4)
            {
                ll nextpos = pos ^ ((ll)1 << i);
                int nextbit = i;
                while (
                    ((j >= 2 && nextbit + shift[j] >= 0 && nextbit + shift[j] < 36) ||
                     (j < 2 && nextbit + shift[j] >= r * 6 && nextbit + shift[j] < r * 6 + 6)) &&
                    (nextpos & ((ll)1 << (nextbit + shift[j]))) == 0)
                {
                    nextbit += shift[j];
                }
                if (nextbit == i)
                    continue;
                nextpos |= ((ll)1 << nextbit);
                if (ans.find(nextpos) == ans.end())
                {
                    q.emplace_back(nextpos, pos, depth + 1);
                }
            }
        }
    }
    ll cur = target;
    ll prevpos;
    int depth;

    tie(depth, prevpos) = ans[cur];
    cout << depth << nL;
    int moves[depth][4];
    int d = depth;
    while (cur != start)
    {
        depth--;
        ll diff = prevpos ^ cur;
        cur = prevpos;
        rep(i, 0, 36)
        {
            if (diff & ((ll)1 << i))
            {
                if (prevpos & ((ll)1 << i))
                {
                    moves[depth][0] = i / 6;
                    moves[depth][1] = i % 6;
                }
                else
                {
                    moves[depth][2] = i / 6;
                    moves[depth][3] = i % 6;
                }
            }
        }
        tie(depth, prevpos) = ans[cur];
    }
    rep(i, 0, d)
    {
        cout << moves[i][0] << " " << moves[i][1] << " " << moves[i][2] << " " << moves[i][3] << nL;
    }
    //cout << ans.size() << " " << cnt << nL;

    return 0;
}