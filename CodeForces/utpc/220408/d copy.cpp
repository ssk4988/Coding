#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

using vi = vector<int>;
using ll = long long;
using pi = pair<int, int>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vi composite(101);
    vi primes;
    rep(i, 2, sz(composite))
    {
        if (!composite[i])
        {
            primes.push_back(i);
            for (int j = i * 2; j < sz(composite); j += i)
                composite[j] = true;
        }
    }
    rep(ans, 2, 101)
    {
        bool isprime = !composite[ans];
        vi divs;
        // case of 2 3 5 7
        rep(i, 2, 11)
        {
            // cout << "? " << i << endl;
            // string res;
            // cin >> res;
            if (ans % i == 0)
            {
                divs.pb(i);
            }
        }
        bool prime = true;
        if (sz(divs) > 1)
            prime = false;
        else if (sz(divs) == 1)
        {
            if (composite[divs[0]])
                prime = false;
            else
            {
                int lim = (100 + divs[0] - 1) / divs[0];
                for (int i : primes)
                {
                    if (i <= 10 || i > lim)
                        continue;
                    // cout << "? " << i << endl;
                    // string res;
                    // cin >> res;
                    if (ans % i == 0)
                        prime = false;
                }
                if(divs[0] == 5){
                    if(ans % 25 == 0) prime = false;
                }
                if(divs[0] == 7){
                    if(ans % 49 == 0) prime = false;
                }
            }
        }
        if(prime != isprime){
            cout << ans << " actual:" << isprime << " mine: " << prime << "\n";
        }
    }
    // cout << sz(primes) << "\n";
    // for(int i : primes) cout << i << "\n";

    // cout << "! " << (prime ? "prime" : "composite") << endl;
}
