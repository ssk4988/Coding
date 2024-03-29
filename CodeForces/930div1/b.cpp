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

struct FT
{
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif)
    { // a[pos] += dif
        for (; pos < sz(s); pos |= pos + 1)
            s[pos] += dif;
    }
    ll query(int pos)
    { // sum of values in [0, pos)
        ll res = 0;
        for (; pos > 0; pos &= pos - 1)
            res += s[pos - 1];
        return res;
    }
    int lower_bound(ll sum)
    { // min pos st sum of [0, pos] >= sum
        // Returns n if no sum is >= sum, or -1 if empty sum is.
        if (sum <= 0)
            return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1)
        {
            if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
                pos += pw, sum -= s[pos - 1];
        }
        return pos;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vl ans(n);
        string str;
        cin >> str;
        rep(iter, 0, 2){
            vi dir(n); // 1 right 0 left
            rep(i, 0, n)
            {
                dir[i] = str[i] == '>';
            }
            FT prefrights(n), preflefts(n);
            FT distrights(n), distlefts(n);
            rep(i, 0, n)
            {
                if (dir[i])
                {
                    prefrights.update(i, 1);
                    distrights.update(i, i);
                }
                else
                {
                    preflefts.update(i, 1);
                    distlefts.update(i, i);
                }
            }
            rep(i, 0, n)
            {
                if (dir[i] == 0)
                {
                    int onleft = prefrights.query(i);
                    int onright = preflefts.query(n) - preflefts.query(i);
                    if (onleft < onright)
                    {
                        // end at left
                        onright = 1 + onleft;
                        ll distonleft = ll(i) * onleft - distrights.query(i);
                        distonleft *= 2;
                        int ridx = preflefts.lower_bound(onright + preflefts.query(i));
                        ll distonright = (distlefts.query(ridx+1) - distlefts.query(i)) - ll(i) * onright;
                        distonright *= 2;
                        ans[iter ? (n - 1 - i) : i] = distonleft + distonright + i + 1;
                    }
                    else{
                        // end at right
                        onleft = onright;
                        ll distonright = distlefts.query(n) - distlefts.query(i);
                        distonright -= ll(i) * onright;
                        distonright *= 2;
                        int lidx = prefrights.lower_bound(prefrights.query(i) - onleft);
                        ll distonleft = ll(i) * onleft - (distrights.query(i) - distrights.query(lidx + 1));
                        distonleft *= 2;
                        ans[iter ? (n - 1 - i) : i] = distonleft + distonright + n - i;
                    }
                }
            }
            reverse(all(str));
            rep(i, 0, n){
                if(str[i] == '<') str[i] = '>';
                else str[i] = '<';
            }
        }
        rep(i, 0, n){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
