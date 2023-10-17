#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)

using vi = vector<int>;
using ll = long long;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;


const ll MOD = 1e9 + 7;
ll mod(ll k){
    return k % MOD;
}
ll mod1(ll k){
    return (k % MOD + MOD) % MOD;
}

int main()
{
    // mimic Andy's code to figure out the WA
    int n, h;
    cin >> n >> h;
    vector<ll> fact(n + 10);
    fact[0] = 1;
    rep(i, 1, sz(fact))
        fact[i] = mod(fact[i - 1] * i);

    vector<ll> hs(h+ 2);
    for (int i = 0; i < h; i++)
    {
        cin >> hs[i + 1];
        hs[i + 1] += hs[i];
    }
    hs[h + 1] = n;
    vector<ll> revs(h + 2);
    rep(i, 1, sz(revs))
    {
        revs[i] = fact[hs[i]];
        // cout << dp[i] << " ";
        for (int j = 0; j < i; j++)
        {
            revs[i] = mod1(revs[i] - mod(revs[j] * fact[hs[i] - hs[j]]));
        }
    }
    cout << revs.back() << endl;
    return 0;
}
