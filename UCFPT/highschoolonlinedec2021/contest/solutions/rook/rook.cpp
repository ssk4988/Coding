#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int get_closest(set<int> &curr_row, int rook)
{
  auto Rit = curr_row.upper_bound(rook);

  // subtracting one from the iterator gives the left closest pawn
  auto Lit = --curr_row.upper_bound(rook);
  int pawn;
  if (Lit != curr_row.end() && Rit != curr_row.end())
    pawn = (ll)rook - *Lit <= *Rit - rook ? *Lit : *Rit;
  else if (Lit == curr_row.end())
    pawn = *Rit;
  else
    pawn = *Lit;

  return pawn;
}

int main(void) 
{
  ios::sync_with_stdio(0); cin.tie(0);
  
  int NUM_CASES; cin >> NUM_CASES;
  for(int T = 1;T <= NUM_CASES;T++) 
  {
    int n, rook;
    cin >> n >> rook;

    set<int> curr_row, next_row;
    map<int, int> cc;

    for (int i = 1; i <= n; i++)
    {
      int a; cin >> a;
      curr_row.insert(a);
      cc[a] = i;
    }

    // 0 = white, 1 = black
    int turn = 0;
    while (curr_row.size() + next_row.size() > 1)
    {
      turn %= 2;
      if (turn++) // black - pawn move
      {
        if (curr_row.size() == 0) continue;

        int pawn = get_closest(curr_row, rook);
        curr_row.erase(pawn);
        next_row.insert(pawn);
      }
      else // white - rook move
      {
        if (curr_row.size() == 0)
        {
          // rook's current row is empty,
          // so we set the next row as the current row
          curr_row = next_row;
          next_row.clear();
        }
        else
        {
          int pawn = get_closest(curr_row, rook);
          curr_row.erase(pawn);
          cout << cc[rook = pawn] << " ";
        }
      }
    }
    cout << endl;
  }

  return 0;
}