#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void solve()
{
    int n, k; cin >> n >> k;

    ll ans = 0;
    vector<int> prefix(n, 0);

    for (int i = 0; i < n; i++)
    {
        int x; cin >> x;

        // add each soldier to initial answer
        ans += x;

        // should this pass? the data has
        // zeros, so this does not work atm   
        // if (x > 0) prefix[i] = 1;
        // else prefix[i] = -1;

        // workaround for zeros in data
        prefix[i] = min(1, max(-1, x));
    }   

    // carry over prefix sums
    for (int i = 1; i < n; i++)
        prefix[i] += prefix[i-1];

    for (int i = 0; i < k; i++)
    {
        int b; cin >> b;
        
        // take bullet if it increases our answer
        if (prefix[b-1] > 0)
            ans += prefix[b-1];
    }

    cout << ans << '\n';
}

int main()
{
    int t; cin >> t;
    while (t--)
        solve();
    
    return 0;
}