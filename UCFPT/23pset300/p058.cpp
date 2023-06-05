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

vvi ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str >> str >> str >> str;
    bool maxima = str[0] == 'Y';
    cin >> str >> str >> str >> str;
    bool minima = str[0] == 'Y';
    cin >> str >> str;
    bool plateaus = str[0] == 'Y';
    if(maxima && minima && !plateaus){
        cout << "-1 x y + 8 5 * + ^\n";
    }
    else if(maxima && minima && plateaus){
        cout << "-1 x y + 8 5 * + ^ x y * +\n";
    }
    else if(maxima && !minima && !plateaus){
        cout << "0 x 2 + 2 ^ x 2 - 2 ^ * y 2 ^ + -\n";
    }
    else if(maxima && !minima && plateaus){
        cout << "0 3 3 * 3 * 5 * 7 * x * x 6 + x 4 + * x 2 + * x -2 + * x -4 + * x -6 + * y 6 + y 4 + * y 2 + * y -2 + * y -4 + * y -6 + * + + -\n";
    }
    else if(!maxima && minima && !plateaus){
        cout << "x 2 + 2 ^ x 2 - 2 ^ * y 2 ^ +\n";
    }
    else if(!maxima && minima && plateaus){
        cout << "3 3 * 3 * 5 * 7 * x * x 6 + x 4 + * x 2 + * x -2 + * x -4 + * x -6 + * y 6 + y 4 + * y 2 + * y -2 + * y -4 + * y -6 + * + +\n";
    }
    else if(!maxima && !minima && !plateaus){
        cout << "x 3 - 4 ^ y -5 + 2 ^ +\n";
    }
    else if(!maxima && !minima && plateaus){
        cout << "1\n";
    }
    // auto f = [&](int x, int y)->int{
    //     return ((x + y) % 2 == 0 ? 1 : -1) + x * y;
    //     // return (x + 2) * (x - 2) * (x - 2) - (y + 2) * (y - 2) * (y - 2);
    //     // return 
    //     // // (x - 2) * (x - 2) + (x + 3) * (x + 3) + (x + 8) * (x + 8) + (x - 7) * (x - 7)
    //     // // + 
    //     // (y - 2) * (y - 2) + (y + 3) * (y + 3) + (y + 8) * (y + 8) + (y - 7) * (y - 7)
    //     // ;
    //     // return 945 * x + (x + 6) * (x + 4) * (x + 2) * (x - 6) * (x - 4) * (x - 2) + (y + 6) * (y + 4) * (y + 2) * (y - 6) * (y - 4) * (y - 2);
    // };
    // vvi grid(21, vi(21));
    // rep(i, -10, 11){
    //     rep(j, -10, 11){
    //         grid[i + 10][j + 10] = f(i, j);
    //     }
    // }
    // rep(i, 0, 21){
    //     rep(j, 0, 21){
    //         cout << grid[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // int minima = 0, plateau = 0, maxima = 0;
    // rep(i, 0, 21){
    //     rep(j, 0, 21){
    //         int greater = 0, less = 0, equal = 0;
    //         rep(k, 0, 4){
    //             int i1 = i + ds[k][0], j1 = j + ds[k][1];
    //             if(i1 < 21 && j1 < 21 && i1 >= 0 && j1 >= 0){
    //                 if(grid[i][j] == grid[i1][j1]) equal++;
    //                 else if(grid[i][j] > grid[i1][j1]) greater++;
    //                 else less++;
    //             }
    //         }
    //         if(equal > 0) plateau++;
    //         if(greater == 4) maxima++;
    //         if(less == 4) minima++;
    //     }
    // }
    // cout << "has " << maxima << " maximas\n";
    // cout << "has " << minima << " minimas\n";
    // cout << "has " << plateau << " plateaus\n";
    
    return 0;
}
