/**
 * Ryan Glaspey, 03/07/20
 * First Draft
 */ 

#include <bits/stdc++.h>

using namespace std;

// A 2D vector (not a c++ container)
struct Vector {
    int x;
    int y;
};

// The cross product for the z component of a vector
int crossProductZ(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int main() {
    int t;
    cin >> t;

    // Make unit vectors for each primary direction
    const Vector NORTH = {0, 1};
    const Vector EAST = {1, 0};
    const Vector SOUTH = {0, -1};
    const Vector WEST = {-1, 0};

    while (t --> 0) {
        // Read direction into string to work with
        string direction;
        cin >> direction;

        // The answer being constructed
        double ans;
        // This will be used for cross product calculations
        Vector lastDirection;
        if (direction[0] == 'N') {
            ans = 0;
            lastDirection = NORTH;
        } else if (direction[0] == 'E') {
            ans = 90;
            lastDirection = EAST;
        } else if (direction[0] == 'S') {
            ans = 180; // or -180
            lastDirection = SOUTH;
        } else {
            ans = -90;
            lastDirection = WEST;
        }

        // The distance needed to be traveled on each
        // new primary direction given
        double jump = 45.0;

        // Handle the remaining sub-directions
        for (int i = 1; i < static_cast<int>(direction.length()); i++) {
            // Find the vector for the new direction
            Vector newDirection;
            if (direction[i] == 'N') {
                newDirection = NORTH;
            } else if (direction[i] == 'E') {
                newDirection = EAST;
            } else if (direction[i] == 'S') {
                newDirection = SOUTH;
            } else {
                newDirection = WEST;
            }
            // Cross product returns -1 for clockwise, 1 for counterclockwise.
            // This needs to be flipped because the compass directions add in
            // the clockwise direction
            ans += jump * (crossProductZ(lastDirection, newDirection) * -1);
            // Update direction
            lastDirection = newDirection;
            // Shrink jump
            jump /= 2.0;
        }
        // This algorithm is implemented with negative numbers.
        // Adding 360 to negative values will remap it to the correct range
        if (ans < 0) ans += 360.0;
        // add small bias for roundoff error
        ans += 1e-8;
        // Print the result to 1 decimal
        printf("%s is %.1f degrees\n", direction.c_str(), ans);
    }

    return 0;
}