// Arup Guha
// 9/6/2022
// C++ Solution for 2022 UCF Final Round Problem: Simplified Calendar System

using namespace std;

#include <iostream>

int main(void) {

	// Get first day and day of week. 
	int day, mon, year, dayOfWeek;
	cin >> day >> mon >> year >> dayOfWeek;
	
	// Get second day...
	int curD, curM, curY;
	cin >> curD >> curM >> curY;
	
	// Calculate the # of days that have passed.
	int elapse = (curY - year)*360 + (curM-mon)*30 + (curD-day);
	
	// This is our new day...annoying wrap around because input used 1-7.
	int newD = (dayOfWeek + elapse)%7;
	if (newD == 0) newD = 7;
	cout << newD << endl;
	
	return 0;
}