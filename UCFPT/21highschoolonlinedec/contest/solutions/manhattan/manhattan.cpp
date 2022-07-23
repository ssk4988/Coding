#include <iostream>
#include <cmath>

using namespace std;

int main(void) {
	// Fast IO
	ios::sync_with_stdio(0); cin.tie(0);

	// Read in input
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		double x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		// Only traveling in straight lines means the total distance is |x2 - x1| to get to the
		// right x value, plus |y2 - y1| to get to the right y value.
		double manhattanDistance = abs(x2 - x1) + abs(y2 - y1);

		// The shortest possible distance Euclid can travel can be determined by the distance
		// formula: sqrt((x2 - x1)^2 - (y2 - y1)^2)
		double euclidDistance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

		if (euclidDistance < manhattanDistance) {
			cout << "Euclid is too fast!" << endl;
		}
		else {
			cout << "Dr. Manhattan wins again!" << endl;
		}
	}
}
