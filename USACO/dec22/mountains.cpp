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

const int MAX_VAL = 1000001;
 
/* Updates element at index 'i' of BIT. */
void update(int i, int add, vector<int>& BIT)
{
    while (i > 0 && i < BIT.size())
    {
        BIT[i] += add;
        i = i + (i & (-i));
    }
}
 
/* Returns cumulative sum of all elements of
   fenwick tree/BIT from start upto and
   including element at index 'i'. */
int sum(int i, vector<int>& BIT)
{
    int ans = 0;
    while (i > 0)
    {
        ans += BIT[i];
        i = i - (i & (-i));
    }
 
    return ans;
}
 
// Returns lower bound for k in BIT.
int findKthSmallest(int k, vector<int> &BIT)
{
    // Do binary search in BIT[] for given
    // value k.
    int l = 0;
    int h = BIT.size();
    while (l < h)
    {
        int mid = (l + h) / 2;
        if (k <= sum(mid, BIT))
            h = mid;
        else
            l = mid+1;
    }
 
    return l;
}
 
// Insert x into BIT. We basically increment
// rank of all elements greater than x.
void insertElement(int x, vector<int> &BIT)
{
    update(x, 1, BIT);
}
 
// Delete x from BIT. We basically decreases
// rank of all elements greater than x.
void deleteElement(int x, vector<int> &BIT)
{
    update(x, -1, BIT);
}
 
// Returns rank of element. We basically
// return sum of elements from start to
// index x.
int findRank(int x, vector<int> &BIT)
{
    return sum(x, BIT);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<ll> h(n);
    rep(i, 0, n){
        cin >> h[i];
    }
    ll curans = 0;
    vvi trees(n + 5, vi(n + 5, 0));
    rep(i, 0, n){
        int curbest = -1;
        rep(j, i + 1, n){
            if(curbest == -1 || (h[j] - h[i]) * (curbest - i) >= (h[curbest] - h[i]) * (j - i)){
                insertElement(j, trees[i]);
                curbest = j;
                curans++;
            }
        }
    }
    // cout << findKthSmallest(0, trees[1]) << nL;
    // cout << findKthSmallest(1, trees[1]) << nL;
    // cout << findKthSmallest(2, trees[1]) << nL;
    // cout << findKthSmallest(0, trees[2]) << nL;
    // // cout << findKthSmallest(1, trees[2]) << nL;
    // cout << findKthSmallest(20, trees[2]) << nL;
    // cout << findRank(2, trees[1]) << nL;
    // cout << findRank(3, trees[1]) << nL;
    // cout << findRank(4, trees[1]) << nL;
    // cout << findRank(n + 10, trees[1]) << nL;
    int nq; cin >> nq;
    rep(i, 0, nq){
        int ind, v; cin >> ind >> v;
        ind--;
        h[ind] += v;
        rep(k, 0, ind){
            //check if ind already in set
            if(findRank(ind, trees[k]) == findRank(ind - 1, trees[k])){
                if(findRank(ind - 1, trees[k]) != 0){
                    int prev = findKthSmallest(findRank(ind - 1, trees[k]), trees[k]);
                    if((h[ind] - h[k]) * (prev - k) >= (h[prev] - h[k]) * (ind - k)){
                        insertElement(ind, trees[k]);
                        curans++;
                    }
                }
            }
            if(findRank(ind, trees[k]) != findRank(ind - 1, trees[k])){
                int indrank = findRank(ind, trees[k]);
                while(findKthSmallest(indrank + 1, trees[k]) != trees[k].size()){
                    //there is a bigger element
                    int bigger = findKthSmallest(indrank + 1, trees[k]);
                    if((h[ind] - h[k]) * (bigger - k) > (h[bigger] - h[k]) * (ind - k)){
                        deleteElement(bigger, trees[k]);
                        curans--;
                    }
                    else{
                        break;
                    }
                }
            }
        }
        curans -= findRank(n, trees[ind]);
        trees[ind] = vi(n + 5, 0);
        int curbest = -1;
        rep(j, ind + 1, n){
            if(curbest == -1 || (h[j] - h[ind]) * (curbest - ind) >= (h[curbest] - h[ind]) * (j - ind)){
                insertElement(j, trees[ind]);
                curbest = j;
                curans++;
            }
        }
        cout << curans << nL;
    }
    
    return 0;
}