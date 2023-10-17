#include <bits/stdc++.h>

using namespace std;

using ll = long long int;
const ll mod = 1000000007;
int main()
{
    int n, h;
    cin >> n >> h;
    vector<ll> fact(n+ 1, 1);
    for (int i = 1; i <=n ; i++)
        fact[i] = fact[i - 1] * i % mod;

    vector<ll> pref(h+ 2);
    for (int i = 0; i < h; i++)
    {
        cin >> pref[i + 1];
        pref[i + 1] += pref[i];
    }
    pref[h+ 1] = n;
    vector<ll> dp(h+ 2);
    dp[0] = 0;
    for (int i = 1; i <= h+ 1; i++)
    {
        dp[i] = fact[pref[i]];
        // cout << dp[i] << " ";
        for (int j = 0; j < i; j++)
        {
            (dp[i] += mod -dp[j] *fact[pref[i] -pref[j]] % mod) %= mod;
        }
    }
    cout << dp[h+ 1] << endl;
    return 0;
}
