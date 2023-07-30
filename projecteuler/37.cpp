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

const int MAX_PR = 5'000'000;
bitset<MAX_PR> isprime;
vi eratosthenesSieve(int lim) {
	isprime.set(); isprime[0] = isprime[1] = 0;
	for (int i = 4; i < lim; i += 2) isprime[i] = 0;
	for (int i = 3; i*i < lim; i += 2) if (isprime[i])
		for (int j = i*i; j < lim; j += i*2) isprime[j] = 0;
	vi pr;
	rep(i,2,lim) if (isprime[i]) pr.push_back(i);
	return pr;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    eratosthenesSieve(MAX_PR);
    int cnt = 0;
    ll sum = 0;
    rep(i, 10, 1'000'000){
        // if(cnt == 11) break;
        if(!isprime[i]) continue;
        bool works = true;
        int j = i;
        while(j){
            if(!isprime[j]) works = false;
            j /= 10;
        }
        if(!works) continue;
        string is = to_string(i);
        while(is.size()){
            if(!isprime[stoi(is)]) works = false;
            is = is.substr(1);
        }
        if(works){
            cnt++;
            sum += i;
            cout << i << nL;
        }
    }
    cout << sum << nL;
    
    return 0;
}