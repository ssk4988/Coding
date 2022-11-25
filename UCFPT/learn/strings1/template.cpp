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

#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

void count_sort(vector<int> &p, vector<int> &c)
{
    int n = p.size();

    vector<int> cnt(n);
    for (auto x : c)
    {
        cnt[x]++;
    }
    vector<int> p_new(n);
    vector<int> pos(n);
    pos[0] = 0;
    for (int i = 1; i < n; i++)
    {
        pos[i] = pos[i - 1] + cnt[i - 1];
    }
    for (auto x : p)
    {
        p_new[pos[c[x]]++] = x;
    }
    p = p_new;
}

vector<int> suffixarray(string &input)
{
    string str = input + "$";
    int n = str.length();
    vector<int> p(n), c(n);
    {
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++)
            a[i] = {str[i], i};
        sort(a.begin(), a.end());

        for (int i = 0; i < n; i++)
            p[i] = a[i].second;
        c[p[0]] = 0;

        for (int i = 1; i < n; i++)
        {
            c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
        }
    }

    int k = 0;
    while ((1 << k) < n)
    {
        for (int i = 0; i < n; i++)
        {
            p[i] = (p[i] - (1 << k) + n) % n;
        }
        count_sort(p, c);
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            c_new[p[i]] = c_new[p[i - 1]] + (cur != prev);
        }
        c = c_new;
        k++;
    }
    return p;
}

vector<int> getlcp(string &input, vector<int> &sa)
{
    string str = input + "$";
    int n = str.length();
    vector<int> lcp(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++)
    {
        c[sa[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int pi = c[i];
        int j = sa[pi - 1];
        while (str[i + k] == str[j + k])
            k++;
        lcp[c[i]] = k--;
        k = max(k, 0);
    }
    return lcp;
}

// vector<int> prefix_function(string str) {
//     int n = (int)str.length();
//     vector<int> pi(n);
//     for (int i = 1; i < n; i++) {
//         int j = pi[i-1];
//         while (j > 0 && str[i] != str[j])
//             j = pi[j-1];
//         if (str[i] == str[j])
//             j++;
//         pi[i] = j;
//     }
//     return pi;
// }

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str;
    cin >> str;
    int n = str.length();
    int lo = 1;
    int hi = n;
    vi sa = suffixarray(str);
    vi lcp = getlcp(str, sa);
    sa.erase(sa.begin());
    lcp.erase(lcp.begin());
    int l = -1, r = -1;
    rep(i, 0, n){
        if(sa[i] == 0){
            l = r = i;
            break;
        }
    }
    multiset<int> ranges;
    ranges.insert(n);
    set<int> pos;
    pos.insert(0);
    pos.insert(n);
    int ans = n;
    int clcp = n;
    while(l > 0 || r + 1 < n){
        int nextl = -1, nextr = -1;
        if(l > 0){
            nextl = lcp[l];
        }
        if(r + 1 < n){
            nextr = lcp[r + 1];
        }
        clcp = min(clcp, max(nextl, nextr));
        while(l > 0 && lcp[l] >= clcp){
            l--;
            pos.insert(sa[l]);
            int low = *prev(pos.find(sa[l]));
            int high = *next(pos.find(sa[l]));
            ranges.erase(ranges.find(high - low));
            ranges.insert(sa[l] - low);
            ranges.insert(high - sa[l]);
        }
        while(r + 1 < n && lcp[r + 1] >= clcp){
            r++;
            pos.insert(sa[r]);
            int low = *prev(pos.find(sa[r]));
            int high = *next(pos.find(sa[r]));
            ranges.erase(ranges.find(high - low));
            ranges.insert(sa[r] - low);
            ranges.insert(high - sa[r]);
        }
        if(*(ranges.rbegin()) <= clcp){
            ans = min(ans, clcp);
        }
    }
    cout << ans << nL;
    // vi z = z_function(str);
    // vi kmp = prefix_function(str);
    // int lastc = 0;
    // for(int i = 0; i < n; i++){
    //     if(kmp[i] == i){
    //         lastc = i;
    //     }
    // }
    // lastc++;
    // int dp[n + 1];
    // rep(i, 0, n + 1){
    //     dp[i] = max(i, lastc);
    // }
    // for(int i = lastc; i < n; i++){
    //     int k = kmp[i];
    //     while(k > lastc){
    //         if(i - k < dp[k]){
    //             dp[k] = i + 1;
    //         }
    //         k = kmp[k - 1];
    //     }
    // }
    

    // while (lo < hi)
    // {
    //     int mi = lo + (hi - lo) / 2;
    //     int cur = 0, end = cur + mi;
    //     bool works = true;
    //     while (end < n && works)
    //     {
    //         int next = -1;
    //         for (int i = cur + 1; i <= end; i++)
    //         {
    //             if (z[i] >= mi)
    //             {
    //                 cur = i;
    //                 end = cur + mi;
    //                 break;
    //             }
    //         }
    //         works = false;
    //     }
    //     if(works){
    //         hi = mi;
    //     }
    //     else{
    //         lo = mi + 1;
    //     }
    // }
    // cout << lo << nL;
    // int ans = n;
    // for(int i = n; i > 0; i--){
    //     if(dp[i] == n){
    //         ans = i;
    //     }
    // }
    // cout << ans << nL;
    return 0;
}