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
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    bool composite[32000];
    memset(composite, false, sizeof composite);
    composite[0] = composite[1] = true;
    vi primes;
    for(int i = 2; i < 32000; i++){
        if(!composite[i]){
            primes.pb(i);
            for(int j = i * i; j < 32000; j += i){
                composite[j] = true;
            }
        }
    }
    rep(cn, 0, nc)
    {
        unordered_map<int, int> freq;
        int n;
        cin >> n;
        rep(i, 0, n)
        {
            int k;
            cin >> k;
            for(int p : primes){
                if(k % p == 0){
                    freq[p]++;
                    while(k % p == 0){
                        k /= p;
                    }
                }
            }
            if(k > 1) freq[k]++;
        }
        bool works = false;
        for (auto &p : freq)
        {
            if (p.s > 1)
            {
                works = true;
                break;
            }
        }
        cout << (works ? "YES" : "NO") << nL;
    }

    return 0;
}