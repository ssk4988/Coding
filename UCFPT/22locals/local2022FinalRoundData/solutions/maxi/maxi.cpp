// Arup Guha
// 9/6/2022
// C++ Solution for 2022 UCF Final Round Problem: Number Maximization

using namespace std;

#include <iostream>
#include <string>

int main(void) {

	// I'll use a frequency array for fun.
	int freq[10];
	for (int i=0; i<10; i++) freq[i] = 0;
	
	// Read as string.
	string s;
	cin >> s;
	
	// Update frequency array.
	for (int i=0; i<s.length(); i++)
		freq[s[i]-'0']++;
	
	// Print in reverse order.
	for (int i=9; i>=0; i--)
		for (int j=0; j<freq[i]; j++)
			cout << i;
	cout << endl;

	return 0;
}