#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// Our modulo.
const ll mod = 1'000'000'007;

// Custom hackpack code to calculate a matrix^e % mod.
// Will be useful in this question to solve the explosion of letters.
// For a deeper understanding of this algorithm, Google "Fast Matrix Exponentiation".
template <typename T>
struct FastMatExpo {
    ll n, m;
    vector<vector<T>> scalar, mult, ident, res;
    FastMatExpo(vector<vector<T>> _scalar, vector<vector<T>> _mult, ll _m) 
    { scalar = _scalar; mult = _mult; n = scalar.size(); m = _m; createIdent(); }
    void createIdent() {
        ident = vector<vector<T>>(n, vector<T>(n, 0));
        for (int i = 0; i < n; i++) ident[i][i] = 1;
    }
    vector<vector<T>> modPow(ll pow) { return res = applyMod(fastPow(scalar, pow-1)); }
    vector<vector<T>> fastPow(vector<vector<T>> mat, ll pow) {
        mat = applyMod(mat);
        if (pow==0) return ident;
        if (pow==1) return mat;
        if (pow&1) return matMult(mat, fastPow(mat, pow-1));
        return applyMod(fastPow(matMult(mat, mat), pow/2));
    }
    vector<vector<T>> matMult(vector<vector<T>> mat1, vector<vector<T>> mat2) {
        vector<vector<T>> res(n, vector<T>(n, (T)0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    res[i][j] = (res[i][j] + ((mat1[i][k] * mat2[k][j]) % m)) % m;
        return applyMod(res);
    }
    vector<vector<T>> applyMod(vector<vector<T>> mat) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] %= m;
        return mat;
    }
    ll getAns(int r) {
        ll ans = 0;
        for (int i = 0; i < n; i++)
            ans = (ans + ((res[r][i] * mult[i][0]) % m)) % m;
        return ans;
    }
};

void solve(int tt) {
    // Print the header for each output as specified by the problem statement.
    cout << "Genome #" << tt << ": "; 

    // Read in all necessary data from standard in.
    string a, c, t, g; cin >> a >> c >> t >> g;
    string genome; cin >> genome;
    ll n; cin >> n;

    // Store our replacement patterns and genes in an iterable vector.
    vector<string> patterns {a, c, t, g};
    vector<char> genes {'A', 'C', 'T', 'G'};

    // Prepare our matrice and mutliplier for fast matrix exponentation.
    vector<vector<ll>> matrix(4, vector<ll>(4));
    vector<vector<ll>> mult(4, vector<ll>(1));

    // For each possible letter replacement
    rep(i, 0, 4)
        // For each possible replacement pattern
        rep(j, 0, 4)
            // Populate our matrix with the count of letter i in pattern j.
            matrix[i][j] = count(all(patterns[j]), genes[i]);

    // Prepare our solution vector for multiplication.
    rep(i, 0, 4)
        // Count the occurences of individual letters in the original genome.
        mult[i][0] = count(all(genome), genes[i]);

    // Create new fast matrix expo object with the parameters we've created.
    FastMatExpo<ll> fme(matrix, mult, mod);
    // Raise that power! (n+1 because n^1 == n)
    fme.modPow(n + 1);

    // Get and output the answers for each letter.
    rep(r, 0, 4) 
        cout << fme.getAns(r) << " ";
    cout << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    // Read the number of test cases from stdin.
    int t; cin >> t;
    // For each test case, solve it!
    for (int tt = 1; tt <= t; tt++)
        solve(tt);

    return 0;    
}
