// 2021 UCF HSPT Online - Piano
// Author: Josh Delagdo

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Read in the number of tests
  int numberTests;
  cin >> numberTests;

  // Go through every test
  for (int test=0; test<numberTests; test++) {
    // Read in the song
    string song;
    cin >> song;

    // Length of the song
    int length = song.length();

    // Since we have the ability to play every node with one hand,
    //   we can play the entire song without ever crossing hands by only
    //   playing with our right hand.
    string output = "";
    for (int i=0; i<length; i++) {
      output += "R";
    }

    // Output the answer
    cout << output << endl;
  }

  return 0;
}