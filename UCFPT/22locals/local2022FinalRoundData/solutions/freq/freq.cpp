// Arup Guha
// 9/6/2022
// C++ Solution for 2022 UCF Final Round Problem: Letter Frequency

using namespace std;

#include <iostream>
#include <string>

#define MAX(a,b) ((a) > (b) ? a : b)

int main(void) {

	// freq[i][j] will be # of times letter j appears in position i.
	int freq[30][26];
	for (int i=0; i<30; i++) 
		for (int j=0; j<26; j++)
			freq[i][j] = 0;
			
	// max[i] stores most appearances of any letter at position i.
	int max[30];
	for (int i=0; i<30; i++) max[i] = 0;
	
	int n;
	cin >> n;
	
	// Read in the data, update frequency, max arrays.
	for (int i=0; i<n; i++) {
		string s;
		cin >> s;
		
		// Update frequency, max arrays.
		for (int j=0; j<s.length(); j++) {
			freq[j][s[j]-'a']++;
			max[j] = MAX(max[j], freq[j][s[j]-'a']);
		}
	}
	
	// Go through each position.
	for (int i=0; i<30; i++) {
	
		// We just want to get out.
		if (max[i] == 0) break;
		
		// header.
		cout << i+1 << ":";
		
		// Print out all letters that have the max frequency.
		for (int j=0; j<26; j++)
			if (freq[i][j] == max[i])
				cout << " " << (char)('a'+j);
		cout << endl;
	}

	return 0;
}