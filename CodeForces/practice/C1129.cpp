// #include <bits/stdc++.h>
// using namespace std;

// using ll = long long;
// using ld = long double;
// using pi = pair<int, int>;
// using pl = pair<ll, ll>;
// using pd = pair<ld, ld>;
// using vi = vector<int>;
// using vl = vector<ll>;
// using vd = vector<ld>;
// using vpi = vector<pi>;
// using vpl = vector<pl>;
// using vpd = vector<pd>;
// using vvi = vector<vi>;

// #define f first
// #define s second
// #define mp make_pair
// #define pb push_back
// #define lb lower_bound
// #define ub upper_bound
// #define all(x) x.begin(), x.end()
// #define sz(x) (int)(x).size()
// #define rep(i, a, b) for (int i = a; i < (b); ++i)
// #define nL "\n"

// struct SuffixArray {
// 	vi sa, lcp;
// 	SuffixArray(string& s, int lim=256) { // or basic_string<int>
// 		int n = sz(s) + 1, k = 0, a, b;
// 		vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
// 		sa = lcp = y, iota(all(sa), 0);
// 		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
// 			p = j, iota(all(y), n - j);
// 			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
// 			fill(all(ws), 0);
// 			rep(i,0,n) ws[x[i]]++;
// 			rep(i,1,lim) ws[i] += ws[i - 1];
// 			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
// 			swap(x, y), p = 1, x[sa[0]] = 0;
// 			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
// 				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
// 		}
// 		rep(i,1,n) rank[sa[i]] = i;
// 		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
// 			for (k && k--, j = sa[rank[i] - 1];
// 					s[i + k] == s[j + k]; k++);
// 	}
// };

// const ll MOD = 1e9 + 7;
// inline ll mod(ll k){
//     return k % MOD;
// }

// int main()
// {
//     cin.tie(0)->sync_with_stdio(0);
//     cin.exceptions(cin.failbit);
//     int n; cin >> n;
//     string str;
//     rep(i, 0, n){
//         char c; cin >> c;
//         str.pb(c);
//     }
//     SuffixArray sa(str);
//     vector<string> s4 = {"0011", "0101", "1110", "1111"};
//     ll ans = 0;
//     vector<ll> dp(n + 1);
//     vi valid(n + 1, 1);
//     for(int i = 0; i + 4 <= n; i++){
//         auto it = find(all(s4), str.substr(i, 4));
//         if(it != s4.end()) valid[i] = false;
//     }
//     vi rev(n + 1);
//     rep(i, 0, n + 1){
//         rev[sa.sa[i]] = i;
//     }
//     rep(i, 0, n){
//         rep(j, 0, i + 2) dp[j] = 0;
//         // dp[0] = 1;
//         for(int j = i; j )
//         for(int j = i + 1; j >= 0; j--){
//             for(int len = 1; len <= 4 && j - len >= 0; len++){
//                 if(len == 4 && !valid[j]) continue;
//                 dp[j - len] = mod(dp[j - len] + dp[j]);
//             }
//         }
//         int l = i + 1;
//         for(int k = rev[j], l = sa.lcp[k]; l >= i + 1 - j && k >= 0; k--){
//             if(sa.sa[k] < j) works = false;
//             l = min(l, sa.lcp[k]);
//         }

//         for(int j = i; j >= 0; j--){
//             bool works = true;
//             if(!works) continue;
//             // H hsh = h.hashInterval(j, i + 1);
//             // if(hshs.count(hsh)) continue;
//             ans = mod(ans + dp[j]);
//             // hshs.insert(hsh);
//         }
//         cout << ans << "\n";
//     } 
//     return 0;
// }
