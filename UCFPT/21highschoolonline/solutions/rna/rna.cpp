#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

// triple hashing, just to be safe
const int HASHES = 3;
const ll BETA = 23;
const ll BASE[] = { (ll)1e9 + 7, (ll)1e9 + 9, (ll)1e9 + 21 };

const char RNA[] = { 'A', 'U', 'G', 'C' };

// returns a^n mod m
ll binpow(ll a, ll n, ll m)
{
    if (n == 0) return 1;
    if (n & 1) return (a * binpow(a, n-1, m)) % m;
    ll val = binpow(a, n / 2, m);
    return (val * val) % m;
}

// converts an rna triplet into an integer from 0 to 63
int get_id(const string &s)
{
    int id = 0;

    for (int i = 0; i < 3; i++)
    {
        id *= 3;
        for (int j = 0; j < 4; j++)
            if (s[i] == RNA[j])
                id += j;
    }
    
    return id;
}

// takes an rna string and converts it into a string
// of condons, after shifting forwards k places
vector<int> make_string(string &s, vector<int> &codons, int k)
{
    vector<int> ret;

    for (int i = 0; 3*(i+1) + k <= s.length(); i++)
        ret.push_back(codons[get_id(s.substr(3*i + k, 3))]);

    return ret;
}

// adds the hashes of all substrings of a given length 
void add_substrings(vector<int> &s, int r, set<vector<ll>> &sub_hashes)
{
    if (s.size() < r)
        return;

    vector<ll> rem(HASHES), hash(HASHES);
    queue<int> q;

    // this is what the coefficient will be on things
    // we want to remove from the hash
    for (int i = 0; i < HASHES; i++)
        rem[i] = binpow(BETA, r, BASE[i]);
    
    // insert the first r characters into the hash
    for (int i = 0; i < r; i++)
    {
        q.push(s[i]);

        for (int j = 0; j < HASHES; j++)
            hash[j] = (hash[j] * BETA + s[i]) % BASE[j];
    }

    sub_hashes.insert(hash);

    // for the rest of the string, we roll the hash over
    // by inserting a character, then removing the last one
    for (int i = r; i < s.size(); i++)
    {
        q.push(s[i]);

        for (int j = 0; j < HASHES; j++)
            hash[j] = (hash[j] * BETA + s[i]) % BASE[j];

        int out = q.front(); q.pop();
  
        for (int j = 0; j < HASHES; j++)
        {
            ll outval = (out * rem[j]) % BASE[j];
            hash[j] = (hash[j] - outval + BASE[j]) % BASE[j];
        }

        sub_hashes.insert(hash);
    }
}   

void solve()
{   
    string s; cin >> s;

    vector<int> codons(64);

    // read in the codons
    for (int i = 0; i < 64; i++)
    {
        string x;
        int a;
        cin >> x >> a;

        codons[get_id(x)] = a;
    }

    int r; cin >> r;

    set<vector<ll>> sub_hashes;

    // we produce different strings by reading at the
    // first, second, and third characters.
    // we can create these strings, and insert all hashes
    // of substrings lengths r / 3.
    for (int i = 0; i < 3; i++)
    {
        vector<int> a = make_string(s, codons, i);
        add_substrings(a, r / 3, sub_hashes);
    }

    cout << sub_hashes.size() << '\n';
}

int main()
{
    int t; cin >> t; 
    
    while (t--)
        solve();

    return 0;
}
